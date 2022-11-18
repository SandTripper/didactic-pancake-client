#include "TcpConnect.h"

#include <stdio.h>
#include <exception>
#include <QDebug>
#include <QtNetwork>
#include <string>
#include <QObject>
#include <iostream>

using namespace std;

TcpConnect *TcpConnect::getInstance()
{
    static TcpConnect tcpConn;
    return &tcpConn;
}

TcpConnect::TcpConnect() : m_sessionID(""),
                           m_enable(false),
                           m_client(new QTcpSocket),
                           m_latestTime(0)
{
    for (int i = 0; i < MAX_CATEGORY; i++)
    {
        vec.emplace_back(vector<DataPacket>());
    }

    connect(m_client, &QTcpSocket::disconnected, this, &TcpConnect::disconnected);

    connect(m_client, &QTcpSocket::readyRead, this, &TcpConnect::read_handler);
    connect(m_client, &QTcpSocket::connected, this, &TcpConnect::reconnected);
    connect(this, &TcpConnect::disconnected, this, [=]()
            {m_enable = false;reconnect(); });
    connect(this, &TcpConnect::reconnected, this, &TcpConnect::relogin);

    m_client->setProxy(QNetworkProxy::NoProxy);

    //利用重连函数进行连接
    reconnect();

    checkConnect();

    m_content = nullptr;
}

TcpConnect::~TcpConnect()
{
    m_client->close();
    delete m_client;
}

void TcpConnect::initRead()
{
    m_check_state = CHECK_STATE_TYPELINE;
    m_method = HBT;
    m_start_line = 0;
    m_checked_idx = 0;
    m_content_length = 0;
    m_read_idx = 0;
    m_content_len_have_read = 0;
    m_content = nullptr;
    memset(m_read_buf, '\0', READ_BUFFER_SIZE);
}

void TcpConnect::initWrite()
{
}

void TcpConnect::read_handler()
{
    m_latestTime = QDateTime::currentDateTime().toTime_t();
    while (read())
    {
        RESULT_CODE read_ret = GET_REQUEST;
        while (m_checked_idx < m_read_idx)
        {
            read_ret = process_read();
            if (read_ret == NO_REQUEST)
            {
                //最后一个数据包不完整，保留残缺的数据行，删除已读过的读缓冲区字符
                int broken_line_len = m_read_idx - m_start_line;
                for (int p1 = 0, p2 = m_start_line; p1 < broken_line_len; ++p1, ++p2)
                {
                    m_read_buf[p1] = p2;
                }
                memset(m_read_buf + broken_line_len, '\0', READ_BUFFER_SIZE - broken_line_len);
                m_read_idx -= m_start_line;
                m_checked_idx = m_read_idx;
                m_start_line = 0;
                break;
            }

            m_check_state = CHECK_STATE_TYPELINE;
            m_start_line = m_checked_idx;
            m_content_len_have_read = 0;
            vec[m_method].emplace_back(DataPacket(m_method, m_content_length, m_content));
            if (m_content != nullptr)
            {
                delete[] m_content;
                m_content = nullptr;
            }

            //发出数据包增加信号
            switch (m_method)
            {
            case HBT:
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
            case DEF:
                emit DEFpackAdd();
                break;
            case RFR:
                emit RFRpackAdd();
                break;
            case RCN:
                emit RCNpackAdd();
                break;
            case GFI:
                emit GFIpackAdd();
                break;
            case AFI:
                emit AFIpackAdd();
                break;
            case DFI:
                emit DFIpackAdd();
                break;
            case SMA:
                emit SMApackAdd();
                break;
            case RMA:
                emit RMApackAdd();
                break;
            case RDY:
                break;
            case SAV:
                emit SAVpackAdd();
                break;
            case RAV:
                emit RAVpackAdd();
                break;
            case SOC:
                emit SOCpackAdd();
                break;
            case ROC:
                emit ROCpackAdd();
                break;
            case AOC:
                emit AOCpackAdd();
                break;
            case DOC:
                emit DOCpackAdd();
                break;
            case EOC:
                emit EOCpackAdd();
                break;
            default:
                break;
            }
        }
        if (read_ret != NO_REQUEST)
        {
            initRead();
        }
    }
}

