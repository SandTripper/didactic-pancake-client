#ifndef FRIENDINFORMATION_H
#define FRIENDINFORMATION_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class FriendInformation;
}
QT_END_NAMESPACE

class FriendInformation : public QWidget
{
    Q_OBJECT
public:
    explicit FriendInformation(QWidget *parent = nullptr);

    ~FriendInformation();

    // 设置好友信息栏背景色;
    void setBackgroundColor(int r, int g, int b);

    //切换到默认界面
    void changeToDefault();

    //切换到信息界面
    void changeToInformation();

public slots:
    //更新显示的好友信息
    void updateFriend(QString username);

    //处理删除好友的逻辑
    void deleteFriend(QString username);

signals:
    //切换到用户聊天信号
    void changeToUserChat(QString username);

protected:
    // 好友信息栏背景色;
    int m_colorR;
    int m_colorG;
    int m_colorB;

private slots:
    void on_btn_send_message_clicked();

private:
    //初始化本窗口
    void initThis();
    // 初始化控件;
    void initControl();

    void paintEvent(QPaintEvent *event);

private:
    Ui::FriendInformation *ui;
};

#endif // FRIENDINFORMATION_H
