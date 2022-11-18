#ifndef MESSAGEBAR_H
#define MESSAGEBAR_H

#include <QWidget>
#include <QListWidget>

#include "MessageWidget.h"
#include "TcpConnect.h"
#include "SoundPlayer.h"
#include "MessageItem.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MessageBar;
}
QT_END_NAMESPACE

class MessageBar : public QWidget
{
    Q_OBJECT
public:
    explicit MessageBar(QWidget *parent = nullptr);

    ~MessageBar();

    // 设置消息栏背景色;
    void setBackgroundColor(int r, int g, int b);

    //自己的头像更改
    void handleMyAvatarChanged();
    //好友的头像更改
    void handleFriendAvatarChanged(const QString &username);

signals:
    void messageAdd(const QString &username, const QString &content, long long l_time);
    //设置显示的聊天窗口的用户
    void setChatUserName(const QString &username);

public slots:
    //显示用户对应的对话框
    void changeToUserWidget(const QString &username);
    //隐藏用户对应的对话框
    void hideUserWidget(const QString &username);
    //删除用户对应的对话框，并清除聊天记录
    void deleteUserWidget(const QString &username);

protected:
    // 消息栏背景色;
    int m_colorR;
    int m_colorG;
    int m_colorB;

private slots:
    void handleRMApackAdd();

    void handleSMApackAdd();

    void handleROCpackAdd();

    //处理语音聊天窗口退出
    void handleVoiceChatWindowClosed(VoiceChatWindow::CLOSE_TYPE type,const QString& formatTime,const QString&username);

private:
    //初始化本窗口
    void initThis();
    // 初始化控件;
    void initControl();

    void paintEvent(QPaintEvent *event);

    //存储用户名对应的窗口
    std::map<QString, MessageWidget *> m_userWidgets;

private:
    Ui::MessageBar *ui;

    QString nowUser;

    TcpConnect *m_tcpConnect;

    SoundPlayer *m_soundNewMessage;
};

#endif // MESSAGEBAR_H
