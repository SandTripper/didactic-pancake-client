#ifndef FRIENDREQUESTSWINDOW_H
#define FRIENDREQUESTSWINDOW_H

#include <QWidget>
#include <QEventLoop>
#include <QEvent>
#include <QObject>
#include <string>

#include "TcpConnect.h"
#include "BaseWindow.h"
#include "FriendRequsetsItem.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class FriendRequestsWindow;
}
QT_END_NAMESPACE

class FriendRequestsWindow : public BaseWindow
{
    Q_OBJECT

public:

    explicit FriendRequestsWindow(QWidget *parent = 0);
    ~FriendRequestsWindow();
    //模态显示函数
    void exec();



protected:
    //重写关闭事件
    void closeEvent(QCloseEvent *event);

private slots:
    void handle_new_friend_request();

private:
    void initTitleBar();

    // 初始化控件;
    void initControl();

    Ui::FriendRequestsWindow *ui;

    QEventLoop *m_Loop;

    TcpConnect *m_connect;

};

#endif // FRIENDREQUESTSWINDOW_H
