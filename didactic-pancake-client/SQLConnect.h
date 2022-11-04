#ifndef SQLCONNECT_H
#define SQLCONNECT_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <vector>
#include <tuple>

class SQLConnect
{
public:
    //返回全局唯一实例
    static SQLConnect *getInstance();

    //返回一个vector容器，包含从fromNum开始最后num条与user的聊天记录，其中tuple存储的分别为：聊天记录ID，是否为自己的消息，消息的时间戳，消息的内容
    std::vector<std::tuple<long long, int, long long, QString, int>> getNlinesChatRecord(const QString &user, int fromNum, int num);

    //添加一条聊天记录，参数：聊天记录ID，聊天对象，是否为自己的消息，消息的时间戳，消息的内容
    void addChatRecord(long long id, const QString &user, int isMine, long long timestp, const QString &content, int isSend);

    //初始化连接与表
    void initUserDataConnect(const QString &username);

    //修改某条消息的发送状态
    void setChatRecordisSend(long long id, int isSend);

    //获取与username的聊天记录条数
    int getUserChatRecordNumber(const QString &username);

    //删除与username的聊天记录
    void deleteChatRecord(const QString &username);

    //返回一个vector容器，包含上次关闭软件时所有聊天窗口，其中tuple存储的分别为：对方用户名，最后一次消息的时间戳，未读消息数，最后一次消息的内容,是否显示
    std::vector<std::tuple<QString, long long, int, QString, int>> getChatItem();

    //返回所有未读消息的总数
    int getAllunReadNum();

    //添加聊天窗口
    void addChatItem(const QString &username, long long lastTime, int unreadNum, const QString &content, int isSend);

    void setChatItem(const QString &username, long long lastTime, int unreadNum, const QString &content, int isSend);

    void deleteChatItem(const QString &username);

private:
    SQLConnect();

private:
    QSqlDatabase m_database;
};

#endif // SQLCONNECT_H
