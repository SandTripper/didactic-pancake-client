#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H

#include <QWidget>
#include <SuspendedScrollbar.h>

#include "SQLConnect.h"

class QPaintEvent;
class QPainter;
class QLabel;
class QMovie;
class AutoWrapLabel;

class MessageItem : public QWidget
{
    Q_OBJECT
public:
    explicit MessageItem(QWidget *parent = nullptr);

    enum User_Type
    {
        User_System, //系统
        User_Me,     //自己
        User_She,    //用户
        User_Time,   //时间
        User_Load,   //加载
    };
    void setTextSuccess();
    void setText(QString text, QString time, QSize allSize, User_Type userType);

    QSize getRealString(QString src);
    QSize fontRect(QString str);

    inline QString text() { return m_msg; }
    inline QString time() { return m_time; }
    inline User_Type userType() { return m_userType; }

public:
    long long message_id;

protected:
    void paintEvent(QPaintEvent *event);

private:
    QString m_msg;
    QString m_time;
    QString m_curTime;

    QSize m_allSize;
    User_Type m_userType = User_System;

    int m_kuangWidth;
    int m_textWidth;
    int m_spaceWid;
    int m_lineHeight;

    QRect m_iconLeftRect;
    QRect m_iconRightRect;
    QRect m_sanjiaoLeftRect;
    QRect m_sanjiaoRightRect;
    QRect m_kuangLeftRect;
    QRect m_kuangRightRect;
    QRect m_textLeftRect;
    QRect m_textRightRect;
    QLabel *m_lbl_avatar;
    QLabel *m_loading = Q_NULLPTR;
    QMovie *m_loadingMovie = Q_NULLPTR;
    bool m_isSending = false;

    AutoWrapLabel *m_lbl_text;
};

//////////////////////////////////////////////////////////////////////
class MessageListWidget : public SuspendedScrollBar_ListWidget
{
    Q_OBJECT
public:
    explicit MessageListWidget(QWidget *parent = nullptr);

    ~MessageListWidget() {}

    //初始化消息
    void initMessages();

    //添加一个自己的消息
    MessageItem * addMyMessage(const QString &msg);

    //添加一个对方的消息
    void addOtherMessage(const QString &msg,long long l_time);

    //添加时间信息
    void addTimeMessage(QString curMsgTime);

    //插入时间信息
    bool insertTimeMessage(QString curMsgTime,int row);

    //添加加载信息
    QListWidgetItem * addLoadMessage();

    //重写clear
    void clear();

public:
    //发送对象的用户名
    QString m_tarUserName;

signals:
    //添加信息
    void addMsg(const QString &content,long long l_time);

private:
    void initThis();

    void paintEvent(QPaintEvent *event);

    //从数据库加载消息,返回加载的消息数
    int loadMessage();

private slots:
    void onScrollBarValueChanged(int num);

private:
    //存储对应的QListWidgetItem指针和MessageItem指针
    std::vector<std::pair<QListWidgetItem *, MessageItem *>> m_items;

    //指向数据库连接对象的指针
    SQLConnect*m_sqlconn;

    //所有聊天记录的条数
    int m_totalChatRecordNum;
};
#endif // MESSAGEITEM_H
