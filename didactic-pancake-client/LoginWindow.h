#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QEventLoop>
#include <QEvent>
#include <QObject>
#include <string>

#include "TcpConnect.h"
#include "BaseWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public BaseWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    //模态显示函数
    std::string exec();

protected:
    //重写关闭事件
    void closeEvent(QCloseEvent *event);

private slots:
    void on_btn_login_clicked();
    void on_lbl_register_clicked();
    void checkLogin();

private:
    void initTitleBar();

    // 初始化控件;
    void initControl();

    Ui::LoginWindow *ui;

    QEventLoop *m_Loop;

    std::string m_session;

    TcpConnect *m_connect;
};

#endif // LOGINWINDOW_H
