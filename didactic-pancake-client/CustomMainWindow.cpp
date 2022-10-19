#include <windows.h>

#include "CustomMainWindow.h"
#include "ui_CustomMainWindow.h"
#include "LoginWindow.h"

CustomMainWindow::CustomMainWindow(QString sessionID, QString username, QWidget *parent) : BaseWindow(parent),
                                                                                           ui(new Ui::CustomMainWindow),
                                                                                           m_sessionID(sessionID),
                                                                                           m_connect(TcpConnect::getInstance()),
                                                                                           m_sideBar(new SideBar(this)),
                                                                                           m_statusBar(new StatusBar(this)),
                                                                                           m_friendBar(new FriendBar(this)),
                                                                                           m_friendInformation(new FriendInformation(this))
{
    ui->setupUi(this);

    setWindowTitle(username); //将窗口名字设为登录的用户名

    initThis();
    initTitleBar();
    initSideBar();
    initStatusBar();
    initFriendBar();
    initFriendInformationBar();
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

void CustomMainWindow::initSideBar()
{
    m_sideBar->setBackgroundColor(46, 46, 46);
    m_sideBar->move(1, 1);
}

void CustomMainWindow::initStatusBar()
{
    m_statusBar->setBackgroundColor(250, 250, 250);
    m_statusBar->move(55, 1);
}

void CustomMainWindow::initFriendBar()
{
    connect(m_sideBar, &SideBar::changeToChat, this, [=]()
            { m_friendBar->setVisible(false); });
    connect(m_sideBar, &SideBar::changeToFriend, this, [=]()
            { m_friendBar->setVisible(true); });

    m_friendBar->setVisible(false);
    m_friendBar->setBackgroundColor(230, 229, 229);
    m_friendBar->move(55, 63);

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
