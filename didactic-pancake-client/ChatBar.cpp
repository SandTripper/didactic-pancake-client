#include <QPainter>

#include "ChatBar.h"
#include "ui_ChatBar.h"

ChatBar::ChatBar(QWidget *parent) : QWidget(parent),
                                    m_colorR(0), m_colorG(0), m_colorB(0),
                                    ui(new Ui::ChatBar)
{
    ui->setupUi(this);

    initThis();
    initControl();
}

ChatBar::~ChatBar()
{
    delete ui;
}

void ChatBar::initThis()
{
    //设置窗口无边框
    setWindowFlags(Qt::FramelessWindowHint);

    connect(ui->listWidget, &ChatListWidget::itemClicked, this, &ChatBar::handleItemClicked);

    connect(ui->listWidget, &ChatListWidget::readMessageNum, this, &ChatBar::readMessageNum);

    connect(ui->listWidget, &ChatListWidget::hideUserChat, this, &ChatBar::hideUserChat);

    connect(ui->listWidget, &ChatListWidget::deleteUserChat, this, &ChatBar::deleteUserChat);
}

void ChatBar::initControl()
{
    connect(this, &ChatBar::selectUser, ui->listWidget, &ChatListWidget::selectChatItem);
}

void ChatBar::setBackgroundColor(int r, int g, int b)
{
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    // 重新绘制（调用paintEvent事件）;
    update();
}

void ChatBar::handleMessageAdd(const QString &username, const QString &content, long long l_time)
{
    ui->listWidget->setContent(username, content, l_time);
}

void ChatBar::handleAddFriend(QString username)
{
    ui->listWidget->addChatItem(username);
}

void ChatBar::handleDeleteFriend(QString username)
{
    ui->listWidget->deleteChatItem(username);
}

void ChatBar::handleItemClicked(QListWidgetItem *item)
{
    emit selectUser(dynamic_cast<ChatItem *>(ui->listWidget->itemWidget(item))->m_username);
}

void ChatBar::paintEvent(QPaintEvent *event)
{
    //设置背景色;
    QPainter painter(this);
    QPainterPath pathBack;
    pathBack.setFillRule(Qt::WindingFill);
    pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));

    //设置顶部分界线
    painter.setPen(QColor(233, 233, 233));            //设置画笔记颜色
    painter.drawLine(QLineF(0, 0, this->width(), 0)); //绘制顶部分界线

    // 当窗口最大化或者还原后，窗口高度变了，消息栏的高度应当一起改变，并更新控件位置;
    if (this->height() != this->parentWidget()->height() - 2 - 61)
    {
        this->setFixedHeight(this->parentWidget()->height() - 2 - 61);
        this->ui->listWidget->setFixedHeight(this->height() - 1);
    }

    QWidget::paintEvent(event);
}
