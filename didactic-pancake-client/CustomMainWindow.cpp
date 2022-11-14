#include <windows.h>

#include "CustomMainWindow.h"
#include "ui_CustomMainWindow.h"
#include "LoginWindow.h"
#include "SQLConnect.h"
#include "Config.h"
#include "PictureViewingWindow.h"

#include <QSoundEffect>

CustomMainWindow::CustomMainWindow(QWidget *parent) : BaseWindow(parent),
                                                      ui(new Ui::CustomMainWindow),
                                                      m_connect(TcpConnect::getInstance()),
                                                      m_sideBar(new SideBar(this)),
                                                      m_statusBar(new StatusBar(this)),
                                                      m_friendBar(new FriendBar(this)),
                                                      m_friendInformation(new FriendInformation(this)),
                                                      m_chatBar(new ChatBar(this)),
                                                      m_messageBar(new MessageBar(this))
{
    ui->setupUi(this);

    // this->hide();

    initThis();
    initControl();
    initTitleBar();
    initSideBar();
    initStatusBar();
    initFriendBar();
    initFriendInformationBar();
    initChatBar();
    initMessageBar();

    TcpConnect::getInstance()->write_data(DataPacket(TcpConnect::RDY, 0, ""));
    //    QTimer::singleShot(5000, this, [=]()
    //    {
    //        TcpConnect::getInstance()->write_data(DataPacket(TcpConnect::RDY,0,""));
    //        this->show();
    //    });
}

CustomMainWindow::~CustomMainWindow()
{
    delete m_sideBar;
    delete m_statusBar;
    delete ui;
}

void CustomMainWindow::initThis()
{
    //设置背景颜色
    setBackgroundColor(214, 214, 214);

    setWindowTitle(Config::loginedUserName); //将窗口名字设为登录的用户名
}

void CustomMainWindow::initTitleBar()
{

    connect(m_titleBar, SIGNAL(signalButtonRestoreClicked()), this, SLOT(onButtonRestoreClicked()));
    connect(m_titleBar, SIGNAL(signalButtonMaxClicked()), this, SLOT(onButtonMaxClicked()));

    m_titleBar->setBackgroundColor(245, 245, 245);
    m_titleBar->setButtonType(MIN_MAX_BUTTON);
    m_titleBar->setTitleWidth(this->width());
    m_titleBar->setTitleHeight(61);

    m_titleBar->m_x = 305;

    m_titleBar->move(m_titleBar->m_x, 1);
}

void CustomMainWindow::initControl()
{
    connect(m_messageBar, &MessageBar::setChatUserName, this, [=](const QString &username)
            { ui->lbl_chatUsername->setText(username); });
}

void CustomMainWindow::initSideBar()
{
    connect(m_chatBar, &ChatBar::readMessageNum, m_sideBar, &SideBar::handleReadMessageNum);

    m_sideBar->setBackgroundColor(46, 46, 46);
    m_sideBar->move(1, 1);
}

void CustomMainWindow::initStatusBar()
{
    connect(m_chatBar, &ChatBar::friendAvatarChanged, m_statusBar, &StatusBar::friendAvatarChanged);

    m_statusBar->setBackgroundColor(250, 250, 250);
    m_statusBar->move(55, 1);
}

void CustomMainWindow::initFriendBar()
{
    connect(m_sideBar, &SideBar::changeToChat, this, [=]()
            { m_friendBar->setVisible(false); });
    connect(m_sideBar, &SideBar::changeToFriend, this, [=]()
            { m_friendBar->setVisible(true); });
    connect(m_chatBar, &ChatBar::friendAvatarChanged, this, [=](const QString &username)
            { m_friendBar->handleFriendAvatarChanged(username); });

    m_friendBar->setVisible(false);
    m_friendBar->setBackgroundColor(230, 229, 229);
    m_friendBar->move(55, 62);

    m_connect->write_data(DataPacket(TcpConnect::GFI, 3, "1\r\n"));
}

