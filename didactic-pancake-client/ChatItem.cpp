#include "ChatItem.h"
#include "ui_ChatItem.h"
#include "SQLConnect.h"

#include <QPainter>
#include <QFile>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QFontMetrics>
#include <vector>

using namespace std;

ChatItem::ChatItem(QWidget *parent, const QString &username) : QWidget(parent),
                                                               m_username(username),
                                                               m_lastTime(0),
                                                               m_unreadNum(0),
                                                               ui(new Ui::ChatItem),
                                                               m_contextMenu(new QMenu),
                                                               m_hideChatAction(new QAction("不显示聊天", this)),
                                                               m_deleteChatAction(new QAction("删除聊天", this)),
                                                               m_connect(TcpConnect::getInstance())
{
    ui->setupUi(this);

    initThis();
    initControl();
}

ChatItem::ChatItem(QWidget *parent, const QString &username, long long lastTime, int unreadNum, const QString &content) : QWidget(parent),
                                                                                                                          m_username(username),
                                                                                                                          m_lastTime(lastTime),
                                                                                                                          m_unreadNum(unreadNum),
                                                                                                                          ui(new Ui::ChatItem),
                                                                                                                          m_contextMenu(new QMenu),
                                                                                                                          m_hideChatAction(new QAction("不显示聊天", this)),
                                                                                                                          m_deleteChatAction(new QAction("删除聊天", this)),
                                                                                                                          m_connect(TcpConnect::getInstance())
{
    ui->setupUi(this);

    initThis();
    initControl();

    setContent(content, lastTime);
    ui->lbl_redpoint->setNum(unreadNum);
}

ChatItem::ChatItem(const ChatItem &other) : QWidget(other.parentWidget()),
                                            m_username(other.m_username),
                                            m_lastTime(other.m_lastTime),
                                            m_unreadNum(other.m_unreadNum),
                                            ui(new Ui::ChatItem),
                                            m_contextMenu(new QMenu),
                                            m_hideChatAction(new QAction("不显示聊天", this)),
                                            m_deleteChatAction(new QAction("删除聊天", this)),
                                            m_connect(TcpConnect::getInstance())
{
    ui->setupUi(this);

    initThis();
    initControl();

    setContent(other.ui->lbl_content->text(), m_lastTime);
    ui->lbl_redpoint->setNum(m_unreadNum);
}

ChatItem::~ChatItem()
{
    delete ui;
}

void ChatItem::setContent(const QString &content, long long l_time)
{
    QString newStrMsg = content;

    QFontMetrics fontWidth(ui->lbl_content->font());                                               //得到每个字符的宽度
    QString elideNote = fontWidth.elidedText(newStrMsg, Qt::ElideRight, ui->lbl_content->width()); //转换字符串
    ui->lbl_content->setText(elideNote);                                                           //显示省略好的字符串
    m_content = elideNote;

    m_lastTime = max(m_lastTime, l_time);
    //格式化时间
    QString curTime;
    if (m_lastTime != 0)
    {
        QLocale locale = QLocale::Chinese;
        uint ui_time = m_lastTime / 1000;
        uint now_time = QDateTime::currentDateTime().toTime_t();

        int delday = (now_time - 57600) / 86400 - (ui_time - 57600) / 86400;
        if (delday == 0)
        {
            curTime = QDateTime::fromTime_t(ui_time).toString("hh:mm");
        }
        else if (delday == 1)
        {
            curTime = QDateTime::fromTime_t(ui_time).toString("昨天");
        }
        else
        {
            curTime = locale.toString(QDateTime::fromTime_t(ui_time), "yy/MM/dd");
        }
    }
    else
    {
        curTime = "";
    }
    ui->lbl_last_time->setText(curTime);
}

void ChatItem::addUnreadNum()
{
    ui->lbl_redpoint->setNum(++m_unreadNum);
}

void ChatItem::clearUnreadNum()
{
    ui->lbl_redpoint->setNum(m_unreadNum = 0);
}

void ChatItem::initThis()
{
    //设置为无边框窗口
    setWindowFlags(Qt::FramelessWindowHint);

    connect(m_hideChatAction, &QAction::triggered, this, [=]()
            { emit hideUserChat(m_username); });
    connect(m_deleteChatAction, &QAction::triggered, this, [=]()
            { emit deleteUserChat(m_username); });
}