TcpConnect::RESULT_CODE TcpConnect::process_read()
{
    LINE_STATUS linestatus = LINE_OK; //记录当前行的读取状态
    RESULT_CODE retcode = NO_REQUEST; //记录请求的处理结果
    char *text = 0;

    //主状态机，用于从buffer中取出所有完整的行
    while (((m_check_state == CHECK_STATE_CONTENT) && (linestatus == LINE_OK)) ||
           ((linestatus = parse_line()) == LINE_OK))
    {
        text = get_line();            // start_line是行在buffer中 的起始位置
        m_start_line = m_checked_idx; //记录下一行的起始位置

        switch (m_check_state)
        {
        case CHECK_STATE_TYPELINE: //第一个状态，分析数据包类型行
            retcode = parse_type_line(text);
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
        case CHECK_STATE_CONTENT: //第三个状态，分析数据包正文
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

char *TcpConnect::get_line()
{
    return m_read_buf + m_start_line;
}

TcpConnect::RESULT_CODE TcpConnect::parse_type_line(char *text)
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
    else if (strcasecmp(method, "DEF") == 0)
    {
        m_method = DEF;
    }
    else if (strcasecmp(method, "RFR") == 0)
    {
        m_method = RFR;
    }
    else if (strcasecmp(method, "RCN") == 0)
    {
        m_method = RCN;
    }
    else if (strcasecmp(method, "GFI") == 0)
    {
        m_method = GFI;
    }
    else if (strcasecmp(method, "AFI") == 0)
    {
        m_method = AFI;
    }
    else if (strcasecmp(method, "DFI") == 0)
    {
        m_method = DFI;
    }
    else if (strcasecmp(method, "SMA") == 0)
    {
        m_method = SMA;
    }
    else if (strcasecmp(method, "RMA") == 0)
    {
        m_method = RMA;
    }
    else if (strcasecmp(method, "RDY") == 0)
    {
        m_method = RDY;
    }
    else if (strcasecmp(method, "SAV") == 0)
    {
        m_method = SAV;
    }
    else if (strcasecmp(method, "RAV") == 0)
    {
        m_method = RAV;
    }
    else if (strcasecmp(method, "SOC") == 0)
    {
        m_method = SOC;
    }
    else if (strcasecmp(method, "ROC") == 0)
    {
        m_method = ROC;
    }
    else if (strcasecmp(method, "AOC") == 0)
    {
        m_method = AOC;
    }
    else if (strcasecmp(method, "DOC") == 0)
    {
        m_method = DOC;
    }
    else if (strcasecmp(method, "EOC") == 0)
    {
        m_method = EOC;
    }
    else
    {
        return BAD_REQUEST;
    }

    //请求行处理完毕，状态转移到头部字段的分析
    m_check_state = CHECK_STATE_HEADER;
    return NO_REQUEST;
}

TcpConnect::RESULT_CODE TcpConnect::parse_headers(char *text)
{
    //遇到空行，表示头部字段解析完毕
    if (text[0] == '\0')
    {
        /*如果数据包有消息体，则还需要读取m_content_length字节的消息体，
        状态机转移到CHECK_STATE_CONTENT状态*/
        if (m_content_length != 0)
        {
            m_check_state = CHECK_STATE_CONTENT;
            return NO_REQUEST;
        }
        //否则说明我们得到了一个完整的请求
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
    if (m_content == nullptr)
    {
        m_content = new char[m_content_length + 1];
    }
    if (m_read_idx >= (m_content_length - m_content_len_have_read + m_checked_idx))
    {
        /*如果当前已读到数据包正文的结尾
        将数据拷贝至m_content并加上'\0'*/
        memcpy(m_content + m_content_len_have_read, text, m_content_length - m_content_len_have_read);
        m_content[m_content_length] = '\0';
        m_checked_idx += m_content_length - m_content_len_have_read;
        m_start_line = m_checked_idx;
        m_content_len_have_read = m_content_length;
        return GET_REQUEST;
    }
    else
    {
        /*如果当前未读到数据包正文的结尾
        将读到的数据段拷贝至m_content并返回NO_REQUEST等待下次数据*/
        memcpy(m_content + m_content_len_have_read, text, m_read_idx - m_checked_idx);
        m_content_len_have_read += m_read_idx - m_checked_idx;
        m_start_line = m_read_idx;
        m_checked_idx = m_read_idx;
        return NO_REQUEST;
    }
}
/*
    if (m_content == nullptr)
    {
        m_content = new char[m_content_length + 1];
    }
    if (m_read_idx >= (m_content_length - m_content_len_have_read + m_checked_idx))
    {
        memcpy(m_content + m_content_len_have_read, text, m_content_length - m_content_len_have_read);
        m_content[m_content_length] = '\0';
        m_checked_idx += m_content_length - m_content_len_have_read;
        m_start_line = m_checked_idx;
        m_content_len_have_read = m_content_length;
        return GET_REQUEST;
    }
    else
    {
        memcpy(m_content + m_content_len_have_read, text, m_read_idx - m_checked_idx);
        m_start_line = m_read_idx;
        m_checked_idx = m_read_idx;
        m_content_len_have_read += m_read_idx - m_checked_idx;
        return NO_REQUEST;
    }
*/

const char *TcpConnect::ReqToString(TcpConnect::PACKET_TYPE r)
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
    case DEF:
        return "DEF";
    case RFR:
        return "RFR";
    case RCN:
        return "RCN";
    case GFI:
        return "GFI";
    case AFI:
        return "AFI";
    case DFI:
        return "DFI";
    case SMA:
        return "SMA";
    case RMA:
        return "RMA";
    case RDY:
        return "RDY";
    case SAV:
        return "SAV";
    case RAV:
        return "RAV";
    case SOC:
        return "SOC";
    case ROC:
        return "ROC";
    case AOC:
        return "AOC";
    case DOC:
        return "DOC";
    case EOC:
        return "EOC";
    default:
        return "ERR";
    }
}

void TcpConnect::reconnect()
{

    if (m_enable)
    {
        return;
    }

    m_client->close();

    m_client->connectToHost(QHostAddress("1.117.146.195"), 4399);

    QTimer::singleShot(RECONNECT_INTERVAL * 1000, this, [=]()
                       { reconnect(); });
}

void TcpConnect::relogin()
{
    m_latestTime = QDateTime::currentDateTime().toTime_t();

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
    if (!m_enable)
    {
        QTimer::singleShot(HBT_INTERVAL * 1000, this, [=]()
                           { checkConnect(); });
        return;
    }
    uint nowTime = QDateTime::currentDateTime().toTime_t();
    if (nowTime - m_latestTime > LONGEST_NO_DATA_INTERVAL)
    {
        emit disconnected();
        return;
    }

    QString content = QString::number(nowTime);
    content += "\r\n";

    // QString转char
    char *ctmp;
    QByteArray ba = content.toLatin1();
    ctmp = ba.data();
    write_data(DataPacket(HBT, content.length(), ctmp));
    QTimer::singleShot(HBT_INTERVAL * 1000, this, [=]()
                       { checkConnect(); });
}

bool TcpConnect::write_data(const DataPacket &data)
{
    //    add_status_line(ReqToString(data.category));
    //    add_headers(data.content_len);
    //    if (!add_content(data.content))
    //    {
    //        return false;
    //    }
    //    m_client->write(m_write_buf, m_write_idx);
    //    initWrite();
    char *buf = nullptr;
    int len = DataPacket::get_format(data, buf);
    m_client->write(buf, len);
    delete[] buf;
    return true;
}
