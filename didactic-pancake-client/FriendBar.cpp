#include <QPainter>

#include "FriendBar.h"
#include "ui_FriendBar.h"

FriendBar::FriendBar(QWidget *parent) : QWidget(parent),
                                        m_colorR(0), m_colorG(0), m_colorB(0),
                                        ui(new Ui::FriendBar),
                                        m_connect(TcpConnect::getInstance())
{
    ui->setupUi(this);

    initThis();
    initControl();
}

FriendBar::~FriendBar()
{
    delete ui;
}

void FriendBar::initThis()
{
    //设置窗口无边框
    setWindowFlags(Qt::FramelessWindowHint);

    connect(m_connect, &TcpConnect::GFIpackAdd, this, &FriendBar::handleGFIpackAdd);
    connect(m_connect, &TcpConnect::AFIpackAdd, this, &FriendBar::handleAFIpackAdd);
    connect(m_connect, &TcpConnect::DFIpackAdd, this, &FriendBar::handleDFIpackAdd);
    connect(ui->listWidget, &FriendListWidget::changeToUserChat, this, &FriendBar::changeToUserChat);
}

void FriendBar::initControl()
{
}

void FriendBar::setBackgroundColor(int r, int g, int b)
{
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    // 重新绘制（调用paintEvent事件）;
    update();
}

FriendListWidget *FriendBar::getListWidget()
{
    return ui->listWidget;
}

void FriendBar::handleFriendAvatarChanged(const QString &username)
{
    ui->listWidget->updateFriendItemAvatar(username);
}

void FriendBar::handleGFIpackAdd()
{
    for (const auto &data : m_connect->vec[TcpConnect::GFI])
    {
        if (data.content_len == 0)
            continue;
        //解析好友列表数据

        ui->listWidget->clear();

        QString text = "";
        for (int i = 0; i < data.content_len - 1; i++)
        {
            if (data.content[i] == '\r' && data.content[i + 1] == '\n')
            {
                ui->listWidget->addFriendItem(text);
                emit addFriend(text);
                text = "";
                i++;
                continue;
            }
            text += data.content[i];
        }
    }
    m_connect->vec[TcpConnect::GFI].clear();
}

void FriendBar::handleAFIpackAdd()
{
    for (const auto &data : m_connect->vec[TcpConnect::AFI])
    {

        if (data.content_len == 0)
            continue;

        //解析添加的好友列表数据
        QString text = "";
        for (int i = 0; i < data.content_len - 1; i++)
        {
            if (data.content[i] == '\r' && data.content[i + 1] == '\n')
            {
                ui->listWidget->addFriendItem(text);
                emit addFriend(text);
                break;
            }
            text += data.content[i];
        }
    }
    m_connect->vec[TcpConnect::AFI].clear();
}

void FriendBar::handleDFIpackAdd()
{
    for (const auto &data : m_connect->vec[TcpConnect::DFI])
    {

        if (data.content_len == 0)
            continue;

        //解析删除的好友列表数据
        QString text = "";
        for (int i = 0; i < data.content_len - 1; i++)
        {
            if (data.content[i] == '\r' && data.content[i + 1] == '\n')
            {
                ui->listWidget->deleteFriendItem(text);
                emit deleteFriend(text);
                break;
            }
            text += data.content[i];
        }
    }
    m_connect->vec[TcpConnect::DFI].clear();
}

void FriendBar::paintEvent(QPaintEvent *event)
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

    // 当窗口最大化或者还原后，窗口高度变了，好友栏的高度应当一起改变;
    if (this->height() != this->parentWidget()->height() - 2 - 61)
    {
        this->setFixedHeight(this->parentWidget()->height() - 2 - 61);
        this->ui->listWidget->setFixedHeight(this->height() - 1);
    }
    QWidget::paintEvent(event);
}
