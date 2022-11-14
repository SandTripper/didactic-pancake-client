#include <QPainter>

#include "FriendInformation.h"
#include "ui_FriendInformation.h"
#include "FriendItem.h"
#include "Config.h"
#include "PictureViewingWindow.h"

FriendInformation::FriendInformation(QWidget *parent) : QWidget(parent),
                                                        m_colorR(0), m_colorG(0), m_colorB(0),
                                                        ui(new Ui::FriendInformation)
{
    ui->setupUi(this);

    initThis();
    initControl();
}

FriendInformation::~FriendInformation()
{
    delete ui;
}

void FriendInformation::initThis()
{
    //设置窗口无边框
    setWindowFlags(Qt::FramelessWindowHint);
}

void FriendInformation::initControl()
{
    //发消息按钮
    QString qss_btn_send_message =
        "QPushButton{background-color:rgb(7,193,96);}" //按钮颜色
        "QPushButton{color: rgb(255,255,255); }"       //文字颜色
        "QPushButton{border-radius: 3px;}"             //圆角半径
        "QPushButton:hover{background-color:rgb(56,205,127);}"
        "QPushButton:hover{color: rgb(255,255,255); }"
        "QPushButton:hover{border-radius: 3px;}"
        "QPushButton:pressed{background-color:rgb(6,173,86);}"
        "QPushButton:pressed{color: rgb(255,255,255); }"
        "QPushButton:pressed{border-radius: 3px;}"
        "QPushButton:disabled{background-color:rgb(143,217,152);}"
        "QPushButton:disabled{color: rgb(255,255,255); }"
        "QPushButton:disabled{border-radius: 3px;}";
    ui->btn_send_message->setStyleSheet(qss_btn_send_message);
    ui->btn_send_message->setCursor(QCursor(Qt::PointingHandCursor));

    //好友头像
    ui->lbl_user_avatar->setCursor(QCursor(Qt::PointingHandCursor));

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

    changeToDefault();
}

void FriendInformation::setBackgroundColor(int r, int g, int b)
{
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    // 重新绘制（调用paintEvent事件）;
    update();
}

void FriendInformation::changeToDefault()
{
    ui->lbl_user_avatar->setVisible(false);
    ui->lbl_user_name->setVisible(false);
    ui->btn_send_message->setVisible(false);
    ui->lbl_background->setVisible(true);
}

void FriendInformation::changeToInformation()
{
    ui->lbl_background->setVisible(false);
    ui->lbl_user_avatar->setVisible(true);
    ui->lbl_user_name->setVisible(true);
    ui->btn_send_message->setVisible(true);
}

void FriendInformation::updateFriend(QString username)
{
    m_username = username;
    ui->lbl_user_name->setText(username);

    QPixmap pix;
    QFile file(QApplication::applicationDirPath() + "/" + Config::loginedUserName + "/datas/avatar/original/" + username + ".png");
    if (file.open(QIODevice::ReadOnly))
    {
        pix.loadFromData(file.readAll());
        file.close();
    }
    else
    {
        pix.load(":/resource/default_avatar.png");
    }
    ui->lbl_user_avatar->setPixmap(pix);
    ui->lbl_user_avatar->setScaledContents(true);

    changeToInformation();
}

void FriendInformation::deleteFriend(QString username)
{
    if (username == m_username)
    {
        changeToDefault();
    }
}

void FriendInformation::paintEvent(QPaintEvent *event)
{
    //设置背景色;
    QPainter painter(this);
    QPainterPath pathBack;
    pathBack.setFillRule(Qt::WindingFill);
    pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));
    // 当窗口最大化或者还原后，窗口宽度变了，好友信息栏的宽度应当一起改变;
    if (this->width() != this->parentWidget()->width() - 1 - 305)
    {
        this->setFixedWidth(this->parentWidget()->width() - 1 - 305);
        this->ui->lbl_background->move((this->width() - ui->lbl_background->width()) / 2, (this->height() - ui->lbl_background->height()) / 2 - 10);
    }
    // 当窗口最大化或者还原后，窗口高度变了，好友信息栏的高度应当一起改变;
    if (this->height() != this->parentWidget()->height() - 2 - 61)
    {
        this->setFixedHeight(this->parentWidget()->height() - 2 - 61);
        this->ui->lbl_background->move((this->width() - ui->lbl_background->width()) / 2, (this->height() - ui->lbl_background->height()) / 2 - 10);
    }

    QWidget::paintEvent(event);
}

void FriendInformation::on_btn_send_message_clicked()
{
    emit changeToUserChat(ui->lbl_user_name->text());
}

void FriendInformation::on_lbl_user_avatar_clicked()
{
    PictureViewingWindow *pxw = new PictureViewingWindow(QApplication::applicationDirPath() + "/" + Config::loginedUserName + "/datas/avatar/original/" + m_username + ".png");
    //关闭时自动释放内存
    pxw->setAttribute(Qt::WA_DeleteOnClose);
    pxw->show();
    Config::openedPictureViewingWindow.emplace_back(pxw);
    connect(pxw, &PictureViewingWindow::closed, this, [=]()
            { Config::openedPictureViewingWindow.back() = nullptr; });
}
