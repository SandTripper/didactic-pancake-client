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
    static const int HBT_INTERVAL = 20;

    //重连间隔
    static const int RECONNECT_INTERVAL = 6;

    //最长无数据间隔
    static const int LONGEST_NO_DATA_INTERVAL = 30;

    //最大的数据包类型数
    static const int MAX_CATEGORY = 128;

    //读缓冲区的大小
    static const int READ_BUFFER_SIZE = 1024;

    /*数据包类型
     HBT表示发送心跳包；
     LGN表示登录请求；
     RGT表示注册请求；
     LGT表示登出请求；
     SCU表示查找用户请求；
     ADF表示添加好友请求；
     DEF表示删除好友；
     RFR表示回复好友请求；
     RCN表示重连请求；
     GFI表示获取好友列表请求；
     AFI表示增加好友；
     DFI表示去除好友；
     SMA表示发送消息；
     RMA表示接收消息；
     RDY表示服务器端就绪；
     SAV表示发送头像数据；
     RAV表示接收头像数据；
     */
    enum PACKET_TYPE
    {
        HBT = 0,
        LGN,
        RGT,
        LGT,
        SCU,
        ADF,
        DEF,
        RFR,
        RCN,
        GFI,
        AFI,
        DFI,
        SMA,
        RMA,
        RDY,
        SAV,
        RAV
    };

    /*主状态机的三种可能状态
        CHECK_STATE_TYPELINE 表示当前正在分析状态行；
        CHECK_STATE_HEADER 表示当前正在头部字段；
        CHECK_STATE_CONTENT 表示当前正在分析正文*/
    enum CHECK_STATE
    {
        CHECK_STATE_TYPELINE = 0,
        CHECK_STATE_HEADER,
        CHECK_STATE_CONTENT,
    };

    /*行的读取状态
        LINE_OK 表示读取到一个完整的行；
        LINE_BAD 表示行出错；
        LINE_OPEN 表示行数据尚且不完整*/
    enum LINE_STATUS
    {
        LINE_OK = 0,
        LINE_BAD,
        LINE_OPEN,
    };

    /*处理数据包的结果：
    NO_REQUEST表示请求不完整，需要继续读取数据包：
    GET_REQUEST表示获得了一个完整的数据包；
    BAD_REQUSET表示数据包有语法错误；
    INTERNAL_ERROR表示内部错误；
    CLOSED_CONNECTION连接断开*/
    enum RESULT_CODE
    {
        NO_REQUEST = 0,
        GET_REQUEST,
        BAD_REQUEST,
        INTERNAL_ERROR,
        CLOSED_CONNECTION
    };

    //存储读到的包
    std::vector<std::vector<DataPacket>> vec;

    QString m_sessionID;

    //连接是否可用且登录
    bool m_enable;

public:
    //返回全局唯一实例
    static TcpConnect *getInstance();

    ~TcpConnect();

    // request转const char*
    static const char *ReqToString(PACKET_TYPE r);

    //填充应答
    bool write_data(const DataPacket &data);

private:
    TcpConnect();
    //初始化读
    void initRead();

    //初始化写
    void initWrite();

    //非阻塞读操作
    bool read();

    //非阻塞写操作
    bool write();

    //解析数据包
    RESULT_CODE process_read();

    //下面这一组函数被process_read调用以解析数据包
    RESULT_CODE parse_type_line(char *text);
    RESULT_CODE parse_headers(char *text);
    RESULT_CODE parse_content(char *text);
    RESULT_CODE do_request();
    char *get_line();
    LINE_STATUS parse_line();

signals:
    void LGNpackAdd();
    void RGTpackAdd();
    void SCUpackAdd();
    void ADFpackAdd();
    void DEFpackAdd();
    void RFRpackAdd();
    void RCNpackAdd();
    void GFIpackAdd();
    void AFIpackAdd();
    void DFIpackAdd();
    void SMApackAdd();
    void RMApackAdd();
    void SAVpackAdd();
    void RAVpackAdd();

    //断线
    void disconnected();
    //重连成功
    void reconnected();

private slots:
    //读取并处理新到的数据
    void read_handler();

    //尝试重连
    void reconnect();

    //尝试重新登录
    void relogin();

private:
    //循环检测网络状况
    void checkConnect();

private:
    QTcpSocket *m_client;

    //读缓冲区
    char m_read_buf[READ_BUFFER_SIZE];

    //标识读缓冲中已经读入的服务器数据的最后一个字节的下一个位置
    int m_read_idx;

    //当前正在分析的字符在读缓冲区中的位置
    int m_checked_idx;

    //当前正在解析的行的起始位置
    int m_start_line;

    //主状态机当前所处的状态
    CHECK_STATE m_check_state;

    //数据包类型
    PACKET_TYPE m_method;

    // 数据包正文的长度
    int m_content_length;

    //数据包正文已读取的长度
    int m_content_len_have_read;

    //存储数据包正文
    char *m_content;

    //最晚的数据包到达时间
    uint m_latestTime;
};

//数据包类
class DataPacket
{
public:
    DataPacket()
    {
        category = TcpConnect::HBT;
        content = nullptr;
        content_len = 0;
    }
    DataPacket(TcpConnect::PACKET_TYPE cat, const char *con)
    {
        category = cat;
        content_len = strlen(con);
        content = new char[content_len + 1];
        memcpy(content, con, content_len);
        content[content_len] = '\0';
    }
    DataPacket(TcpConnect::PACKET_TYPE cat, int conlen, const char *con)
    {
        category = cat;
        content_len = conlen;
        content = new char[conlen + 1];
        memcpy(content, con, conlen);
        content[content_len] = '\0';
    }
    DataPacket(const DataPacket &other)
    {
        category = other.category;
        content_len = other.content_len;
        content = new char[content_len + 1];
        memcpy(content, other.content, content_len);
        content[content_len] = '\0';
    }
    ~DataPacket()
    {
        delete[] content;
    }
    static int get_format(const DataPacket &pack, char *&format_pack)
    {
        std::string type_head_str = TcpConnect::ReqToString(pack.category);
        type_head_str += "\r\nContent-Length: ";
        type_head_str += std::to_string(pack.content_len);
        type_head_str += "\r\n\r\n";
        int type_head_str_len = type_head_str.length();

        format_pack = new char[type_head_str_len + pack.content_len + 1];
        memcpy(format_pack, type_head_str.c_str(), type_head_str_len);
        memcpy(format_pack + type_head_str_len, pack.content, pack.content_len);
        format_pack[type_head_str_len + pack.content_len] = '\0';
        return type_head_str_len + pack.content_len;
    }
    TcpConnect::PACKET_TYPE category;
    int content_len;
    char *content;
};

#endif // TCPCONNECT_H
