#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>

#include "MessageItem.h"
#include "TcpConnect.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MessageWidget;
}
QT_END_NAMESPACE

class MessageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MessageWidget(QString username, QWidget *parent = nullptr);

    ~MessageWidget();

    // 设置消息窗口背景色;
    void setBackgroundColor(int r, int g, int b);

    MessageListWidget *getListWidget();

    //初始化聊天记录
    void initMessages();

    static void messageHasSend(long long id);

    static std::map<long long, MessageItem *> getSendingMessage();
    static void setSendingMessage(const std::map<long long, MessageItem *> &sendingMessage);

    //更新自己的头像
    void updateMyAvatar();

    //更新聊天对象的头像
    void updateTargetAvatar();

public slots:

signals:
    void messageAdd(const QString &username, const QString &content, long long l_time);

protected:
    // 消息窗口背景色;
    int m_colorR;
    int m_colorG;
    int m_colorB;

private slots:
    void on_btn_send_clicked();

private:
    //初始化本窗口
    void initThis();
    // 初始化控件;
    void initControl();

    void paintEvent(QPaintEvent *event);

private:
    Ui::MessageWidget *ui;

    TcpConnect *m_connect;

    QString m_tarUserName;

    //存储发送中的消息
    static std::map<long long, MessageItem *> m_sendingMessage;
};

#endif // MESSAGEWIDGET_H
