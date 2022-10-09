#include "BaseWindow.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QFile>
#include <QGraphicsDropShadowEffect>
#include <QtMath>

BaseWindow::BaseWindow(QWidget *parent)
    : QWidget(parent)
{
    // FramelessWindowHint属性设置窗口去除边框;
    // WindowMinimizeButtonHint 属性设置在窗口最小化时，点击任务栏窗口可以显示出原窗口;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

    // 设置窗口背景透明;
    setAttribute(Qt::WA_TranslucentBackground);

    // 初始化标题栏;
    initTitleBar();

    m_colorR = 0;
    m_colorG = 0;
    m_colorB = 0;
}

BaseWindow::~BaseWindow()
{
}

void BaseWindow::initTitleBar()
{
    m_titleBar = new BaseTitleBar(this);
    m_titleBar->move(m_titleBar->m_x, 1);

    connect(m_titleBar, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
    connect(m_titleBar, SIGNAL(signalButtonRestoreClicked()), this, SLOT(onButtonRestoreClicked()));
    connect(m_titleBar, SIGNAL(signalButtonMaxClicked()), this, SLOT(onButtonMaxClicked()));
    connect(m_titleBar, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));
}

void BaseWindow::paintEvent(QPaintEvent *event)
{
    //  Q_UNUSED(event);
    //  QStyleOption opt;
    //  opt.init(this);
    //  QPainter painter(this);
    //  style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    //设置背景色;
    QPainter painter(this);
    QPainterPath pathBack;
    pathBack.setFillRule(Qt::WindingFill);
    pathBack.addRoundedRect(QRect(1, 1, this->width() - 1, this->height() - 2), 3, 3);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));

    // painter.setCompositionMode( QPainter::CompositionMode_Clear );

    //设置边框
    painter.setPen(QColor(10, 10, 10, 41));                         //设置画笔记颜色
    painter.drawRoundedRect(0, 0, width() - 1, height() - 1, 1, 1); //绘制边框

    return QWidget::paintEvent(event);
}

// void BaseWindow::loadStyleSheet(const QString &sheetName)
//{
//     QFile file(":/Resources/" + sheetName + ".css");
//     file.open(QFile::ReadOnly);
//     if (file.isOpen())
//     {
//         QString styleSheet = this->styleSheet();
//         styleSheet += QLatin1String(file.readAll());
//         this->setStyleSheet(styleSheet);
//     }
// }

// 设置标题栏背景色,在paintEvent事件中进行绘制标题栏背景色;
//在构造函数中给了默认值，可以外部设置颜色值改变标题栏背景色;
void BaseWindow::setBackgroundColor(int r, int g, int b)
{
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    // 重新绘制（调用paintEvent事件）;
    update();
}

void BaseWindow::onButtonMinClicked()
{
    if (Qt::Tool == (windowFlags() & Qt::Tool))
    {
        hide(); //设置了Qt::Tool 如果调用showMinimized()则窗口就销毁了？？？
    }
    else
    {
        showMinimized();
    }
}

void BaseWindow::onButtonRestoreClicked()
{
    QPoint windowPos;
    QSize windowSize;
    m_titleBar->getRestoreInfo(windowPos, windowSize);
    this->setGeometry(QRect(windowPos, windowSize));
}

void BaseWindow::onButtonMaxClicked()
{
    m_titleBar->saveRestoreInfo(this->pos(), QSize(this->width(), this->height()));
    QRect desktopRect = QApplication::desktop()->availableGeometry();
    QRect FactRect = QRect(desktopRect.x() - 3, desktopRect.y() - 3, desktopRect.width() + 6, desktopRect.height() + 6);
    setGeometry(FactRect);
}

void BaseWindow::onButtonCloseClicked()
{
    close();
}
