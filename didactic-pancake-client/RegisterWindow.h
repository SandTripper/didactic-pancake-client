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

    void on_btn_register_clicked();
    void checkRegister();

private:
    void initTitleBar();

    // 初始化控件;
    void initControl();

    Ui::RegisterWindow *ui;

    QEventLoop *m_Loop;

    QString m_username;

    TcpConnect *m_connect;
};

#endif // REGISTERWINDOW_H
