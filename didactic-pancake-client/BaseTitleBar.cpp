#include "BaseTitleBar.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QFile>
#include <QMouseEvent>
#include <QDebug>
#include <QPalette>

#define BUTTON_WIDTH 33  // 按钮宽度;
#define BUTTON_HEIGHT 25 // 按钮高度;
#define TITLE_HEIGHT 61  // 标题栏高度;

BaseTitleBar::BaseTitleBar(QWidget *parent)
    : QWidget(parent), m_x(1), m_colorR(153), m_colorG(153), m_colorB(153), m_isPressed(false), m_buttonType(MIN_MAX_BUTTON)
{
    // 初始化;
    initControl();
    initConnections();
}

BaseTitleBar::~BaseTitleBar()
{
}

// 初始化控件;
void BaseTitleBar::initControl()
{
    m_pIcon = new QLabel;
    m_pTitleContent = new QLabel;

    m_pButtonMin = new QPushButton;
    m_pButtonRestore = new QPushButton;
    m_pButtonMax = new QPushButton;
    m_pButtonClose = new QPushButton;

    m_pButtonMin->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    m_pButtonRestore->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    m_pButtonMax->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    m_pButtonClose->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));

    m_pTitleContent->setObjectName("TitleContent");
    m_pButtonMin->setObjectName("ButtonMin");
    m_pButtonRestore->setObjectName("ButtonRestore");
    m_pButtonMax->setObjectName("ButtonMax");
    m_pButtonClose->setObjectName("ButtonClose");

    QString qss_pButtonMin =
        "QPushButton:!hover:!pressed{border-image: url(:/resource/m_pButtonMin_normal.png)}" //默认
        "QPushButton:hover{border-image: url(:/resource/m_pButtonMin_hover.png)}"            //鼠标hover
        "QPushButton:pressed{border-image: url(:/resource/m_pButtonMin_press.png)}";         //鼠标点击
    QString qss_pButtonRestore =
        "QPushButton:!hover:!pressed{border-image: url(:/resource/m_pButtonRestore_normal.png)}" //默认
        "QPushButton:hover{border-image: url(:/resource/m_pButtonRestore_hover.png)}"            //鼠标hover
        "QPushButton:pressed{border-image: url(:/resource/m_pButtonRestore_press.png)}";         //鼠标点击
    QString qss_pButtonMax =
        "QPushButton:!hover:!pressed{border-image: url(:/resource/m_pButtonMax_normal.png)}" //默认
        "QPushButton:hover{border-image: url(:/resource/m_pButtonMax_hover.png)}"            //鼠标hover
        "QPushButton:pressed{border-image: url(:/resource/m_pButtonMax_press.png)}";         //鼠标点击
    QString qss_pButtonClose =
        "QPushButton:!hover:!pressed{border-image: url(:/resource/m_pButtonClose_normal.png)}" //默认
        "QPushButton:hover{border-image: url(:/resource/m_pButtonClose_hover.png)}"            //鼠标hover
        "QPushButton:pressed{border-image: url(:/resource/m_pButtonClose_press.png)}";         //鼠标点击
    m_pButtonMin->setStyleSheet(qss_pButtonMin);
    m_pButtonRestore->setStyleSheet(qss_pButtonRestore);
    m_pButtonMax->setStyleSheet(qss_pButtonMax);
    m_pButtonClose->setStyleSheet(qss_pButtonClose);

    m_pButtonMin->setToolTip(QStringLiteral("最小化"));
    m_pButtonRestore->setToolTip(QStringLiteral("还原"));
    m_pButtonMax->setToolTip(QStringLiteral("最大化"));
    m_pButtonClose->setToolTip(QStringLiteral("关闭"));

    m_pButtonMin->setCursor(QCursor(Qt::PointingHandCursor));
    m_pButtonRestore->setCursor(QCursor(Qt::PointingHandCursor));
    m_pButtonMax->setCursor(QCursor(Qt::PointingHandCursor));
    m_pButtonClose->setCursor(QCursor(Qt::PointingHandCursor));

    QHBoxLayout *mylayout = new QHBoxLayout(this);
    mylayout->setSpacing(0);
    mylayout->addWidget(m_pTitleContent);
    mylayout->addWidget(m_pButtonMin);
    mylayout->addWidget(m_pButtonRestore);
    mylayout->addWidget(m_pButtonMax);
    mylayout->addWidget(m_pButtonClose);

    mylayout->setContentsMargins(5, 0, 0, 0);

    mylayout->setAlignment(Qt::AlignRight | Qt::AlignTop);

    m_pTitleContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(TITLE_HEIGHT);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

// 信号槽的绑定;
void BaseTitleBar::initConnections()
{
    connect(m_pButtonMin, SIGNAL(clicked()), this, SLOT(onButtonMinClicked()));
    connect(m_pButtonRestore, SIGNAL(clicked()), this, SLOT(onButtonRestoreClicked()));
    connect(m_pButtonMax, SIGNAL(clicked()), this, SLOT(onButtonMaxClicked()));
    connect(m_pButtonClose, SIGNAL(clicked()), this, SLOT(onButtonCloseClicked()));
}

