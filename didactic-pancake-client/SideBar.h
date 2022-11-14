#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class SideBar;
}
QT_END_NAMESPACE

class SideBar : public QWidget
{
    Q_OBJECT
public:
    explicit SideBar(QWidget *parent = nullptr);

    ~SideBar();

    // 设置侧边栏背景色;
    void setBackgroundColor(int r, int g, int b);

public:
    //是否是最大化窗口
    bool m_isMaxWindow;

public slots:
    //处理新增已读消息
    void handleReadMessageNum(int num);

    void on_btn_change_to_chat_clicked();

    void on_btn_change_to_friend_clicked();

signals:
    //切换到聊天界面
    void changeToChat();
    //切换到好友界面
    void changeToFriend();
    //关闭信号
    void closed();

    //用户头像更改
    void myAvatarChanged();

protected:
    // 侧边栏背景色;
    int m_colorR;
    int m_colorG;
    int m_colorB;

private:
    //初始化本窗口
    void initThis();
    // 初始化控件;
    void initControl();

    //更新用户头像
    void updateAvatar();

    //重写paintEvent事件
    void paintEvent(QPaintEvent *event);

    //重写以下事件以实现拖动窗口的功能
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_change_avatar_triggered();
    void on_lbl_user_avatar_clicked();

private:
    // 移动窗口的变量;
    bool m_isPressed;

    QPoint m_startMovePos;

    Ui::SideBar *ui;

    //未读消息数目
    int m_unreadNum;

    //头像右键的更换头像动作
    QAction *m_changeAvatarAction;
};

#endif // SIDEBAR_H
