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
    //没有搜索到结果时的高度
    static const int NO_SEARCH_RESULT_HEIGHT = 185;

    //搜索到结果后的高度
    static const int WITH_SEARCH_RESULT_HEIGHT = 301;

    explicit AddFriendWindow(QWidget *parent = nullptr);

    ~AddFriendWindow();
    //模态显示函数
    void exec();

protected:
    //重写关闭事件
    void closeEvent(QCloseEvent *event);

private slots:
    //处理服务器对搜索请求的回复
    void checkSearch();
    //处理服务器对添加好友请求的回复
    void checkAddFriend();
    //按下搜索按钮
    void on_btn_search_clicked();
    //按下添加好友按钮
    void on_btn_add_friend_clicked();

private:
    //初始化本窗口
    void initThis();
    //初始化标题栏
    void initTitleBar();
    // 初始化控件;
    void initControl();

    Ui::AddFriendWindow *ui;

    QEventLoop *m_Loop;

    //指向服务器的连接对象
    TcpConnect *m_connect;

    //暂存正在查询的用户名
    QString m_query_user_name;
};

#endif // ADDFRIENDWINDOW_H
