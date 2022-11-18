#ifndef VOICECHATWINDOW_H
#define VOICECHATWINDOW_H

#include "VoiceChat.h"

#include <QWidget>
#include <QEventLoop>
#include <QEvent>
#include <QObject>
#include <string>
#include <QByteArray>

#include "TcpConnect.h"
#include "BaseWindow.h"
#include "SoundPlayer.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class VoiceChatWindow;
}
QT_END_NAMESPACE

class VoiceChatWindow : public BaseWindow
{
    Q_OBJECT

public:

    enum MY_TYPE
    {
        WAITING_FOR_ACCEPT,
        CHOOSE_ACCEPT_OR_NOT,
        CHATTING,
    };

    enum CLOSE_TYPE
    {
        NORMAL_CALL,
        FRIEND_OFFLINE,
        FRIEND_CANCEL,
        FRIEND_REJECT,
        FRIEND_BUSY,
        CANCEL,
        REJECT,
    };

    explicit VoiceChatWindow(const QString&targetUserName,MY_TYPE type,QWidget *parent = nullptr);

    ~VoiceChatWindow();
    //模态显示函数
    void exec();

    //重写show函数
    void show();

signals:
    void closed(CLOSE_TYPE type,const QString&formatTime);

private slots:
    void on_btn_accept_clicked();

    //处理开始语音聊天
    void handleAOCpackAdd();

    //处理发起语音聊天状态
    void handleSOCpackAdd();

    //处理结束语音聊天状态
    void handleDOCpackAdd();

    void on_btn_reject_clicked();

    void on_btn_cancel_clicked();

    void on_btn_hang_up_clicked();

    void on_btn_close_clicked();

private:
    //初始化本窗口
    void initThis();
    //初始化标题栏
    void initTitleBar();
    // 初始化控件;
    void initControl();
    //定时处理时间变化
    void tick(int tot);
    //将状态切换至聊天
    void changeTypeToChatting();
    //持续时间格式化
    QString formatTime(uint times);


private:
    Ui::VoiceChatWindow *ui;

    QEventLoop *m_Loop;

    TcpConnect* m_tcpConnect;

    //聊天对象用户名
    QString m_targetUserName;

    MY_TYPE m_type;

    QPixmap m_wait_ball_types_pix[3];
    int m_wait_ball_types[3][3];

    int m_wait_ball_type_cnt;

    VoiceChat*m_voiceChat;

    SoundPlayer *m_soundHangUp;

    SoundPlayer *m_soundVoiceChat;

    uint m_startTime;

    uint m_chatTime;
};

#endif // VOICECHATWINDOW_H
