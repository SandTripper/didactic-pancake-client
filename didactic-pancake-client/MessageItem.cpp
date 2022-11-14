#include "MessageItem.h"

#include <QFontMetrics>
#include <QPaintEvent>
#include <QDateTime>
#include <QPainter>
#include <QMovie>
#include <QLabel>
#include <QDebug>
#include <QFontDatabase>
#include <QTimer>
#include <tuple>
#include <QApplication>

#include "AutoWrapLabel.h"
#include "Config.h"

using namespace std;

MessageItem::MessageItem(const QString &tarUserName, QWidget *parent) : QWidget(parent), m_tarUserName(tarUserName)
{
    QFont te_font = this->font();
    te_font.setFamily("Microsoft YaHei");
    te_font.setPointSize(10);
    //    te_font.setWordSpacing(0);
    //    te_font.setLetterSpacing(QFont::PercentageSpacing,0);
    //    te_font.setLetterSpacing(QFont::PercentageSpacing, 100);          //300%,100为默认  //设置字间距%
    //    te_font.setLetterSpacing(QFont::AbsoluteSpacing, 0);             //设置字间距为3像素 //设置字间距像素值
    this->setFont(te_font);

    m_lbl_avatar = new QLabel(this);
    m_lbl_avatar->setScaledContents(true);

    m_lbl_text = new AutoWrapLabel(this);
    m_lbl_text->setFont(te_font);
    m_lbl_text->setTextInteractionFlags(Qt::TextSelectableByMouse);

    m_loadingMovie = new QMovie(this);
    m_loadingMovie->setFileName(":/resource/loading.gif");
    m_loading = new QLabel(this);
    m_loading->setMovie(m_loadingMovie);
    m_loading->resize(16, 16);
    m_loading->setAttribute(Qt::WA_TranslucentBackground, true);
    m_loading->setAutoFillBackground(false);
}

void MessageItem::setTextSuccess()
{
    m_loading->hide();
    m_loadingMovie->stop();
    m_isSending = true;
}

void MessageItem::setText(QString text, QString time, QSize allSize, MessageItem::User_Type userType)
{
    m_msg = text;
    m_userType = userType;
    m_time = time;
    m_allSize = allSize;
    if (userType == User_Me)
    {
        if (!m_isSending)
        {
            m_loading->move(m_kuangRightRect.x() - m_loading->width() - 10, m_kuangRightRect.y() + m_kuangRightRect.height() / 2 - m_loading->height() / 2);
            m_loading->show();
            m_loadingMovie->start();
        }
    }
    else if (userType == User_Load)
    {
        m_loading->move((width() - m_loading->width()) / 2, (height() - m_loading->height()) / 2);
        m_loading->show();
        m_loadingMovie->start();
    }
    else
    {
        m_loading->hide();
    }

    if (userType == User_Me)
    {
        m_lbl_text->move(m_textRightRect.x(), m_textRightRect.y());
        m_lbl_text->setFixedSize(m_textRightRect.width(), m_textRightRect.height());
        m_lbl_text->setText(text);

        m_lbl_avatar->move(m_iconRightRect.x(), m_iconRightRect.y());
        m_lbl_avatar->setFixedSize(m_iconRightRect.width(), m_iconRightRect.height());

        QPixmap pix;
        QFile file(QApplication::applicationDirPath() + "/" + Config::loginedUserName + "/datas/avatar/34x34/" + Config::loginedUserName + ".png");
        if (file.open(QIODevice::ReadOnly))
        {
            pix.loadFromData(file.readAll());
            file.close();
        }
        else
        {
            pix.load(":/resource/default_avatar.png");
        }
        m_lbl_avatar->setPixmap(pix);
    }
    else if (userType == User_She)
    {

        m_lbl_text->move(m_textLeftRect.x(), m_textLeftRect.y());
        m_lbl_text->setFixedSize(m_textLeftRect.width(), m_textLeftRect.height());
        m_lbl_text->setText(text);

        m_lbl_avatar->move(m_iconLeftRect.x(), m_iconLeftRect.y());
        m_lbl_avatar->setFixedSize(m_iconLeftRect.width(), m_iconLeftRect.height());

        QPixmap pix;
        QFile file(QApplication::applicationDirPath() + "/" + Config::loginedUserName + "/datas/avatar/34x34/" + m_tarUserName + ".png");
        if (file.open(QIODevice::ReadOnly))
        {
            pix.loadFromData(file.readAll());
            file.close();
        }
        else
        {
            pix.load(":/resource/default_avatar.png");
        }
        m_lbl_avatar->setPixmap(pix);
    }
    else
    {
        m_lbl_text->hide();
    }

    if (userType == User_Time)
    {
        //格式化时间
        QLocale locale = QLocale::Chinese;
        uint i_time = time.toUInt();
        uint now_time = QDateTime::currentDateTime().toTime_t();

        int delday = (now_time - 57600) / 86400 - (i_time - 57600) / 86400;
        if (delday == 0)
        {
            m_curTime = QDateTime::fromTime_t(time.toInt()).toString("hh:mm");
        }
        else if (delday == 1)
        {
            m_curTime = QDateTime::fromTime_t(time.toInt()).toString("昨天 hh:mm");
        }
        else if (1 < delday && delday < 7)
        {
            m_curTime = locale.toString(QDateTime::fromTime_t(time.toInt()), "dddd hh:mm");
        }
        else
        {
            m_curTime = locale.toString(QDateTime::fromTime_t(time.toInt()), "yyyy年MM月dd日 hh:mm");
        }
    }
    this->update();
}

