#ifndef FRIENDBAR_H
#define FRIENDBAR_H

#include <QWidget>

#include "TcpConnect.h"
#include "FriendItem.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class FriendBar;
}
QT_END_NAMESPACE

class FriendBar : public QWidget
{
    Q_OBJECT
public:
    explicit FriendBar(QWidget *parent = nullptr);

    ~FriendBar();

    // 设置好友栏背景色;
    void setBackgroundColor(int r, int g, int b);

    //获取FriendListWidget对象指针
    FriendListWidget *getListWidget();

signals:
    //添加好友的信号
    void addFriend(QString username);
    //删除好友的信号
    void deleteFriend(QString username);
    //切换到聊天信号
    void changeToUserChat(const QString username);

protected:
    // 好友栏背景色;
    int m_colorR;
    int m_colorG;
    int m_colorB;

private slots:
    //处理从服务器获取到的好友列表
    void handleGFIpackAdd();
    //处理新增加的好友
    void handleAFIpackAdd();
    //处理新删除的好友
    void handleDFIpackAdd();

private:
    //初始化本窗口
    void initThis();
    // 初始化控件;
    void initControl();

    void paintEvent(QPaintEvent *event);

private:
    Ui::FriendBar *ui;

    //指向服务器的连接对象
    TcpConnect *m_connect;
};

#endif // FRIENDBAR_H
