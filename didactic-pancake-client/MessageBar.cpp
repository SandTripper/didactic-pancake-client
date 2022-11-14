#include <QPainter>

#include "MessageBar.h"
#include "ui_MessageBar.h"
#include "FriendItem.h"

MessageBar::MessageBar(QWidget *parent) : QWidget(parent),
                                          m_colorR(0), m_colorG(0), m_colorB(0),
                                          ui(new Ui::MessageBar),
                                          nowUser(""),
                                          m_connect(TcpConnect::getInstance()),
                                          m_soundPlayer(new SoundPlayer)
{
    ui->setupUi(this);

    initThis();
    initControl();
}

MessageBar::~MessageBar()
{
    delete m_soundPlayer;
    delete ui;
}

void MessageBar::initThis()
{
    //设置窗口无边框
    setWindowFlags(Qt::FramelessWindowHint);

    connect(m_connect, &TcpConnect::SMApackAdd, this, &MessageBar::handleSMApackAdd);
    connect(m_connect, &TcpConnect::RMApackAdd, this, &MessageBar::handleRMApackAdd);
}

void MessageBar::initControl()
{
    //设置背景图片的透明度
    QPixmap pix1_(":/resource/pancake2.png");
    QPixmap temp(pix1_.size());
    temp.fill(Qt::transparent);
    QPainter p1(&temp);
    p1.setCompositionMode(QPainter::CompositionMode_Source);
    p1.drawPixmap(0, 0, pix1_);
    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    //根据QColor中第四个参数设置透明度，此处position的取值范围是0～255
    p1.fillRect(temp.rect(), QColor(0, 0, 0, 50));
    p1.end();
    pix1_ = temp;
    ui->lbl_background->setPixmap(pix1_);
    ui->lbl_background->setScaledContents(true);
}

void MessageBar::setBackgroundColor(int r, int g, int b)
{
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    // 重新绘制（调用paintEvent事件）;
    update();
}

void MessageBar::handleMyAvatarChanged()
{
    if (nowUser != "")
    {
        m_userWidgets[nowUser]->updateMyAvatar();
    }
}

void MessageBar::handleFriendAvatarChanged(const QString &username)
{
    if (nowUser != "" && nowUser == username)
    {
        m_userWidgets[nowUser]->updateTargetAvatar();
    }
}

void MessageBar::hideUserWidget(const QString &username)
{
    if (nowUser == username) //当前显示的是目标窗口
    {
        emit setChatUserName("");
    }

    if (m_userWidgets.find(username) == m_userWidgets.end()) //不存在用户对话框
    {
        return;
    }

    m_userWidgets[username]->getListWidget()->clear();
    m_userWidgets[username]->hide();

    if (nowUser == username) //当前显示的不是目标
    {
        nowUser = "";
    }
}

void MessageBar::changeToUserWidget(const QString &username)
{
    emit setChatUserName(username);

    if (m_userWidgets.find(username) == m_userWidgets.end()) //不存在用户对话框，创建并初始化
    {
        MessageWidget *widget = new MessageWidget(username, this);
        connect(widget, &MessageWidget::messageAdd, this, &MessageBar::messageAdd);
        m_userWidgets[username] = widget;
    }

    if (nowUser != username) //当前显示的不是目标
    {
        if (nowUser != "")
        {
            m_userWidgets[nowUser]->getListWidget()->clear();
            m_userWidgets[nowUser]->hide();
        }
        nowUser = username;
        m_userWidgets[username]->show();
        m_userWidgets[username]->initMessages();
    }
}

void MessageBar::deleteUserWidget(const QString &username)
{
    //数据库删除聊天记录
    SQLConnect::getInstance()->deleteChatRecord(username);

    if (nowUser == username) //当前显示的是目标窗口
    {
        emit setChatUserName("");
        nowUser = "";
    }

    auto it = m_userWidgets.find(username);
    if (it != m_userWidgets.end()) //存在用户对话框，删除
    {
        delete it->second;
        m_userWidgets.erase(it);
    }
}

void MessageBar::handleRMApackAdd()
{
    for (const auto &data : m_connect->vec[TcpConnect::RMA])
    {
        if (data.content_len == 0)
            continue;

        QString username = "";
        QString time = "";
        QString content = "";

        int lineCnt = 0;

        for (int i = 0; i < data.content_len; i++)
        {
            if (data.content[i] == '\r' && data.content[i + 1] == '\n')
            {
                ++lineCnt;
                if (lineCnt >= 2)
                {
                    content = QString(data.content + i + 2);
                    break;
                }
                ++i;
                continue;
            }
            if (lineCnt == 0)
            {
                username += data.content[i];
            }
            else if (lineCnt == 1)
            {
                time += data.content[i];
            }
        }

        content.remove(content.length() - 2, 2);

        if (m_userWidgets.find(username) == m_userWidgets.end()) //不存在该用户窗口
        {
            MessageWidget *widget = new MessageWidget(username, this);
            connect(widget, &MessageWidget::messageAdd, this, &MessageBar::messageAdd);
            m_userWidgets[username] = widget;
        }
        m_userWidgets[username]->getListWidget()->addOtherMessage(content, time.toLongLong());

        //新消息声音提示
        m_soundPlayer->playNewMessageEffect();
    }
    m_connect->vec[TcpConnect::RMA].clear();
}

void MessageBar::handleSMApackAdd()
{
    for (const auto &data : m_connect->vec[TcpConnect::SMA])
    {
        if (data.content_len == 0)
            continue;
        QString msg_id = "";
        QString time = "";
        for (int i = 0; i < data.content_len; i++)
        {
            if (data.content[i] == '\r' && data.content[i + 1] == '\n')
            {

                time = QString(data.content + i + 2);
                break;
            }
            msg_id += data.content[i];
        }
        time.remove(time.length() - 2, 2);
        MessageWidget::messageHasSend(msg_id.toLongLong());
    }
    m_connect->vec[TcpConnect::SMA].clear();
}

void MessageBar::paintEvent(QPaintEvent *event)
{
    //设置背景色;
    QPainter painter(this);
    QPainterPath pathBack;
    pathBack.setFillRule(Qt::WindingFill);
    pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));
    // 当窗口最大化或者还原后，窗口宽度变了，消息栏的宽度应当一起改变;
    if (this->width() != this->parentWidget()->width() - 1 - 305)
    {
        this->setFixedWidth(this->parentWidget()->width() - 1 - 305);
        this->ui->lbl_background->move((this->width() - ui->lbl_background->width()) / 2, (this->height() - ui->lbl_background->height()) / 2 - 10);
    }
    // 当窗口最大化或者还原后，窗口高度变了，消息栏的高度应当一起改变;
    if (this->height() != this->parentWidget()->height() - 2 - 61)
    {
        this->setFixedHeight(this->parentWidget()->height() - 2 - 61);
        this->ui->lbl_background->move((this->width() - ui->lbl_background->width()) / 2, (this->height() - ui->lbl_background->height()) / 2 - 10);
    }

    QWidget::paintEvent(event);
}
