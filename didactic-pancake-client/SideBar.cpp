#include "SideBar.h"
#include "ui_SideBar.h"

#include <QPainter>
#include <QMouseEvent>

#include "SQLConnect.h"
#include "SelectNewAvatarWindow.h"
#include "PictureViewingWindow.h"
#include "Config.h"

SideBar::SideBar(QWidget *parent) : QWidget(parent),
                                    m_isMaxWindow(false),
                                    m_colorR(0), m_colorG(0), m_colorB(0),
                                    ui(new Ui::SideBar),
                                    m_unreadNum(SQLConnect::getInstance()->getAllunReadNum()),
                                    m_changeAvatarAction(new QAction("更换头像"))
{
    ui->setupUi(this);

    initThis();
    initControl();
}

SideBar::~SideBar()
{
    emit closed();
    delete m_changeAvatarAction;
    delete ui;
}

void SideBar::initThis()
{
    //设置窗口无边框
    setWindowFlags(Qt::FramelessWindowHint);

    //默认选中聊天界面
    on_btn_change_to_chat_clicked();

    ui->lbl_redpoint->setNum(m_unreadNum);

    connect(m_changeAvatarAction, &QAction::triggered, this, &SideBar::on_change_avatar_triggered);
}

void SideBar::initControl()
{
    //侧边栏单选按钮
    QString qss_btn_change_to_chat =
        "QPushButton{border-image: url(:/resource/btn_change_to_chat_normal.png)}"          //默认
        "QPushButton:hover{border-image: url(:/resource/btn_change_to_chat_hover.png)}"     //鼠标hover
        "QPushButton:pressed{border-image: url(:/resource/btn_change_to_chat_press.png)}"   //鼠标点击
        "QPushButton:disabled{border-image: url(:/resource/btn_change_to_chat_press.png)}"; //不可用
    QString qss_btn_change_to_friend =
        "QPushButton{border-image: url(:/resource/btn_change_to_friend_normal.png)}"          //默认
        "QPushButton:hover{border-image: url(:/resource/btn_change_to_friend_hover.png)}"     //鼠标hover
        "QPushButton:pressed{border-image: url(:/resource/btn_change_to_friend_press.png)}"   //鼠标点击
        "QPushButton:disabled{border-image: url(:/resource/btn_change_to_friend_press.png)}"; //不可用

    ui->btn_change_to_chat->setStyleSheet(qss_btn_change_to_chat);
    ui->btn_change_to_friend->setStyleSheet(qss_btn_change_to_friend);

    ui->btn_change_to_chat->setToolTip(QStringLiteral("聊天"));
    ui->btn_change_to_friend->setToolTip(QStringLiteral("通讯录"));

    ui->btn_change_to_chat->setCursor(QCursor(Qt::PointingHandCursor));
    ui->btn_change_to_friend->setCursor(QCursor(Qt::PointingHandCursor));

    QPixmap pix;
    QFile file(QApplication::applicationDirPath() + "/" + Config::loginedUserName + "/datas/avatar/original/" + Config::loginedUserName + ".png");
    if (file.open(QIODevice::ReadOnly))
    {
        pix.loadFromData(file.readAll());
        file.close();
    }
    else
    {
        pix.load(":/resource/default_avatar.png");
    }
    ui->lbl_user_avatar->setPixmap(pix.scaled(ui->lbl_user_avatar->width(), ui->lbl_user_avatar->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->lbl_user_avatar->setScaledContents(true);
    ui->lbl_user_avatar->setCursor(QCursor(Qt::PointingHandCursor));
    ui->lbl_user_avatar->getContextMenu()->addAction(m_changeAvatarAction);

    //设置消息红点大于99时显示99
    ui->lbl_redpoint->setPointType(RedPoint::SHOW99WHENBIGGER);
}

void SideBar::updateAvatar()
{
    QPixmap pix;
    QFile file(QApplication::applicationDirPath() + "/" + Config::loginedUserName + "/datas/avatar/original/" + Config::loginedUserName + ".png");
    if (file.open(QIODevice::ReadOnly))
    {
        pix.loadFromData(file.readAll());
        file.close();
    }
    else
    {
        pix.load(":/resource/default_avatar.png");
    }
    ui->lbl_user_avatar->setPixmap(pix.scaled(ui->lbl_user_avatar->width(), ui->lbl_user_avatar->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void SideBar::setBackgroundColor(int r, int g, int b)
{
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    // 重新绘制（调用paintEvent事件）;
    update();
}

void SideBar::paintEvent(QPaintEvent *event)
{
    //设置背景色;
    QPainter painter(this);
    QPainterPath pathBack;
    pathBack.setFillRule(Qt::WindingFill);
    pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));

    // 当窗口最大化或者还原后，窗口高度变了，侧边栏的高度应当一起改变;
    if (this->height() != this->parentWidget()->height() - 2)
    {
        this->setFixedHeight(this->parentWidget()->height() - 2);
    }
    QWidget::paintEvent(event);
}

void SideBar::handleReadMessageNum(int num)
{
    m_unreadNum -= num;
    ui->lbl_redpoint->setNum(m_unreadNum);
}

// 以下通过mousePressEvent、mouseMoveEvent、mouseReleaseEvent三个事件实现了鼠标拖动侧边栏栏移动窗口的效果;
void SideBar::mousePressEvent(QMouseEvent *event)
{

    // 在窗口最大化时禁止拖动窗口;
    if (!m_isMaxWindow)
    {
        m_isPressed = true;
        m_startMovePos = event->globalPos();
    }

    return QWidget::mousePressEvent(event);
}

void SideBar::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPressed)
    {
        QPoint movePoint = event->globalPos() - m_startMovePos;
        QPoint widgetPos = this->parentWidget()->pos();
        m_startMovePos = event->globalPos();
        this->parentWidget()->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());
    }
    return QWidget::mouseMoveEvent(event);
}

void SideBar::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
    return QWidget::mouseReleaseEvent(event);
}

void SideBar::on_change_avatar_triggered()
{
    SelectNewAvatarWindow snaw;
    connect(&snaw, &SelectNewAvatarWindow::myAvatarChanged, this, [=]()
            {
        updateAvatar();
        emit myAvatarChanged(); });
    snaw.setWindowModality(Qt::ApplicationModal);
    snaw.exec();
}
void SideBar::on_btn_change_to_chat_clicked()
{
    //通过设置其他按钮是否可用实现单选效果
    ui->btn_change_to_friend->setDisabled(false);
    ui->btn_change_to_chat->setDisabled(true);

    emit changeToChat();
}

void SideBar::on_btn_change_to_friend_clicked()
{
    //通过设置其他按钮是否可用实现单选效果
    ui->btn_change_to_chat->setDisabled(false);
    ui->btn_change_to_friend->setDisabled(true);

    emit changeToFriend();
}

void SideBar::on_lbl_user_avatar_clicked()
{
    PictureViewingWindow *pxw = new PictureViewingWindow(QApplication::applicationDirPath() + "/" + Config::loginedUserName + "/datas/avatar/original/" + Config::loginedUserName + ".png");
    //关闭时自动释放内存
    pxw->setAttribute(Qt::WA_DeleteOnClose);
    pxw->show();
    Config::openedPictureViewingWindow.emplace_back(pxw);
    connect(pxw, &PictureViewingWindow::closed, this, [=]()
            { Config::openedPictureViewingWindow.back() = nullptr; });
}
