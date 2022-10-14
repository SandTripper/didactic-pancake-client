#ifndef ADDFRIENDWINDOW_H
#define ADDFRIENDWINDOW_H

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
    class AddFriendWindow;
}
QT_END_NAMESPACE

class AddFriendWindow : public BaseWindow
{
    Q_OBJECT

public:
    static const int NO_SEARCH_RESULT_HEIGHT = 185;

    static const int WITH_SEARCH_RESULT_HEIGHT = 301;

    explicit AddFriendWindow(QWidget *parent = 0);
    ~AddFriendWindow();
    //模态显示函数
    void exec();

protected:
    //重写关闭事件
    void closeEvent(QCloseEvent *event);

private slots:
    void checkSearch();
    void checkAddFriend();
    void on_btn_search_clicked();

    void on_btn_add_friend_clicked();

private:
    void initTitleBar();

    // 初始化控件;
    void initControl();

    Ui::AddFriendWindow *ui;

    QEventLoop *m_Loop;

    TcpConnect *m_connect;

    //暂存正在查询的用户名
    QString m_query_user_name;
};

#endif // ADDFRIENDWINDOW_H
