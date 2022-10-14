#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>

#include "FriendRequestsWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class StatusBar;
}
QT_END_NAMESPACE

class StatusBar : public QWidget
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = nullptr);

    ~StatusBar();

    // 设置状态栏背景色;
    void setBackgroundColor(int r, int g, int b);

    //显示好友申请按钮上的红点
    void showRedPoint();

    //隐藏好友申请按钮上的红点
    void hideRedPoint();

public:
    //是否是最大化窗口
    bool m_isMaxWindow;

public slots:

protected:
    // 状态栏背景色;
    int m_colorR;
    int m_colorG;
    int m_colorB;

private slots:
    void on_btn_add_friend_clicked();

    void on_btn_process_friend_requests_clicked();

private:
    // 初始化控件;
    void initControl();

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    // 移动窗口的变量;
    bool m_isPressed;
    QPoint m_startMovePos;

    //好友申请窗口
    FriendRequestsWindow* m_friend_requests_window;

    Ui::StatusBar *ui;

    TcpConnect* m_connect;


};

#endif // STATUSBAR_H
