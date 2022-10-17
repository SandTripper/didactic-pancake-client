#include "TcpConnect.h"

#include <stdio.h>
#include <exception>
#include <QDebug>
#include <QtNetwork>
#include <string>
#include <QObject>
#include <iostream>
#include <QDebug>

using namespace std;

TcpConnect *TcpConnect::getInstance()
{
    static TcpConnect tcpConn;
    return &tcpConn;
}

TcpConnect::TcpConnect() : m_sessionID(""),
                           m_enable(1),
                           m_client(new QTcpSocket),
                           m_heartBeatNum(1),
                           m_heartBeatNumRecv(1)
{
    for (int i = 0; i < MAX_CATEGORY; i++)
    {
        vec.emplace_back(vector<DataPacket>());
    }

    connect(m_client, &QTcpSocket::readyRead, this, &TcpConnect::read_handler);
    connect(this, &TcpConnect::HBTpackAdd, this, &TcpConnect::HBTpackHandler);
    connect(this, &TcpConnect::disconnected, this, &TcpConnect::reconnect);
    connect(this, &TcpConnect::reconnected, this, &TcpConnect::relogin);

    m_client->connectToHost(QHostAddress("1.117.146.195"), 4399);

    checkConnect();
}

TcpConnect::~TcpConnect()
{
    m_client->close();
    delete m_client;
}

const char *TcpConnect::ReqToString(TcpConnect::REQUEST r)
{
    switch (r)
    {
    case HBT:
        return "HBT";
    case LGN:
        return "LGN";
    case RGT:
        return "RGT";
    case LGT:
        return "LGT";
    case SCU:
        return "SCU";
    case ADF:
        return "ADF";
    case RFR:
        return "RFR";
    case RCN:
        return "RCN";
    default:
        return "ERR";
    }
}

void TcpConnect::initRead()
{
    m_method = HBT;
    m_start_line = 0;
    m_checked_idx = 0;

    m_check_state = CHECK_STATE_REQUESTLINE;
    m_read_idx = 0;
    memset(m_read_buf, '\0', READ_BUFFER_SIZE);
}

void TcpConnect::initWrite()
{
    m_bytes_have_send = 0;
    m_bytes_to_send = 0;
    m_write_idx = 0;
    m_content_length = 0;
    memset(m_write_buf, '\0', WRITE_BUFFER_SIZE);
}

void TcpConnect::read_handler()
{
    if (read())
    {
        RESULT_CODE read_ret = process_read();
        if (read_ret == NO_REQUEST)
        {
            return;
        }
        vec[m_method].emplace_back(DataPacket(m_method, m_content_length, m_string));

        //发出数据包增加信号
        switch (m_method)
        {
        case HBT:
            emit HBTpackAdd();
            break;
        case LGN:
            emit LGNpackAdd();
            break;
        case RGT:
            emit RGTpackAdd();
            break;
        case SCU:
            emit SCUpackAdd();
            break;
        case ADF:
            emit ADFpackAdd();
            break;
        case RFR:
            emit RFRpackAdd();
            break;
        case RCN:
            emit RCNpackAdd();
            break;
        default:
            break;
        }

        initRead();
    }
}

void TcpConnect::HBTpackHandler()
{
    for (const auto data : vec[TcpConnect::HBT])
    {
        if (data.content_len == 0)
            continue;
        m_heartBeatNumRecv = max(m_heartBeatNumRecv, stoi(string(data.content, data.content + data.content_len - 2)));
    }
    vec[TcpConnect::HBT].clear();
}

void TcpConnect::reconnect()
{
    m_client->close();

    m_client->connectToHost(QHostAddress("1.117.146.195"), 4399);
}

void TcpConnect::relogin()
{
    if (m_sessionID != "")
    {
        QString content = m_sessionID + "\r\n";
        // QString转char
        char *ctmp;
        QByteArray ba = content.toLatin1();
        ctmp = ba.data();
        write_data(DataPacket(RCN, content.length(), ctmp));
    }
    m_enable = true;
}