void ChatItem::initControl()
{
    ui->lbl_user_avatar->setPixmap(QPixmap(":/resource/default_avatar.png"));
    ui->lbl_user_avatar->setScaledContents(true);

    QFontMetrics fontWidth(ui->lbl_user_name->font());                                                //得到每个字符的宽度
    QString elideNote = fontWidth.elidedText(m_username, Qt::ElideRight, ui->lbl_user_name->width()); //转换

    ui->lbl_user_name->setText(elideNote); //显示省略好的字符串

    QString qss_m_contextMenu =
        "QMenu{background-color:rgba(255,255,255,1);}"
        "QMenu{border:1px solid rgb(196,196,196);}"
        "QMenu::item{padding:5px 30px;}"
        "QMenu::item:selected{background-color:rgb(226,226,226);}"
        "QMenu::item:selected{color:rgb(0,0,0)};";

    m_contextMenu->setStyleSheet(qss_m_contextMenu);
    m_contextMenu->addAction(m_hideChatAction);
    m_contextMenu->addAction(m_deleteChatAction);

    QString qss_lbl_content =
        "QLabel{color: rgb(153,153,153);}";
    ui->lbl_content->setStyleSheet(qss_lbl_content);

    QString qss_lbl_last_time =
        "QLabel{color: rgba(0,0,0,56);}";
    ui->lbl_last_time->setStyleSheet(qss_lbl_last_time);

    //设置消息红点大于99时显示...
    ui->lbl_redpoint->setPointType(RedPoint::SHOWDOTWHENBIGGER);
}

void ChatItem::paintEvent(QPaintEvent *event)
{

    //设置背景色;
    //    QPainter painter(this);
    //    QPainterPath pathBack;
    //    pathBack.setFillRule(Qt::WindingFill);
    //    pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);
    //    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    //    painter.fillPath(pathBack, QBrush(QColor(255, 255, 255)));
    QWidget::paintEvent(event);
}

void ChatItem::contextMenuEvent(QContextMenuEvent *event)
{
    m_contextMenu->exec(event->globalPos());
}

///////////////////////////////////////////////////////////////////////
ChatListWidget::ChatListWidget(QWidget *parent) : SuspendedScrollBar_ListWidget(parent)
{
    initThis();
}

void ChatListWidget::setContent(const QString &username, const QString &content, long long l_time)
{
    int newIndex = 0;
    for (; newIndex < (int)m_items.size(); ++newIndex)
    {
        if (m_items[newIndex].second->m_lastTime < l_time)
        {
            break;
        }
    }
    for (int i = 0; i < (int)m_items.size(); ++i)
    {
        if (m_items[i].second->m_username.compare(username) == 0)
        {

            bool isChoose = m_items[i].first == currentItem();
            m_items[i].second->setContent(content, l_time);

            if (m_items[i].first->isHidden()) //处于隐藏状态
            {
                showChatItem(username);
            }
            if (!isChoose) //当前未选中该聊天
            {
                m_items[i].second->addUnreadNum();
                emit readMessageNum(-1);
            }

            SQLConnect::getInstance()->setChatItem(username, m_items[i].second->m_lastTime, m_items[i].second->m_unreadNum, content, !m_items[i].first->isHidden());

            ChatItem *w_item = new ChatItem(*m_items[i].second);
            connect(w_item, &ChatItem::hideUserChat, this, [=](const QString &username)
                    {
                hideChatItem(username);
                emit hideUserChat(username); });
            connect(w_item, &ChatItem::deleteUserChat, this, [=](const QString &username)
                    {
                deleteChatItem(username);
                emit deleteUserChat(username); });

            delete takeItem(i);

            QListWidgetItem *p_item = new QListWidgetItem();
            insertItem(newIndex, p_item);
            p_item->setSizeHint(QSize(0, w_item->height()));
            setItemWidget(p_item, w_item);
            p_item->setSelected(isChoose);

            m_items.erase(m_items.begin() + i);
            m_items.insert(m_items.begin() + newIndex, make_pair(p_item, w_item));
            if (isChoose)
            {
                setCurrentRow(newIndex);
            }

            return;
        }
    }
    //该窗口不存在
    addChatItem(username);
    setContent(username, content, l_time);
}

void ChatListWidget::initThis()
{
    //设置鼠标滚轮速度
    verticalScrollBar()->setSingleStep(10);

    QString qss_this =
        "QListWidget{border-bottom: 1px solid black;}"
        "QListWidget{outline: 0px;}"
        "QListWidget{border: 0px;}"
        "QListWidget{background-color: rgb(235,234,233);}"
        "QListWidget:item:hover{background-color: rgb(220,219,218);}"
        "QListWidget:item:hover{border: 0px;}"
        "QListWidget::item:selected{border: 0px;}"
        "QListWidget::item:selected{background-color: rgb(201,202,203);}";
    setStyleSheet(qss_this);

    connect(this, &QListWidget::itemClicked, this, &ChatListWidget::handleItemClicked);

    auto lst = SQLConnect::getInstance()->getChatItem();

    for (const auto &item : lst)
    {
        QListWidgetItem *pItem = new QListWidgetItem();
        ChatItem *w_item = new ChatItem(this, get<0>(item), get<1>(item), get<2>(item), get<3>(item));
        connect(w_item, &ChatItem::hideUserChat, this, [=](const QString &username)
                {
            hideChatItem(username);
            emit hideUserChat(username); });
        connect(w_item, &ChatItem::deleteUserChat, this, [=](const QString &username)
                {
            deleteChatItem(username);
            emit deleteUserChat(username); });

        //计算需要插到第几行
        int i;
        for (i = 0; i < (int)m_items.size(); ++i)
        {
            if (m_items[i].second->m_lastTime < w_item->m_lastTime)
            {
                break;
            }
        }
        m_items.emplace(m_items.begin() + i, make_pair(pItem, w_item));
        insertItem(i, pItem);

        pItem->setSizeHint(QSize(0, w_item->height()));
        setItemWidget(pItem, w_item);
        if (get<4>(item) == 0)
        {
            pItem->setHidden(true);
        }
    }
}

