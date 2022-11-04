#include "FriendItem.h"
#include "ui_FriendItem.h"

#include <QPainter>
#include <QFile>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <vector>

using namespace std;

FriendItem::FriendItem(QWidget *parent, const QString &username) : QWidget(parent),
                                                                   m_username(username),
                                                                   ui(new Ui::FriendItem),
                                                                   m_contextMenu(new QMenu),
                                                                   m_sendMessageAction(new QAction("发消息", this)),
                                                                   m_deleteFriendAction(new QAction("删除好友", this)),
                                                                   m_connect(TcpConnect::getInstance())
{
    ui->setupUi(this);

    initThis();
    initControl();
}

FriendItem::~FriendItem()
{
    delete ui;
}

void FriendItem::initThis()
{
    //设置为无边框窗口
    setWindowFlags(Qt::FramelessWindowHint);

    connect(m_sendMessageAction, &QAction::triggered, this, &FriendItem::changeToSendMessage);
    connect(m_deleteFriendAction, &QAction::triggered, this, &FriendItem::deleteFriend);
}

void FriendItem::initControl()
{
    ui->lbl_user_avatar->setPixmap(QPixmap(":/resource/default_avatar.png"));
    ui->lbl_user_avatar->setScaledContents(true);

    ui->lbl_user_name->setText(m_username);

    QString qss_m_contextMenu =
        "QMenu{background-color:rgba(255,255,255,1);}"
        "QMenu{border:1px solid rgb(196,196,196);}"
        "QMenu::item{padding:5px 30px;}"
        //"QMenu::item{color:rgb(0,0,0)};"
        //"QMenu::item{background-color:rgba(255,255,255,1)};"
        //"QMenu::item{font-size:12px;}"
        "QMenu::item:selected{background-color:rgb(226,226,226);}"
        "QMenu::item:selected{color:rgb(0,0,0)};";

    m_contextMenu->setStyleSheet(qss_m_contextMenu);
    m_contextMenu->addAction(m_sendMessageAction);
    m_contextMenu->addAction(m_deleteFriendAction);
}

void FriendItem::paintEvent(QPaintEvent *event)
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

void FriendItem::contextMenuEvent(QContextMenuEvent *event)
{
    m_contextMenu->exec(event->globalPos());
}

void FriendItem::changeToSendMessage()
{
    emit changeToUserChat(m_username);
}

void FriendItem::deleteFriend()
{
    //向服务器发送删除好友信息
    QString content = m_username + "\r\n";
    // QString转char*
    char *ctmp;
    QByteArray ba = content.toLatin1();
    ctmp = ba.data();

    m_connect->write_data(DataPacket(TcpConnect::DEF, content.length(), ctmp));
}

///////////////////////////////////////////////////////////////////////
FriendListWidget::FriendListWidget(QWidget *parent) : SuspendedScrollBar_ListWidget(parent)
{
    initThis();
}

void FriendListWidget::initThis()
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

    connect(this, &QListWidget::itemClicked, this, &FriendListWidget::handleItemClicked);
}

void FriendListWidget::addFriendItem(const QString &username)
{
    QListWidgetItem *pItem = new QListWidgetItem();
    FriendItem *w_item = new FriendItem(this, username);
    connect(w_item, &FriendItem::changeToUserChat, this, &FriendListWidget::changeToUserChat);

    //计算需要插到第几行
    int i;
    for (i = 0; i < (int)m_items.size(); ++i)
    {
        if (m_items[i].second->m_username.compare(username) > 0)
        {
            break;
        }
    }
    m_items.insert(m_items.begin() + i, make_pair(pItem, w_item));
    insertItem(i, pItem);

    pItem->setSizeHint(QSize(0, w_item->height()));
    setItemWidget(pItem, w_item);
}

void FriendListWidget::deleteFriendItem(const QString &username)
{
    for (int i = 0; i < (int)m_items.size(); ++i)
    {
        if (m_items[i].second->m_username.compare(username) == 0)
        {
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
}

void FriendListWidget::handleItemClicked(QListWidgetItem *item)
{
    emit chooseFriend(dynamic_cast<FriendItem *>(itemWidget(item))->m_username);
}