QSize MessageItem::fontRect(QString str)
{
    m_msg = str;
    int minHei = 30;
    int iconWH = 34;
    int iconSpaceW = 20;
    int iconRectW = 5;
    int iconTMPH = 10;
    int sanJiaoW = 6;
    int kuangTMP = 67;
    int textSpaceRect = 12;
    m_kuangWidth = this->width() - kuangTMP - 2 * (iconWH + iconSpaceW + iconRectW);
    m_textWidth = m_kuangWidth - 2 * textSpaceRect;
    m_spaceWid = this->width() - m_textWidth;
    m_iconLeftRect = QRect(iconSpaceW, iconTMPH, iconWH, iconWH);
    m_iconRightRect = QRect(this->width() - iconSpaceW - iconWH, iconTMPH, iconWH, iconWH);

    QSize size = getRealString(m_msg); // 整个的size

    // qDebug() << "fontRect Size:" << size;
    int hei = size.height() < minHei ? minHei : size.height();

    m_sanjiaoLeftRect = QRect(iconWH + iconSpaceW + iconRectW, m_lineHeight / 2, sanJiaoW, hei - m_lineHeight);
    m_sanjiaoRightRect = QRect(this->width() - iconRectW - iconWH - iconSpaceW - sanJiaoW, m_lineHeight / 2, sanJiaoW, hei - m_lineHeight);

    if (size.width() < (m_textWidth + m_spaceWid))
    {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), m_lineHeight / 4 * 3, size.width() - m_spaceWid + 2 * textSpaceRect, hei - m_lineHeight);
        m_kuangRightRect.setRect(this->width() - size.width() + m_spaceWid - 2 * textSpaceRect - iconWH - iconSpaceW - iconRectW - sanJiaoW,
                                 m_lineHeight / 4 * 3, size.width() - m_spaceWid + 2 * textSpaceRect, hei - m_lineHeight);
    }
    else
    {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), m_lineHeight / 4 * 3, m_kuangWidth, hei - m_lineHeight);
        m_kuangRightRect.setRect(iconWH + kuangTMP + iconSpaceW + iconRectW - sanJiaoW, m_lineHeight / 4 * 3, m_kuangWidth, hei - m_lineHeight);
    }
    m_textLeftRect.setRect(m_kuangLeftRect.x() + textSpaceRect, m_kuangLeftRect.y() + iconTMPH - 1,
                           m_kuangLeftRect.width() - 2 * textSpaceRect, m_kuangLeftRect.height() - 2 * iconTMPH);
    m_textRightRect.setRect(m_kuangRightRect.x() + textSpaceRect, m_kuangRightRect.y() + iconTMPH - 1,
                            m_kuangRightRect.width() - 2 * textSpaceRect, m_kuangRightRect.height() - 2 * iconTMPH);

    return QSize(size.width(), hei);
}