// 设置标题栏背景色,在paintEvent事件中进行绘制标题栏背景色;
//在构造函数中给了默认值，可以外部设置颜色值改变标题栏背景色;
void BaseTitleBar::setBackgroundColor(int r, int g, int b)
{
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    // 重新绘制（调用paintEvent事件）;
    update();
}

// 设置标题栏图标;
void BaseTitleBar::setTitleIcon(QString filePath)
{
    QPixmap titleIcon(filePath);
    m_pIcon->setPixmap(titleIcon.scaled(25, 25));
}

// 设置标题内容;
void BaseTitleBar::setTitleContent(QString titleContent)
{
    m_pTitleContent->setText(titleContent);
    m_titleContent = titleContent;
}

// 设置标题栏长度;
void BaseTitleBar::setTitleWidth(int width)
{
    this->setFixedWidth(width);
}

// 设置标题栏高度;
void BaseTitleBar::setTitleHeight(int height)
{
    this->setFixedHeight(height);
}

// 设置标题栏上按钮类型;
// 由于不同窗口标题栏上的按钮都不一样，所以可以自定义标题栏中的按钮;
// 这里提供了四个按钮，分别为最小化、还原、最大化、关闭按钮，如果需要其他按钮可自行添加设置;
void BaseTitleBar::setButtonType(ButtonType buttonType)
{
    m_buttonType = buttonType;

    switch (buttonType)
    {
    case MIN_BUTTON:
    {
        m_pButtonRestore->setVisible(false);
        m_pButtonMax->setVisible(false);
    }
    break;
    case MIN_MAX_BUTTON:
    {
        m_pButtonRestore->setVisible(false);
    }
    break;
    case ONLY_CLOSE_BUTTON:
    {
        m_pButtonMin->setVisible(false);
        m_pButtonRestore->setVisible(false);
        m_pButtonMax->setVisible(false);
    }
    break;
    default:
        break;
    }
}

void BaseTitleBar::setButtonStyle(const QString &qss_btn_min, const QString &qss_btn_restore, const QString &qss_btn_max, const QString &qss_btn_close)
{
    m_pButtonMin->setStyleSheet(qss_btn_min);
    m_pButtonRestore->setStyleSheet(qss_btn_restore);
    m_pButtonMax->setStyleSheet(qss_btn_max);
    m_pButtonClose->setStyleSheet(qss_btn_close);
}

// 保存窗口最大化前窗口的位置以及大小;
void BaseTitleBar::saveRestoreInfo(const QPoint point, const QSize size)
{
    m_restorePos = point;
    m_restoreSize = size;
}

// 获取窗口最大化前窗口的位置以及大小;
void BaseTitleBar::getRestoreInfo(QPoint &point, QSize &size)
{
    point = m_restorePos;
    size = m_restoreSize;
}

// 绘制标题栏背景色;
void BaseTitleBar::paintEvent(QPaintEvent *event)
{
    //设置背景色;
    QPainter painter(this);
    QPainterPath pathBack;
    pathBack.setFillRule(Qt::WindingFill);
    pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));

    // 当窗口最大化或者还原后，窗口宽度变了，标题栏的宽度应当一起改变;
    if (this->width() != this->parentWidget()->width() - 1 - m_x)
    {
        this->setFixedWidth(this->parentWidget()->width() - 1 - m_x);
    }
    QWidget::paintEvent(event);
}

// 双击响应事件，主要是实现双击标题栏进行最大化和最小化操作;
void BaseTitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    // 只有存在最大化、还原按钮时双击才有效;
    if (m_buttonType == MIN_MAX_BUTTON)
    {
        // 通过最大化按钮的状态判断当前窗口是处于最大化还是原始大小状态;
        // 或者通过单独设置变量来表示当前窗口状态;
        if (m_pButtonMax->isVisible())
        {
            onButtonMaxClicked();
        }
        else
        {
            onButtonRestoreClicked();
        }
    }

    return QWidget::mouseDoubleClickEvent(event);
}

// 以下通过mousePressEvent、mouseMoveEvent、mouseReleaseEvent三个事件实现了鼠标拖动标题栏移动窗口的效果;
void BaseTitleBar::mousePressEvent(QMouseEvent *event)
{
    if (m_buttonType == MIN_MAX_BUTTON)
    {
        // 在窗口最大化时禁止拖动窗口;
        if (m_pButtonMax->isVisible())
        {
            m_isPressed = true;
            m_startMovePos = event->globalPos();
        }
    }
    else
    {
        m_isPressed = true;
        m_startMovePos = event->globalPos();
    }

    return QWidget::mousePressEvent(event);
}

void BaseTitleBar::mouseMoveEvent(QMouseEvent *event)
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

void BaseTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
    return QWidget::mouseReleaseEvent(event);
}

// 以下为按钮操作响应的槽;
void BaseTitleBar::onButtonMinClicked()
{
    emit signalButtonMinClicked();
}

void BaseTitleBar::onButtonRestoreClicked()
{
    m_pButtonRestore->setVisible(false);
    m_pButtonMax->setVisible(true);
    emit signalButtonRestoreClicked();
}

void BaseTitleBar::onButtonMaxClicked()
{
    m_pButtonMax->setVisible(false);
    m_pButtonRestore->setVisible(true);
    emit signalButtonMaxClicked();
}

void BaseTitleBar::onButtonCloseClicked()
{
    emit signalButtonCloseClicked();
}
