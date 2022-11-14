#include <QApplication>
#include <QDebug>
#include <string>

#include "CustomMainWindow.h"
#include "LoginWindow.h"
#include "FriendRequsetsItem.h"
#include "Config.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设置任务栏图标
    a.setWindowIcon(QIcon(":/resource/pancake.png"));
    //取消焦点虚线框
    qApp->setStyleSheet("*{outline:0px;}");

    //首先运行登录窗口
    LoginWindow login;
    LoginData loginData = login.exec();
    // LoginData loginData = LoginData{"111","admin",900,600};

    if (loginData.sessionID != "") //登录成功，获取到sessionID，进入主窗口
    {
        Config::loginedUserName = loginData.username;
        Config::loginedSessionID = loginData.sessionID;
        SQLConnect::getInstance()->initUserDataConnect(loginData.username);
        CustomMainWindow w;
        w.move(loginData.x, loginData.y); //移动到和登录窗口一样的位置
        w.show();
        return a.exec();
    }

    return 0;
}
