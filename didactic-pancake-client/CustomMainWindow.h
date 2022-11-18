#ifndef CUSTOMMAINWINDOW_H
#define CUSTOMMAINWINDOW_H

#include <QWidget>
#include <string>

#include "BaseWindow.h"
#include "TcpConnect.h"
#include "SideBar.h"
#include "StatusBar.h"
#include "FriendBar.h"
#include "FriendInformation.h"
#include "ChatBar.h"
#include "MessageBar.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class CustomMainWindow;
}
QT_END_NAMESPACE

class CustomMainWindow : public BaseWindow
{
    Q_OBJECT

public:
    explicit CustomMainWindow(QWidget *parent = nullptr);
    ~CustomMainWindow();

protected slots:
    //点击回复按钮
    void onButtonRestoreClicked();
    //点击最大化按钮
    void onButtonMaxClicked();

protected:
    //重写关闭事件
    void closeEvent(QCloseEvent *event);

    //重写移动事件
    void moveEvent(QMoveEvent *event);

private:
    //初始化本窗口
    void initThis();
    //初始化标题栏
    void initTitleBar();
    //初始化控件
    void initControl();
    //初始化侧边栏
    void initSideBar();
    //初始化状态栏
    void initStatusBar();
    //初始化好友栏
    void initFriendBar();
    //初始化好友信息栏
    void initFriendInformationBar();
    //初始化聊天栏
    void initChatBar();
    //初始化消息栏
    void initMessageBar();

    Ui::CustomMainWindow *ui;

    //指向与服务器的连接对象
    TcpConnect *m_connect;

    //侧边栏
    SideBar *m_sideBar;

    //状态栏
    StatusBar *m_statusBar;

    //好友栏
    FriendBar *m_friendBar;

    //好友信息栏
    FriendInformation *m_friendInformation;

    //聊天栏
    ChatBar *m_chatBar;

    //消息栏
    MessageBar *m_messageBar;
};

#endif // CUSTOMMAINWINDOW_H