void TcpConnect::checkConnect()
{
    QString content = QString::number(++m_heartBeatNum);
    content += "\r\n";

    // QString转char
    char *ctmp;
    QByteArray ba = content.toLatin1();
    ctmp = ba.data();
    write_data(DataPacket(HBT, content.length(), ctmp));

    QTimer::singleShot(LONGEST_REPLY_INTERVAL * 1000, this, [=]()
                       {
        if(m_heartBeatNumRecv<m_heartBeatNum)
        {
            emit disconnected();
            m_enable=false;
        }
        else
        {
            if(m_enable==false)
            {
                emit reconnected();
            }
        } });
    if (m_enable)
    {
        QTimer::singleShot(HBT_INTERVAL * 1000, this, [=]()
                           { checkConnect(); });
    }
    else
    {
        QTimer::singleShot(RECONNECT_INTERVAL * 1000, this, [=]()
                           { checkConnect(); });
    }
}

bool TcpConnect::read()
{
    if (m_read_idx >= READ_BUFFER_SIZE)
    {
        return false;
    }
    int bytes_read = 0;

    bytes_read = m_client->read(m_read_buf + m_read_idx, READ_BUFFER_SIZE - m_read_idx);
    m_read_idx += bytes_read;
    if (bytes_read <= 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

TcpConnect::RESULT_CODE TcpConnect::process_read()
{
    LINE_STATUS linestatus = LINE_OK; //记录当前行的读取状态
    RESULT_CODE retcode = NO_REQUEST; //记录处理结果
    char *text = 0;

    //主状态机，用于从buffer中取出所有完整的行
    while (((m_check_state == CHECK_STATE_CONTENT) && (linestatus == LINE_OK)) ||
           ((linestatus = parse_line()) == LINE_OK))
    {
        text = get_line();            // start_line是行在buffer中 的起始位置
        m_start_line = m_checked_idx; //记录下一行的起始位置

        switch (m_check_state)
        {
        case CHECK_STATE_REQUESTLINE: //第一个状态，分析消息类型行
            retcode = parse_request_line(text);
            if (retcode == BAD_REQUEST)
            {
                return BAD_REQUEST;
            }
            break;
        case CHECK_STATE_HEADER: //第二个状态，分析头部字段
            retcode = parse_headers(text);
            if (retcode == BAD_REQUEST)
            {
                return BAD_REQUEST;
            }
            else if (retcode == GET_REQUEST)
            {
                return GET_REQUEST;
            }
            break;
        case CHECK_STATE_CONTENT:
            retcode = parse_content(text);
            if (retcode == GET_REQUEST)
            {
                return GET_REQUEST;
            }
            linestatus = LINE_OPEN;
            break;
        default:
            return INTERNAL_ERROR;
        }
    }
    return NO_REQUEST;
}

bool TcpConnect::write_data(const DataPacket &data)
{
    add_status_line(ReqToString(data.category));
    add_headers(data.content_len);
    if (!add_content(data.content))
    {
        return false;
    }
    m_client->write(m_write_buf, m_write_idx);
    initWrite();
    return 0;
}

TcpConnect::RESULT_CODE TcpConnect::parse_request_line(char *text)
{
    char *method = text;
    if (strcasecmp(method, "HBT") == 0)
    {
        m_method = HBT;
    }
    else if (strcasecmp(method, "LGN") == 0)
    {
        m_method = LGN;
    }
    else if (strcasecmp(method, "RGT") == 0)
    {
        m_method = RGT;
    }
    else if (strcasecmp(method, "LGT") == 0)
    {
        m_method = LGT;
    }
    else if (strcasecmp(method, "SCU") == 0)
    {
        m_method = SCU;
    }
    else if (strcasecmp(method, "ADF") == 0)
    {
        m_method = ADF;
    }
    else if (strcasecmp(method, "RFR") == 0)
    {
        m_method = RFR;
    }
    else if (strcasecmp(method, "RCN") == 0)
    {
        m_method = RCN;
    }
    else
    {
        return BAD_REQUEST;
    }

    //消息类型行处理完毕，状态转移到头部字段的分析
    m_check_state = CHECK_STATE_HEADER;
    return NO_REQUEST;
}

TcpConnect::RESULT_CODE TcpConnect::parse_headers(char *text)
{
    //遇到空行，表示头部字段解析完毕
    if (text[0] == '\0')
    {
        /*如果数据有消息体，则还需要读取m_content_length字节的消息体，
            状态机转移到CHECK_STATE_CONTENT状态*/
        if (m_content_length != 0)
        {
            m_check_state = CHECK_STATE_CONTENT;
            return NO_REQUEST;
        }
        //否则说明我们得到了一个完整的数据包
        else
        {
            return GET_REQUEST;
        }
    }
    //处理"Content-Length"头部字段
    else if (strncasecmp(text, "Content-Length:", 15) == 0)
    {
        text += 15;
        text += strspn(text, " \t");
        m_content_length = atol(text);
    }
    else //其他头部字段都不处理
    {
    }

    return NO_REQUEST;
}

TcpConnect::RESULT_CODE TcpConnect::parse_content(char *text)
{
    if (m_read_idx >= (m_content_length + m_checked_idx))
    {
        text[m_content_length] = '\0';
        m_string = text;
        return GET_REQUEST;
    }
    else
    {
        return NO_REQUEST;
    }
}

char *TcpConnect::get_line()
{
    return m_read_buf + m_start_line;
}

TcpConnect::LINE_STATUS TcpConnect::parse_line()
{
    char temp;
    /*buffer中第0~checked_index字节都已分析完毕，
        第checked_index~(read_index-1)字节由下面的循环挨个分析*/
    for (; m_checked_idx < m_read_idx; ++m_checked_idx)
    {
        //获得当前要分析的字节
        temp = m_read_buf[m_checked_idx];
        //如果当前的字节是'\r'，即回车符，则说明可能读取到一个完整的行
        if (temp == '\r')
        {
            /*如果'\r'字符碰巧是目前buffer中最后一个已经被读入的数据，
                那么这次分析没有读取到一个完整的行，返回LINE_OPEN以表示还需要
                继续读取数据才能进一步分析*/
            if ((m_checked_idx + 1) == m_read_idx)
            {
                return LINE_OPEN;
            }
            //如果下一个字符是'\n'，则说明我们成功读取到一个完整的行
            else if (m_read_buf[m_checked_idx + 1] == '\n')
            {
                m_read_buf[m_checked_idx++] = '\0';
                m_read_buf[m_checked_idx++] = '\0';
                return LINE_OK;
            }
            //否则，就说明数据包存在语法问题
            return LINE_BAD;
        }
        //如果当前的字节是'\n'，即换行符，则也说明可能读取到一个完整的行
        else if (temp == '\n')
        {
            //如果上一个字符是'\r'，则说明我们成功读取到一个完整的行
            if ((m_checked_idx > 1) && m_read_buf[m_checked_idx - 1] == '\r')
            {
                m_read_buf[m_checked_idx - 1] = '\0';
                m_read_buf[m_checked_idx++] = '\0';
                return LINE_OK;
            }
            //否则，就说明数据包存在语法问题
            else
            {
                return LINE_BAD;
            }
        }
    }
    return LINE_OPEN;
}

bool TcpConnect::add_response(const char *format, ...)
{
    if (m_write_idx >= WRITE_BUFFER_SIZE)
    {
        return false;
    }
    va_list arg_list;
    va_start(arg_list, format);
    int len = vsnprintf(m_write_buf + m_write_idx,
                        WRITE_BUFFER_SIZE - 1 - m_write_idx, format, arg_list);
    if (len >= (WRITE_BUFFER_SIZE - 1 - m_write_idx))
    {
        va_end(arg_list);
        return false;
    }
    m_write_idx += len;
    va_end(arg_list);

    return true;
}

bool TcpConnect::add_content(const char *content)
{
    return add_response("%s", content);
}

bool TcpConnect::add_status_line(const char *status)
{
    return add_response("%s\r\n", status);
}

bool TcpConnect::add_headers(int content_length)
{
    add_content_length(content_length);
    add_blank_line();
    return true;
}

bool TcpConnect::add_content_length(int content_length)
{
    return add_response("Content-Length: %d\r\n", content_length);
}

bool TcpConnect::add_blank_line()
{
    return add_response("%s", "\r\n");
}