void MessageItem::updateAvatar()
{
    if (m_userType == User_Type::User_Me)
    {
        QPixmap pix;
        QFile file(QApplication::applicationDirPath() + "/" + Config::loginedUserName + "/datas/avatar/34x34/" + Config::loginedUserName + ".png");
        if (file.open(QIODevice::ReadOnly))
        {
            pix.loadFromData(file.readAll());
            file.close();
        }
        else
        {
            pix.load(":/resource/default_avatar.png");
        }
        m_lbl_avatar->setPixmap(pix);
    }
    else if (m_userType == User_Type::User_She)
    {
        QPixmap pix;
        QFile file(QApplication::applicationDirPath() + "/" + Config::loginedUserName + "/datas/avatar/34x34/" + m_tarUserName + ".png");
        if (file.open(QIODevice::ReadOnly))
        {
            pix.loadFromData(file.readAll());
            file.close();
        }
        else
        {
            pix.load(":/resource/default_avatar.png");
        }
        m_lbl_avatar->setPixmap(pix);
    }
}

QSize MessageItem::getRealString(QString src)
{
    QFontMetricsF fm(this->font());
    m_lineHeight = fm.lineSpacing();
    // int nMaxWidth = 0;
    //     int nCount = src.count("\n");
    //     if (nCount == 0)
    //     {
    //         nMaxWidth = fm.width(src);
    //         QString value = src;
    //         if (nMaxWidth > m_textWidth)
    //         {
    //             nMaxWidth = m_textWidth;
    //             int size = m_textWidth / fm.width(" ");
    //             int num = fm.width(value) / m_textWidth;
    //             int ttmp = num * fm.width(" ");
    //             num = (fm.width(value)) / m_textWidth;
    //             nCount += num;
    //             QString temp = "";
    //             for (int i = 0; i < num; i++)
    //             {
    //                 temp += value.mid(i * size, (i + 1) * size) + "\n";
    //             }
    //             src.replace(value, temp);
    //         }
    //     }
    //     else
    //     {
    //         for (int i = 0; i < (nCount + 1); i++)
    //         {
    //             QString value = src.split("\n").at(i);
    //             nMaxWidth = fm.width(value) > nMaxWidth ? fm.width(value) : nMaxWidth;
    //             if (fm.width(value) > m_textWidth)
    //             {
    //                 nMaxWidth = m_textWidth;
    //                 int size = m_textWidth / fm.width(" ");
    //                 int num = fm.width(value) / m_textWidth;
    //                 num = ((i + num) * fm.width(" ") + fm.width(value)) / m_textWidth;
    //                 nCount += num;
    //                 QString temp = "";
    //                 for (int i = 0; i < num; i++)
    //                 {
    //                     temp += value.mid(i * size, (i + 1) * size) + "\n";
    //                 }
    //                 src.replace(value, temp);
    //             }
    //         }
    //     }
    //     return QSize(nMaxWidth + m_spaceWid, (nCount + 1) * m_lineHeight + 2 * m_lineHeight);
    AutoWrapLabel a;
    a.setFont(this->font());
    a.setFixedWidth(m_textWidth);
    a.setText(src);

    return QSize(a.getMaxWidth() + m_spaceWid, a.getRaw() * m_lineHeight + 2 * m_lineHeight);
}

void MessageItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //消锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));

    if (m_userType == User_Type::User_She)
    { // 用户
        //头像
        //        painter.drawRoundedRect(m_iconLeftRect,m_iconLeftRect.width(),m_iconLeftRect.height());
        // painter.drawPixmap(m_iconLeftRect, m_leftPixmap);

        //框加边
        QColor col_KuangB(234, 234, 234);
        painter.setBrush(QBrush(col_KuangB));
        painter.drawRoundedRect(m_kuangLeftRect.x() - 1, m_kuangLeftRect.y() - 1, m_kuangLeftRect.width() + 2, m_kuangLeftRect.height() + 2, 4, 4);
        //框
        QColor col_Kuang(255, 255, 255);
        painter.setBrush(QBrush(col_Kuang));
        painter.drawRoundedRect(m_kuangLeftRect, 4, 4);

        //三角
        QPointF points[3] = {
            QPointF(m_sanjiaoLeftRect.x(), 30),
            QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 25),
            QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 35),
        };
        QPen pen;
        pen.setColor(col_Kuang);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

        //三角加边
        QPen penSanJiaoBian;
        penSanJiaoBian.setColor(col_KuangB);
        painter.setPen(penSanJiaoBian);
        painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 24));
        painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x() + m_sanjiaoLeftRect.width(), 36));

        //        //内容
        //        QPen penText;
        //        penText.setColor(QColor(51, 51, 51));
        //        painter.setPen(penText);
        //        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        //        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        //        painter.setFont(this->font());
        //        painter.drawText(m_textLeftRect, m_msg, option);
    }
    else if (m_userType == User_Type::User_Me)
    { // 自己
        //头像
        //        painter.drawRoundedRect(m_iconRightRect,m_iconRightRect.width(),m_iconRightRect.height());
        // painter.drawPixmap(m_iconRightRect, m_rightPixmap);

        //框
        QColor col_Kuang(149, 236, 105);
        painter.setBrush(QBrush(col_Kuang));
        painter.drawRoundedRect(m_kuangRightRect, 4, 4);

        //三角
        QPointF points[3] = {
            QPointF(m_sanjiaoRightRect.x() + m_sanjiaoRightRect.width(), 30),
            QPointF(m_sanjiaoRightRect.x(), 25),
            QPointF(m_sanjiaoRightRect.x(), 35),
        };
        QPen pen;
        pen.setColor(col_Kuang);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

        //        //内容
        //        QPen penText;
        //        penText.setColor(Qt::black);
        //        painter.setPen(penText);
        //        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        //        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        //        painter.setFont(this->font());
        //        painter.drawText(m_textRightRect, m_msg, option);
    }
    else if (m_userType == User_Type::User_Time)
    { // 时间
        //处理时间背景框的长宽
        QFontMetricsF fm(this->font());
        int textRectWidth = fm.width(m_curTime) + 12 - fm.width(m_curTime) / 30 * 2;
        if (textRectWidth > 100)
            textRectWidth -= 4;

        QPainterPath pathBack;
        pathBack.setFillRule(Qt::WindingFill);
        pathBack.addRoundedRect(QRect((this->width() - textRectWidth) / 2, (this->height() - 19) / 2 + 1, textRectWidth, 19), 2, 2);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter.fillPath(pathBack, QBrush(QColor(218, 218, 218)));

        QPen penText;
        penText.setColor(QColor(255, 255, 255));
        painter.setPen(penText);
        QTextOption option(Qt::AlignCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        QFont te_font = this->font();
        te_font.setFamily("Microsoft YaHei");
        te_font.setPointSize(9);
        painter.setFont(te_font);
        painter.drawText(this->rect(), m_curTime, option);
    }
}

///////////////////////////////////////////////////////////////////////
MessageListWidget::MessageListWidget(QWidget *parent) : SuspendedScrollBar_ListWidget(parent),
                                                        m_sqlconn(SQLConnect::getInstance())
{
    initThis();
}

void MessageListWidget::initMessages()
{
    m_totalChatRecordNum = SQLConnect::getInstance()->getUserChatRecordNumber(m_tarUserName);
    clear();
    loadMessage();
    if (parentWidget()->isVisible())
    {
        scrollToBottom();
    }
}

void MessageListWidget::initThis()
{
    //设置鼠标滚轮速度
    verticalScrollBar()->setSingleStep(10);

    QString qss_this =
        "QListWidget{border-bottom: 1px solid black;}"
        "QListWidget{outline: 0px;}"
        "QListWidget{border: 0px;}"
        "QListWidget{background-color: rgb(245,245,245);}"
        "QListWidget:item:hover{background-color: rgb(245,245,245);}"
        "QListWidget:item:hover{border: 0px;}"
        "QListWidget::item:selected{border: 0px;}"
        "QListWidget::item:selected{background-color: rgb(245,245,245);}";
    setStyleSheet(qss_this);

    //初始化时，连接滑动条信号
    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(onScrollBarValueChanged(int)));

    //    //设置为无法选择
    //    setSelectionMode(QAbstractItemView::NoSelection);
}

