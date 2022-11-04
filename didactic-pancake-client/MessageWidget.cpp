#include <QPainter>
#include <QDebug>

#include "MessageWidget.h"
#include "ui_MessageWidget.h"
#include "SuspendedScrollbar.h"
#include "SQLConnect.h"

using namespace std;

map<long long, MessageItem *> MessageWidget::m_sendingMessage;

MessageWidget::MessageWidget(QString username, QWidget *parent) : QWidget(parent),
                                                                  m_colorR(245), m_colorG(245), m_colorB(245),
                                                                  ui(new Ui::MessageWidget),
                                                                  m_connect(TcpConnect::getInstance()),
                                                                  m_tarUserName(username)
{
    ui->setupUi(this);
    initThis();
    initControl();
}

MessageWidget::~MessageWidget()
{
    delete ui;
}

void MessageWidget::initThis()
{
    //设置窗口无边框
    setWindowFlags(Qt::FramelessWindowHint);

    connect(ui->listWidget, &MessageListWidget::addMsg, [=](const QString &content,long long l_time)
            { emit messageAdd(m_tarUserName, content,l_time); });
}

void MessageWidget::initControl()
{

    //发送按钮
    QString qss_btn_send =
        "QPushButton{background-color:rgb(233,233,233);}" //按钮颜色
        "QPushButton{color: rgb(7,193,96); }"             //文字颜色
        "QPushButton{border-radius: 4px;}"                //圆角半径
        "QPushButton:hover{background-color:rgb(210,210,210);}"
        "QPushButton:hover{color: rgb(7,193,96); }"
        "QPushButton:hover{border-radius: 4px;}"
        "QPushButton:pressed{background-color:rgb(198,198,198);}"
        "QPushButton:pressed{color: rgb(7,193,96); }"
        "QPushButton:pressed{border-radius: 4px;}";
    ui->btn_send->setStyleSheet(qss_btn_send);

    //输入框
    QString qss_edit_input =
        "QTextEdit{background-color:rgb(245,245,245);}"
        "QTextEdit{padding-left: 1px; }"
        "QTextEdit{border: 0px;}";
    ui->edit_input->setStyleSheet(qss_edit_input);
    //设置鼠标滚轮速度
    ui->edit_input->verticalScrollBar()->setSingleStep(7);

    //表情按钮
    QString qss_btn_emoji =
        "QPushButton{border-image: url(:/resource/btn_emoji_normal.png)}"         //默认
        "QPushButton:hover{border-image: url(:/resource/btn_emoji_hover.png)}"    //鼠标hover
        "QPushButton:pressed{border-image: url(:/resource/btn_emoji_press.png)}"; //鼠标点击
    ui->btn_emoji->setStyleSheet(qss_btn_emoji);
    ui->btn_emoji->setToolTip(QStringLiteral("表情"));
    ui->btn_emoji->setCursor(QCursor(Qt::PointingHandCursor));

    ui->listWidget->m_tarUserName = m_tarUserName;
}

void MessageWidget::setBackgroundColor(int r, int g, int b)
{
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    // 重新绘制（调用paintEvent事件）;
    update();
}

MessageListWidget *MessageWidget::getListWidget()
{
    return ui->listWidget;
}

void MessageWidget::initMessages()
{
    ui->listWidget->initMessages();
}

void MessageWidget::messageHasSend(long long id)
{
    auto it = m_sendingMessage.find(id);
    if (it != m_sendingMessage.end())
    {
        SQLConnect::getInstance()->setChatRecordisSend(id, 1);
        m_sendingMessage[id]->setTextSuccess();
        m_sendingMessage.erase(it);
    }
}

void MessageWidget::paintEvent(QPaintEvent *event)
{
    //设置背景色;
    QPainter painter(this);
    QPainterPath pathBack;
    pathBack.setFillRule(Qt::WindingFill);
    pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));
    // 当窗口最大化或者还原后，窗口宽度变了，消息窗口的宽度应当一起改变;
    if (this->width() != this->parentWidget()->width())
    {
        this->setFixedWidth(this->parentWidget()->width());

        ui->btn_send->move(this->width() - 396 + 266, this->height() - 439 + 394);
        ui->edit_input->setFixedWidth(this->width() - 396 + 344);
    }
    // 当窗口最大化或者还原后，窗口高度变了，消息窗口的高度应当一起改变;
    if (this->height() != this->parentWidget()->height())
    {
        this->setFixedHeight(this->parentWidget()->height());

        ui->btn_send->move(this->width() - 396 + 266, this->height() - 439 + 394);
        ui->edit_input->move(24, this->height() - 439 + 350);
        ui->btn_emoji->move(22, this->height() - 439 + 319);
    }

    //设置分界线
    painter.setPen(QColor(231, 231, 231)); //设置顶部分界线颜色
    painter.drawLine(QLineF(0, 0, this->width(), 0));

    painter.setPen(QColor(236, 236, 236)); //设置输入框和消息框分界线颜色
    painter.drawLine(QLineF(0, this->height() - 130, this->width(), this->height() - 130));

    QWidget::paintEvent(event);
}

std::map<long long, MessageItem *> MessageWidget::getSendingMessage()
{
    return m_sendingMessage;
}

void MessageWidget::setSendingMessage(const std::map<long long, MessageItem *> &sendingMessage)
{
    m_sendingMessage = sendingMessage;
}

void MessageWidget::on_btn_send_clicked()
{
    QString text = ui->edit_input->toPlainText();
    ui->edit_input->clear();

    //储存发送中消息ID
    auto p_item = ui->listWidget->addMyMessage(text);
    m_sendingMessage[p_item->message_id] = p_item;

    QString content = QString::number(p_item->message_id) + "\r\n" + m_tarUserName + "\r\n" + text + "\r\n";
    // QString转char*
    string str = content.toStdString();
    m_connect->write_data(DataPacket(TcpConnect::SMA, str.length(), str.c_str()));

    ui->edit_input->setFocus();
}
