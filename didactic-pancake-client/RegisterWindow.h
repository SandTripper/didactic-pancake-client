#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

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
    class RegisterWindow;
}
QT_END_NAMESPACE

class RegisterWindow : public BaseWindow
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = 0);
    ~RegisterWindow();
    //模态显示函数
    QString exec();

protected:
    //重写关闭事件
    void closeEvent(QCloseEvent *event);

private slots:
    //注册按钮被按下
    void on_btn_register_clicked();
    //检查服务器的注册回复
    void checkRegister();

private:
    //初始化本窗口
    void initThis();
    //初始化标题栏
    void initTitleBar();
    // 初始化控件;
    void initControl();

    Ui::RegisterWindow *ui;

    QEventLoop *m_Loop;
    //存储注册成功的用户名
    QString m_username;
    //指向唯一的连接对象
    TcpConnect *m_connect;
};

#endif // REGISTERWINDOW_H