void ChatListWidget::addChatItem(const QString &username)
{
    for (int i = 0; i < (int)m_items.size(); ++i)
    {
        if (m_items[i].second->m_username == username)
        {
            return;
        }
    }

    QListWidgetItem *pItem = new QListWidgetItem();
    ChatItem *w_item = new ChatItem(this, username);
    connect(w_item, &ChatItem::hideUserChat, this, [=](const QString &username)
            {
        hideChatItem(username);
        emit hideUserChat(username); });
    connect(w_item, &ChatItem::deleteUserChat, this, [=](const QString &username)
            {
        deleteChatItem(username);
        emit deleteUserChat(username); });

    //计算需要插到第几行
    int i;
    for (i = 0; i < (int)m_items.size(); ++i)
    {
        if (m_items[i].second->m_lastTime < w_item->m_lastTime)
        {
            break;
        }
    }
    m_items.emplace(m_items.begin() + i, make_pair(pItem, w_item));
    insertItem(i, pItem);

    pItem->setSizeHint(QSize(0, w_item->height()));
    setItemWidget(pItem, w_item);

    SQLConnect::getInstance()->addChatItem(username, w_item->m_lastTime, w_item->m_unreadNum, "", !pItem->isHidden());
}

void ChatListWidget::showChatItem(const QString &username)
{
    for (int i = 0; i < (int)m_items.size(); ++i)
    {
        if (m_items[i].second->m_username.compare(username) == 0)
        {
            emit readMessageNum(-m_items[i].second->m_unreadNum);
            m_items[i].first->setHidden(false);
            SQLConnect::getInstance()->setChatItem(m_items[i].second->m_username, m_items[i].second->m_lastTime, m_items[i].second->m_unreadNum, m_items[i].second->m_content, 1);
            break;
        }
    }
}

void ChatListWidget::selectChatItem(const QString &username)
{
    for (int i = 0; i < (int)m_items.size(); ++i)
    {
        if (m_items[i].second->m_username.compare(username) == 0)
        {
            if (m_items[i].first->isHidden())
            {
                showChatItem(username);
            }
            emit readMessageNum(m_items[i].second->m_unreadNum);
            m_items[i].second->clearUnreadNum();
            SQLConnect::getInstance()->setChatItem(m_items[i].second->m_username, m_items[i].second->m_lastTime, m_items[i].second->m_unreadNum, m_items[i].second->m_content, 1);
            this->setCurrentRow(i);
            break;
        }
    }
}

void ChatListWidget::hideChatItem(const QString &username)
{
    for (int i = 0; i < (int)m_items.size(); ++i)
    {
        if (m_items[i].second->m_username.compare(username) == 0)
        {
            emit readMessageNum(m_items[i].second->m_unreadNum);
            SQLConnect::getInstance()->setChatItem(m_items[i].second->m_username, m_items[i].second->m_lastTime, m_items[i].second->m_unreadNum, m_items[i].second->m_content, 0);
            m_items[i].first->setHidden(true);
            if (currentItem() == m_items[i].first)
            {
                setCurrentItem(nullptr);
            }
            break;
        }
    }
}

void ChatListWidget::deleteChatItem(const QString &username)
{
    for (int i = 0; i < (int)m_items.size(); ++i)
    {
        if (m_items[i].second->m_username.compare(username) == 0)
        {
            emit readMessageNum(m_items[i].second->m_unreadNum);
            if (currentItem() == m_items[i].first)
            {
                delete takeItem(i);
                if (currentItem() != nullptr)
                {
                    currentItem()->setSelected(false);
                }
            }
            else
            {
                delete takeItem(i);
            }
            m_items.erase(m_items.begin() + i);
            break;
        }
    }

    SQLConnect::getInstance()->deleteChatItem(username);
}

void ChatListWidget::handleItemClicked(QListWidgetItem *item)
{
    ChatItem *w_item = dynamic_cast<ChatItem *>(itemWidget(item));
    emit readMessageNum(w_item->m_unreadNum);
    w_item->clearUnreadNum();
    SQLConnect::getInstance()->setChatItem(w_item->m_username, w_item->m_lastTime, w_item->m_unreadNum, w_item->m_content, 1);
    emit chooseChat(w_item->m_username);
}