void CustomMainWindow::initFriendInformationBar()
{
    connect(m_friendBar->getListWidget(), &FriendListWidget::chooseFriend, m_friendInformation, &FriendInformation::updateFriend);
    connect(m_friendBar, &FriendBar::deleteFriend, m_friendInformation, &FriendInformation::deleteFriend);
    connect(m_sideBar, &SideBar::changeToChat, this, [=]()
            { m_friendInformation->setVisible(false); });
    connect(m_sideBar, &SideBar::changeToFriend, this, [=]()
            { m_friendInformation->setVisible(true); });

    m_friendInformation->setVisible(false);
    m_friendInformation->setBackgroundColor(245, 245, 245);
    m_friendInformation->move(305, 62);
}

void CustomMainWindow::initChatBar()
{
    connect(m_sideBar, &SideBar::changeToChat, this, [=]()
            { m_chatBar->setVisible(true); });
    connect(m_sideBar, &SideBar::changeToFriend, this, [=]()
            { m_chatBar->setVisible(false); });

    connect(m_messageBar, &MessageBar::messageAdd, m_chatBar, &ChatBar::handleMessageAdd);
    connect(m_friendBar, &FriendBar::addFriend, m_chatBar, &ChatBar::handleAddFriend);
    connect(m_friendBar, &FriendBar::deleteFriend, m_chatBar, &ChatBar::handleDeleteFriend);
    connect(m_friendInformation, &FriendInformation::changeToUserChat, [=](QString username)
            {
        m_sideBar->on_btn_change_to_chat_clicked();
        m_chatBar->selectUser(username); });

    connect(m_friendBar, &FriendBar::changeToUserChat, [=](QString username)
            {
        m_sideBar->on_btn_change_to_chat_clicked();
        m_chatBar->selectUser(username); });

    m_chatBar->setVisible(true);
    m_chatBar->setBackgroundColor(230, 229, 229);
    m_chatBar->move(55, 62);
}

void CustomMainWindow::initMessageBar()
{
    connect(m_sideBar, &SideBar::changeToChat, this, [=]()
            {
        m_messageBar->show();
        ui->lbl_chatUsername->show(); });
    connect(m_sideBar, &SideBar::changeToFriend, this, [=]()
            {
        m_messageBar->hide();
        ui->lbl_chatUsername->hide(); });
    connect(m_chatBar, &ChatBar::selectUser, m_messageBar, &MessageBar::changeToUserWidget);
    connect(m_friendBar, &FriendBar::deleteFriend, m_messageBar, &MessageBar::deleteUserWidget);
    connect(m_chatBar, &ChatBar::hideUserChat, m_messageBar, &MessageBar::hideUserWidget);
    connect(m_chatBar, &ChatBar::deleteUserChat, m_messageBar, &MessageBar::deleteUserWidget);

    connect(m_chatBar, &ChatBar::friendAvatarChanged, m_messageBar, [=](const QString &username)
            { m_messageBar->handleFriendAvatarChanged(username); });

    connect(m_sideBar, &SideBar::myAvatarChanged, m_messageBar, [=]()
            { m_messageBar->handleMyAvatarChanged(); });

    m_messageBar->setVisible(true);
    m_messageBar->setBackgroundColor(245, 245, 245);
    m_messageBar->move(305, 62);
}

void CustomMainWindow::onButtonRestoreClicked()
{
    //传值给侧边栏和状态栏，以处理拖动窗口逻辑
    m_sideBar->m_isMaxWindow = false;
    m_statusBar->m_isMaxWindow = false;
}

void CustomMainWindow::onButtonMaxClicked()
{
    //传值给侧边栏和状态栏，以处理拖动窗口逻辑
    m_sideBar->m_isMaxWindow = true;
    m_statusBar->m_isMaxWindow = true;
}

void CustomMainWindow::closeEvent(QCloseEvent *event)
{
    for (auto pvw : Config::openedPictureViewingWindow)
    {
        qDebug() << pvw;
        if (pvw != nullptr)
        {
            pvw->close();
        }
    }
    return BaseWindow::closeEvent(event);
}