void MessageListWidget::paintEvent(QPaintEvent *event)
{
    // 当窗口最大化或者还原后，窗口宽度变了，消息窗口的宽度应当一起改变;
    if (this->width() != this->parentWidget()->width())
    {
        this->setFixedWidth(this->parentWidget()->width());

        for (const auto &mes : m_items)
        {
            if (mes.second->userType() == MessageItem::User_She)
            {
                mes.second->move(this->width() - 396, mes.second->pos().y());
            }
        }
        for (int i = 0; i < count(); i++)
        {
            MessageItem *messageW = (MessageItem *)itemWidget(item(i));
            QListWidgetItem *item = this->item(i);
            messageW->setFixedWidth(this->width());
            QSize size = messageW->fontRect(messageW->text());
            item->setSizeHint(size);
            messageW->setText(messageW->text(), messageW->time(), size, messageW->userType());
            setItemWidget(item, messageW);
        }
    }
    // 当窗口最大化或者还原后，窗口高度变了，消息窗口的高度应当一起改变;
    if (this->height() != this->parentWidget()->height())
    {
        this->setFixedHeight(this->parentWidget()->height() - 439 + 308);
    }

    return SuspendedScrollBar_ListWidget::paintEvent(event);
}

void MessageListWidget::onScrollBarValueChanged(int num)
{
    if (verticalScrollBar()->minimum() == num && (int)m_items.size() != m_totalChatRecordNum)
    {
        int lmaxnum = verticalScrollBar()->maximum();
        addLoadMessage();
        QTimer::singleShot(100, this, [=]()
                           {
            int row = loadMessage();
            int nmaxnum = verticalScrollBar()->maximum();
            verticalScrollBar()->setValue(nmaxnum-lmaxnum);
            delete takeItem(row);
            showScrollBar(); });
    }
}

int MessageListWidget::loadMessage()
{
    auto lst = m_sqlconn->getNlinesChatRecord(m_tarUserName, m_items.size(), 50);
    // this->clear();

    int lineCnt = 0;

    for (const auto &msg : lst)
    {
        if (insertTimeMessage(QString::number(get<2>(msg) / 1000), lineCnt))
            ++lineCnt;
        MessageItem *messageW = new MessageItem(m_tarUserName);
        QListWidgetItem *item = new QListWidgetItem();
        insertItem(lineCnt, item);
        messageW->setFixedWidth(this->width());
        QSize size = messageW->fontRect(get<3>(msg));
        item->setSizeHint(size);
        if (get<1>(msg) == 1)
        {
            messageW->setText(get<3>(msg), QString::number(get<2>(msg) / 1000), size, MessageItem::User_Me);
        }
        else
        {
            messageW->setText(get<3>(msg), QString::number(get<2>(msg) / 1000), size, MessageItem::User_She);
        }
        if (get<4>(msg) == 1)
        {
            messageW->setTextSuccess();
        }
        setItemWidget(item, messageW);
        m_items.emplace_back(make_pair(item, messageW));
        ++lineCnt;
    }
    return lineCnt;
}

void MessageListWidget::clear()
{
    m_items.clear();
    return QListWidget::clear();
}

MessageItem *MessageListWidget::addMyMessage(const QString &msg)
{
    auto qdt = QDateTime::currentDateTime();
    long long l_time = (long long)qdt.toTime_t() * 1000 + qdt.time().msec();
    long long msg_id = l_time * 10000 + rand() % 10000;
    m_sqlconn->addChatRecord(msg_id, m_tarUserName, 1, (long long)qdt.toTime_t() * 1000 + qdt.time().msec(), msg, 0);
    ++m_totalChatRecordNum;

    emit addMsg(msg, l_time);

    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    addTimeMessage(time);

    MessageItem *messageW = new MessageItem(m_tarUserName);
    QListWidgetItem *item = new QListWidgetItem();

    addItem(item);

    messageW->setFixedWidth(this->width());
    QSize size = messageW->fontRect(msg);
    item->setSizeHint(size);
    messageW->setText(msg, time, size, MessageItem::User_Me);
    messageW->message_id = msg_id;
    setItemWidget(item, messageW);
    m_items.emplace_back(make_pair(item, messageW));

    scrollToBottom();

    return messageW;
}

