#include "StatusBar.h"
#include "ui_StatusBar.h"
#include "AddFriendWindow.h"

#include <QPainter>
#include <QMouseEvent>

StatusBar::StatusBar(QWidget *parent) : QWidget(parent),
                                        m_isMaxWindow(false),
                                        m_colorR(0), m_colorG(0), m_colorB(0),
                                        isFriendRequestsWindowOpen(false),
                                        m_friend_requests_window(new FriendRequestsWindow),
                                        ui(new Ui::StatusBar),
                                        m_connect(TcpConnect::getInstance())
{
    ui->setupUi(this);

    initThis();
    initControl();
}

StatusBar::~StatusBar()
{
    delete m_friend_requests_window;
    delete ui;
}

void StatusBar::initThis()
{
    connect(m_connect, &TcpConnect::RFRpackAdd, this, &StatusBar::showRedPoint);

    //设置窗口无边框
    setWindowFlags(Qt::FramelessWindowHint);
}

void StatusBar::initControl()
{
    //将处理好友申请窗口设为模态
    m_friend_requests_window->setWindowModality(Qt::ApplicationModal);

    //添加好友按钮
    QString qss_btn_add_friend =
        "QPushButton:!hover:!pressed{border-image: url(:/resource/btn_add_friend_normal.png)}" //默认
        "QPushButton:hover{border-image: url(:/resource/btn_add_friend_hover.png)}"            //鼠标hover
        "QPushButton:pressed{border-image: url(:/resource/btn_add_friend_press.png)}";         //鼠标点击
    ui->btn_add_friend->setStyleSheet(qss_btn_add_friend);
    ui->btn_add_friend->setToolTip(QStringLiteral("添加好友"));
    ui->btn_add_friend->setCursor(QCursor(Qt::PointingHandCursor));

    //处理好友申请按钮
    QString qss_btn_process_friend_requests =
        "QPushButton:!hover:!pressed{border-image: url(:/resource/btn_process_friend_requests_normal.png)}" //默认
        "QPushButton:hover{border-image: url(:/resource/btn_process_friend_requests_hover.png)}"            //鼠标hover
        "QPushButton:pressed{border-image: url(:/resource/btn_process_friend_requests_press.png)}";         //鼠标点击
    ui->btn_process_friend_requests->setStyleSheet(qss_btn_process_friend_requests);
    ui->btn_process_friend_requests->setToolTip(QStringLiteral("处理好友申请"));
    ui->btn_process_friend_requests->setCursor(QCursor(Qt::PointingHandCursor));

    //网络状况状态栏
    QString qss_btn_network_status =
        "QPushButton{background-color:rgb(25,198,136);}" //默认
        "QPushButton{color: rgb(255,255,255); }"
        "QPushButton{border-radius: 12px;}";
    ui->btn_network_status->setStyleSheet(qss_btn_network_status);

    //初始化好友申请按钮上的红点
    ui->lbl_red_point->setPixmap(QPixmap(":/resource/red_point.png"));
    ui->lbl_red_point->setScaledContents(true);
    ui->lbl_red_point->setVisible(false);
}

void StatusBar::setBackgroundColor(int r, int g, int b)
{
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    // 重新绘制（调用paintEvent事件）;
    update();
}

void StatusBar::showRedPoint()
{
    if (!isFriendRequestsWindowOpen)
    {
        ui->lbl_red_point->setVisible(true);
    }
}

void StatusBar::hideRedPoint()
{
    ui->lbl_red_point->setVisible(false);
}

void StatusBar::paintEvent(QPaintEvent *event)
{
    //设置背景色;
    QPainter painter(this);
    QPainterPath pathBack;
    pathBack.setFillRule(Qt::WindingFill);
    pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));
    QWidget::paintEvent(event);
}

// 以下通过mousePressEvent、mouseMoveEvent、mouseReleaseEvent三个事件实现了鼠标拖动状态栏移动窗口的效果;
void StatusBar::mousePressEvent(QMouseEvent *event)
{
    // 在窗口最大化时禁止拖动窗口;
    if (!m_isMaxWindow)
    {
        m_isPressed = true;
        m_startMovePos = event->globalPos();
    }
    return QWidget::mousePressEvent(event);
}

void StatusBar::mouseMoveEvent(QMouseEvent *event)
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

void StatusBar::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
    return QWidget::mouseReleaseEvent(event);
}

void StatusBar::on_btn_add_friend_clicked()
{
    AddFriendWindow afw;
    afw.setWindowModality(Qt::ApplicationModal);
    afw.exec();
}

void StatusBar::on_btn_process_friend_requests_clicked()
{
    hideRedPoint();
    isFriendRequestsWindowOpen = true;
    m_friend_requests_window->exec();
    isFriendRequestsWindowOpen = false;
}
