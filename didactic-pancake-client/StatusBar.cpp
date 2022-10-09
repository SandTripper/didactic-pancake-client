#include "StatusBar.h"
#include "ui_StatusBar.h"

#include <QPainter>
#include <QMouseEvent>

StatusBar::StatusBar(QWidget *parent) : QWidget(parent), m_isMaxWindow(false), m_colorR(0), m_colorG(0), m_colorB(0),
                                        ui(new Ui::StatusBar)
{
    ui->setupUi(this);

    initControl();

    setWindowFlags(Qt::FramelessWindowHint);
}

StatusBar::~StatusBar()
{
    delete ui;
}

void StatusBar::setBackgroundColor(int r, int g, int b)
{
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    // 重新绘制（调用paintEvent事件）;
    update();
}

void StatusBar::initControl()
{
    QString qss_btn_add_friend =
        "QPushButton:!hover:!pressed{border-image: url(:/resource/btn_add_friend_normal.png)}" //默认
        "QPushButton:hover{border-image: url(:/resource/btn_add_friend_hover.png)}"            //鼠标hover
        "QPushButton:pressed{border-image: url(:/resource/btn_add_friend_press.png)}";         //鼠标点击
    ui->btn_add_friend->setStyleSheet(qss_btn_add_friend);
    ui->btn_add_friend->setToolTip(QStringLiteral("添加好友"));

    QString qss_btn_network_status =
        "QPushButton{background-color:rgb(25,198,136);}" //默认
        "QPushButton{color: rgb(255,255,255); }"
        "QPushButton{border-radius: 12px;}";

    ui->btn_network_status->setStyleSheet(qss_btn_network_status);
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

// 以下通过mousePressEvent、mouseMoveEvent、mouseReleaseEvent三个事件实现了鼠标拖动侧边栏栏移动窗口的效果;
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