void MessageListWidget::addOtherMessage(const QString &msg, long long l_time)
{
    auto qdt = QDateTime::currentDateTime();
    long long msg_id = (long long)qdt.toTime_t() * 10000000 + qdt.time().msec() * 10000 + rand() % 10000;
    m_sqlconn->addChatRecord(msg_id, m_tarUserName, 0, l_time, msg, 1);
    ++m_totalChatRecordNum;

    emit addMsg(msg, l_time);

    QString time = QString::number(l_time / 1000); //时间戳
    addTimeMessage(time);

    MessageItem *messageW = new MessageItem(m_tarUserName);
    QListWidgetItem *item = new QListWidgetItem();
    addItem(item);

    messageW->setFixedWidth(this->width());
    QSize size = messageW->fontRect(msg);
    item->setSizeHint(size);
    messageW->setText(msg, time, size, MessageItem::User_She);
    messageW->message_id = msg_id;
    setItemWidget(item, messageW);
    m_items.emplace_back(make_pair(item, messageW));

    if (parentWidget()->isVisible())
    {
        scrollToBottom();
    }
}

void MessageListWidget::addTimeMessage(QString curMsgTime)
{
    bool isShowTime = false;

    if (this->count() > 0)
    {
        QListWidgetItem *lastItem = this->item(this->count() - 1);
        MessageItem *messageW = (MessageItem *)this->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        // qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 180); // 两个消息相差三分钟
        // isShowTime = true;
    }
    else
    {
        isShowTime = true;
    }
    if (isShowTime)
    {
        MessageItem *messageTime = new MessageItem(m_tarUserName);
        QListWidgetItem *itemTime = new QListWidgetItem();
        addItem(itemTime);
        QSize size = QSize(this->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, MessageItem::User_Time);
        this->setItemWidget(itemTime, messageTime);
    }
}

bool MessageListWidget::insertTimeMessage(QString curMsgTime, int row)
{
    bool isShowTime = false;

    if (row > 0)
    {
        QListWidgetItem *lastItem = this->item(row - 1);
        MessageItem *messageW = (MessageItem *)this->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        // qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 180); // 两个消息相差三分钟
        // isShowTime = true;
    }
    else
    {
        isShowTime = true;
    }
    if (isShowTime)
    {
        MessageItem *messageTime = new MessageItem(m_tarUserName);

        QListWidgetItem *itemTime = new QListWidgetItem();

        insertItem(row, itemTime);

        QSize size = QSize(this->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, MessageItem::User_Time);
        this->setItemWidget(itemTime, messageTime);
    }
    return isShowTime;
}

QListWidgetItem *MessageListWidget::addLoadMessage()
{
    MessageItem *messageLoad = new MessageItem(m_tarUserName);
    QListWidgetItem *itemLoad = new QListWidgetItem();
    insertItem(0, itemLoad);
    QSize size = QSize(this->width(), 30);
    messageLoad->resize(size);
    itemLoad->setSizeHint(size);
    messageLoad->setText("", "", size, MessageItem::User_Load);
    setItemWidget(itemLoad, messageLoad);
    return itemLoad;
}

void MessageListWidget::updateMyAvatar()
{
    for (int i = 0; i < (int)m_items.size(); ++i)
    {
        if (m_items[i].second->userType() == MessageItem::User_Me)
        {
            m_items[i].second->updateAvatar();
        }
    }
}

void MessageListWidget::updateTargetAvatar()
{
    for (int i = 0; i < (int)m_items.size(); ++i)
    {
        if (m_items[i].second->userType() == MessageItem::User_She)
        {
            m_items[i].second->updateAvatar();
        }
    }
}
