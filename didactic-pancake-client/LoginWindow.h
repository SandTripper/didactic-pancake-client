#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QEventLoop>
#include <QEvent>
#include <QObject>

#include "TcpConnect.h"
#include "BaseWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class LoginWindow;
}
QT_END_NAMESPACE

//用以向主窗口传递参数
struct LoginData
{
    QString sessionID; //获取到的sessionID
    QString username;  //当前登录的用户名
    int x;             //关闭时登录窗口的x坐标
    int y;             //关闭时登录窗口的y坐标
};

class LoginWindow : public BaseWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    //模态显示函数
    LoginData exec();

protected:
    //重写关闭事件
    void closeEvent(QCloseEvent *event);

private slots:
    //登录按钮被按下
    void on_btn_login_clicked();
    //注册按钮被按下
    void on_lbl_register_clicked();
    //检查服务器传回的登录回复
    void checkLogin();

private:
    //初始化本窗口
    void initThis();
    //初始化标题栏
    void initTitleBar();
    // 初始化控件;
    void initControl();

    Ui::LoginWindow *ui;

    QEventLoop *m_Loop;
    //当前的sessionID
    QString m_session;
    //指向唯一的连接对象
    TcpConnect *m_connect;
};

#endif // LOGINWINDOW_H
