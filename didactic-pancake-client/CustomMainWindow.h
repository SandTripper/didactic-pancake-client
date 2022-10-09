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
    explicit CustomMainWindow(std::string sessionID, QWidget *parent = 0);
    ~CustomMainWindow();

protected slots:
    void onButtonRestoreClicked();
    void onButtonMaxClicked();

private:
    void initTitleBar();
    void initSideBar();
    void initStatusBar();

    Ui::CustomMainWindow *ui;

    //与服务器的会话ID
    std::string m_sessionID;

    //指向与服务器的连接对象
    TcpConnect *m_connect;

    //侧边栏
    SideBar *m_sideBar;

    //状态栏
    StatusBar *m_statusBar;
};

#endif // CUSTOMMAINWINDOW_H
