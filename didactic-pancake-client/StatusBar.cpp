#include "StatusBar.h"
#include "ui_StatusBar.h"
#include "AddFriendWindow.h"

#include <QPainter>
#include <QMouseEvent>

StatusBar::StatusBar(QWidget *parent) : QWidget(parent), m_isMaxWindow(false), m_colorR(0), m_colorG(0), m_colorB(0),
    m_friend_requests_window(new FriendRequestsWindow),
    ui(new Ui::StatusBar)
{
    ui->setupUi(this);

    m_connect=TcpConnect::getInstance();
    connect(m_connect,&TcpConnect::RFRpackAdd,this,&StatusBar::showRedPoint);

    //item数目变的不为空
    void notEmptyItem();
    //item数目变为空
    void emptyItem();

    initControl();

    setWindowFlags(Qt::FramelessWindowHint);
}

StatusBar::~StatusBar()
{
    delete ui;
    delete m_friend_requests_window;
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
    ui->lbl_red_point->setVisible(true);
}

void StatusBar::hideRedPoint()
{
    ui->lbl_red_point->setVisible(false);
}

void StatusBar::initControl()
{
    m_friend_requests_window->setWindowModality(Qt::ApplicationModal);

    QString qss_btn_add_friend =
            "QPushButton:!hover:!pressed{border-image: url(:/resource/btn_add_friend_normal.png)}" //默认
            "QPushButton:hover{border-image: url(:/resource/btn_add_friend_hover.png)}"            //鼠标hover
            "QPushButton:pressed{border-image: url(:/resource/btn_add_friend_press.png)}";         //鼠标点击
    ui->btn_add_friend->setStyleSheet(qss_btn_add_friend);
    ui->btn_add_friend->setToolTip(QStringLiteral("添加好友"));
    ui->btn_add_friend->setCursor(QCursor(Qt::PointingHandCursor));

    QString qss_btn_process_friend_requests =
            "QPushButton:!hover:!pressed{border-image: url(:/resource/btn_process_friend_requests_normal.png)}" //默认
            "QPushButton:hover{border-image: url(:/resource/btn_process_friend_requests_hover.png)}"            //鼠标hover
            "QPushButton:pressed{border-image: url(:/resource/btn_process_friend_requests_press.png)}";         //鼠标点击
    ui->btn_process_friend_requests->setStyleSheet(qss_btn_process_friend_requests);
    ui->btn_process_friend_requests->setToolTip(QStringLiteral("处理好友申请"));
    ui->btn_process_friend_requests->setCursor(QCursor(Qt::PointingHandCursor));

    QString qss_btn_network_status =
            "QPushButton{background-color:rgb(25,198,136);}" //默认
            "QPushButton{color: rgb(255,255,255); }"
            "QPushButton{border-radius: 12px;}";

    ui->btn_network_status->setStyleSheet(qss_btn_network_status);


    ui->lbl_red_point->setPixmap(QPixmap(":/resource/red_point.png"));
    ui->lbl_red_point->setScaledContents(true);
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

    //    // 当窗口最大化或者还原后，窗口长度变了，栏的高度应当一起改变;
    //    if (this->height() != this->parentWidget()->height() - 2)
    //    {
    //        this->setFixedHeight(this->parentWidget()->height() - 2);
    //    }
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
    m_friend_requests_window->exec();
    hideRedPoint();
}
