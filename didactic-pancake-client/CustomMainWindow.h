#ifndef CUSTOMMAINWINDOW_H
#define CUSTOMMAINWINDOW_H

#include <QWidget>
#include <string>

#include "BaseWindow.h"
#include "TcpConnect.h"
#include "SideBar.h"
#include "StatusBar.h"

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
    explicit CustomMainWindow(QString sessionID, QString username, QWidget *parent = 0);
    ~CustomMainWindow();

protected slots:
    //点击回复按钮
    void onButtonRestoreClicked();
    //点击最大化按钮
    void onButtonMaxClicked();

private:
    //初始化本窗口
    void initThis();
    //初始化标题栏
    void initTitleBar();
    //初始化侧边栏
    void initSideBar();
    //初始化状态栏
    void initStatusBar();

    Ui::CustomMainWindow *ui;

    //与服务器的会话ID
    QString m_sessionID;

    //指向与服务器的连接对象
    TcpConnect *m_connect;

    //侧边栏
    SideBar *m_sideBar;

    //状态栏
    StatusBar *m_statusBar;
};

#endif // CUSTOMMAINWINDOW_H
