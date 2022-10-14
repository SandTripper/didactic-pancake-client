#include <windows.h>

#include "CustomMainWindow.h"
#include "ui_CustomMainWindow.h"
#include "LoginWindow.h"

CustomMainWindow::CustomMainWindow(std::string sessionID, QWidget *parent) : BaseWindow(parent),
                                                                             ui(new Ui::CustomMainWindow),
                                                                             m_sessionID(sessionID)
{

    initTitleBar();
    initSideBar();
    initStatusBar();

    ui->setupUi(this);

    //获取与服务器的连接
    m_connect = TcpConnect::getInstance();

    setBackgroundColor(214, 214, 214);

    m_titleBar->raise();
    m_sideBar->raise();
    m_statusBar->raise();
}

CustomMainWindow::~CustomMainWindow()
{
    delete m_sideBar;
    delete m_statusBar;
    delete ui;
}

void CustomMainWindow::onButtonRestoreClicked()
{
    m_sideBar->m_isMaxWindow = false;
    m_statusBar->m_isMaxWindow = false;
}

void CustomMainWindow::onButtonMaxClicked()
{
    m_sideBar->m_isMaxWindow = true;
    m_statusBar->m_isMaxWindow = true;
}



void CustomMainWindow::initTitleBar()
{

    connect(m_titleBar, SIGNAL(signalButtonRestoreClicked()), this, SLOT(onButtonRestoreClicked()));
    connect(m_titleBar, SIGNAL(signalButtonMaxClicked()), this, SLOT(onButtonMaxClicked()));

    m_titleBar->setBackgroundColor(245, 246, 247);
    m_titleBar->setButtonType(MIN_MAX_BUTTON);
    m_titleBar->setTitleWidth(this->width());
    m_titleBar->setTitleHeight(61);

    m_titleBar->m_x = 305;

    m_titleBar->move(m_titleBar->m_x, 1);
}

void CustomMainWindow::initSideBar()
{

    m_sideBar = new SideBar(this);
    m_sideBar->setBackgroundColor(46, 46, 46);
    m_sideBar->move(1, 1);
}

void CustomMainWindow::initStatusBar()
{
    m_statusBar = new StatusBar(this);
    m_statusBar->setBackgroundColor(250, 250, 250);
    m_statusBar->move(55, 1);
}
