#ifndef CHATITEM_H
#define CHATITEM_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>

#include "SuspendedScrollbar.h"
#include "TcpConnect.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class ChatItem;
}
QT_END_NAMESPACE

class ChatItem : public QWidget
{
    Q_OBJECT
public:
    explicit ChatItem(QWidget *parent = nullptr, const QString &username = "");

    ChatItem(QWidget *parent, const QString &username, long long lastTime, int unreadNum, const QString &content);

    ChatItem(const ChatItem &other);

    ~ChatItem();

    //设置预览消息内容
    void setContent(const QString &content, long long l_time);

    //增加未读消息数
    void addUnreadNum();

    //清除未读消息数
    void clearUnreadNum();

    //更新头像图片
    void updateAvatar();

public:
    QString m_username;

    long long m_lastTime;

    //未读的消息数
    int m_unreadNum;

    //预览消息内容
    QString m_content;

signals:
    //隐藏用户聊天
    void hideUserChat(const QString &username);
    //删除用户聊天
    void deleteUserChat(const QString &username);

private:
    //初始化本窗口
    void initThis();
    //初始化控件;
    void initControl();

    void paintEvent(QPaintEvent *event);
    //重写右键菜单事件
    void contextMenuEvent(QContextMenuEvent *event);

private:
    Ui::ChatItem *ui;

    //右键菜单
    QMenu *m_contextMenu;

    //右键菜单的不显示聊天动作
    QAction *m_hideChatAction;
    //右键菜单的删除聊天动作
    QAction *m_deleteChatAction;

    //指向与服务器的连接对象
    TcpConnect *m_connect;
};
//////////////////////////////////////////////////////////////////////
class ChatListWidget : public SuspendedScrollBar_ListWidget
{
    Q_OBJECT
public:
    explicit ChatListWidget(QWidget *parent = nullptr);

    ~ChatListWidget() {}

    //设置用户的消息预览
    void setContent(const QString &username, const QString &content, long long l_time);

    //添加一个聊天框
    void addChatItem(const QString &username);

    //显示一个聊天框
    void showChatItem(const QString &username);

    //选择一个聊天框
    void selectChatItem(const QString &username);

    //隐藏一个聊天框
    void hideChatItem(const QString &username);

    //删除一个聊天框
    void deleteChatItem(const QString &username);

    //更新用户的头像
    void updateChatItemAvatar(const QString &username);

signals:
    void chooseChat(QString username);
    //增加的已读消息的数量
    void readMessageNum(int num);
    //隐藏用户聊天
    void hideUserChat(const QString &username);
    //删除用户聊天
    void deleteUserChat(const QString &username);

private slots:
    void handleItemClicked(QListWidgetItem *item);

private:
    void initThis();

private:
    //存储用户名对应的QListWidgetItem指针和ChatItem指针
    std::vector<std::pair<QListWidgetItem *, ChatItem *>> m_items;

    //当前登录的用户名
    QString m_loginedUserName;
};

#endif // CHATITEM_H
