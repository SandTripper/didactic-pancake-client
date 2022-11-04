#ifndef FRIENDITEM_H
#define FRIENDITEM_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>

#include "SuspendedScrollbar.h"
#include "TcpConnect.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class FriendItem;
}
QT_END_NAMESPACE

class FriendItem : public QWidget
{
    Q_OBJECT
public:
    explicit FriendItem(QWidget *parent = nullptr, const QString &username = "");

    ~FriendItem();

public:
    QString m_username;

signals:
    //切换到用户聊天信号
    void changeToUserChat(const QString &username);

private slots:
    void changeToSendMessage();

    void deleteFriend();

private:
    //初始化本窗口
    void initThis();
    //初始化控件;
    void initControl();

    void paintEvent(QPaintEvent *event);
    //重写右键菜单事件
    void contextMenuEvent(QContextMenuEvent *event);

private:
    Ui::FriendItem *ui;

    QListWidgetItem *m_item;

    //右键菜单
    QMenu *m_contextMenu;

    //右键菜单的两个动作
    QAction *m_sendMessageAction;
    QAction *m_deleteFriendAction;
    //指向与服务器的连接对象
    TcpConnect *m_connect;
};
//////////////////////////////////////////////////////////////////////
class FriendListWidget : public SuspendedScrollBar_ListWidget
{
    Q_OBJECT
public:
    explicit FriendListWidget(QWidget *parent = nullptr);

    ~FriendListWidget() {}

    //添加一个好友框
    void addFriendItem(const QString &username);

    //删除一个好友框
    void deleteFriendItem(const QString &username);

signals:
    void chooseFriend(QString username);

    void changeToUserChat(const QString &username);

private slots:
    void handleItemClicked(QListWidgetItem *item);

private:
    void initThis();

private:
    //存储用户名对应的QListWidgetItem指针和FriendItem指针
    std::vector<std::pair<QListWidgetItem *, FriendItem *>> m_items;
};

#endif // FRIENDITEM_H
