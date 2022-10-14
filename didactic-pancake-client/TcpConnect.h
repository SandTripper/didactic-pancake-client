#ifndef TCPCONNECT_H
#define TCPCONNECT_H

#include <QtNetwork>
#include <vector>
#include <string.h>
#include <QObject>

class DataPacket;


class TcpConnect : public QObject
{
    Q_OBJECT

public:
    //心跳包发送间隔
    static const int HBTtime = 15;

    //最大的数据包类型数
    static const int MAX_CATEGORY = 128;

    //读缓冲区的大小
    static const int READ_BUFFER_SIZE = 1024;
    //写缓冲区的大小
    static const int WRITE_BUFFER_SIZE = 1024;

    /*请求类型
     HBT表示发送心跳包；
     LGN表示登录请求；
     RGT表示注册请求；
     LGT表示登出请求；
     SCU表示查找用户请求；
     ADF表示添加好友请求；
     RFR表示回复好友请求；
     */
    enum REQUEST
    {
        HBT = 0,
        LGN,
        RGT,
        LGT,
        SCU,
        ADF,
        RFR,
    };

    //主状态机的两种可能状态，分别表示：当前正在分析请求行，当前正在分析内容
    enum CHECK_STATE
    {
        CHECK_STATE_REQUESTLINE = 0,
        CHECK_STATE_HEADER,
        CHECK_STATE_CONTENT,
    };

    //行的读取状态，分别表示：读取到一个完整的行，行出错，行数据尚且不完整
    enum LINE_STATUS
    {
        LINE_OK = 0,
        LINE_BAD,
        LINE_OPEN,
    };

    /*服务器处理请求的结果：
        NO_REQUEST表示请求不完整，需要继续读取客户数据：
        GET_REQUEST表示获得了一个完整的的客户请求；
        BAD_REQUSET表示客户请求有语法错误；
        INTERNAL_ERROR表示服务器内部错误；
        CLOSED_CONNECTION表示客户端已经关闭连接*/
    enum RESULT_CODE
    {
        NO_REQUEST = 0,
        GET_REQUEST,
        BAD_REQUEST,
        INTERNAL_ERROR,
        CLOSED_CONNECTION
    };

    std::vector<std::vector<DataPacket>> vec;

public:
    //返回全局唯一实例
    static TcpConnect *getInstance();

    ~TcpConnect();

    // request转char
    const char *ReqToString(REQUEST r);

    //填充应答
    bool write_data(const DataPacket &data);

private:
    TcpConnect();
    //初始化连接
    void init();

    //非阻塞读操作
    bool read();

    //非阻塞写操作
    bool write();

    //解析请求
    RESULT_CODE process_read();

    //下面这一组函数被process_read调用以分析请求
    RESULT_CODE parse_request_line(char *text);
    RESULT_CODE parse_headers(char *text);
    RESULT_CODE parse_content(char *text);
    RESULT_CODE do_request();
    char *get_line();
    LINE_STATUS parse_line();

    //下面这一组函数被process_write调用以填充HTTP应答
    bool add_response(const char *format, ...);
    bool add_content(const char *content);
    bool add_status_line(const char *status);
    bool add_headers(int content_length);
    bool add_content_length(int content_length);
    bool add_blank_line();

signals:
    // void HBTpackAdd();
    void LGNpackAdd();
    void RGTpackAdd();
    void SCUpackAdd();
    void ADFpackAdd();
    void RFRpackAdd();

protected slots:
    //读取并处理新到的数据
    void read_handler();

private:
    QTcpSocket *m_client;

    //读缓冲区
    char m_read_buf[READ_BUFFER_SIZE];

    //标识读缓冲中已经读入的客户数据的最后一个字节的下一个位置
    int m_read_idx;

    //当前正在分析的字符在读缓冲区中的位置
    int m_checked_idx;

    //当前正在解析的行的起始位置
    int m_start_line;

    //写缓冲区
    char m_write_buf[WRITE_BUFFER_SIZE];

    //写缓冲区中待发送的字节数
    int m_write_idx;

    //主状态机当前所处的状态
    CHECK_STATE m_check_state;

    //需要发送的字节数
    int m_bytes_to_send;
    //已经发送的字节数
    int m_bytes_have_send;

    // 数据消息体的长度
    int m_content_length;

    //数据状态码
    REQUEST m_method;

    //存储数据正文
    char *m_string;
};

//数据包类
class DataPacket
{
public:
    DataPacket()
    {
        category = TcpConnect::HBT;
        content = NULL;
        content_len = 0;
    }
    DataPacket(TcpConnect::REQUEST cat, const char *con)
    {
        category = cat;
        content_len = strlen(con);
        content = new char[content_len+1];
        strncpy(content, con, content_len);
        content[content_len]='\0';
    }
    DataPacket(TcpConnect::REQUEST cat, int conlen, const char *con)
    {
        category = cat;
        content_len = conlen;
        content = new char[conlen+1];
        strncpy(content, con, conlen);
        content[content_len]='\0';
    }
    DataPacket(const DataPacket &other)
    {
        category = other.category;
        content_len = other.content_len;
        content = new char[content_len+1];
        strncpy(content, other.content, content_len);
        content[content_len]='\0';
    }
    ~DataPacket()
    {
        delete[] content;
    }
    TcpConnect::REQUEST category;
    int content_len;
    char *content;
};

#endif // TCPCONNECT_H
