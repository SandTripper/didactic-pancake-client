#ifndef CHATBAR_H
#define CHATBAR_H

#include <QWidget>

#include "ChatItem.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class ChatBar;
}
QT_END_NAMESPACE

class ChatBar : public QWidget
{
    Q_OBJECT
public:
    explicit ChatBar(QWidget *parent = nullptr);

    ~ChatBar();

    // 设置消息栏背景色;
    void setBackgroundColor(int r, int g, int b);

signals:
    //选择聊天信号
    void selectUser(QString username);
    //增加的已读消息的数量
    void readMessageNum(int num);
    //隐藏用户聊天
    void hideUserChat(const QString &username);
    //删除用户聊天
    void deleteUserChat(const QString &username);

public slots:
    //处理新增信息
    void handleMessageAdd(const QString &username, const QString &content, long long l_time);
    //处理添加好友
    void handleAddFriend(QString username);
    //处理删除好友
    void handleDeleteFriend(QString username);

protected:
    // 好友栏背景色;
    int m_colorR;
    int m_colorG;
    int m_colorB;

private slots:
    //处理listWidget控件的选择信号
    void handleItemClicked(QListWidgetItem *item);

private:
    //初始化本窗口
    void initThis();
    // 初始化控件;
    void initControl();

    void paintEvent(QPaintEvent *event);

private:
    Ui::ChatBar *ui;
};

#endif // CHATBAR_H
