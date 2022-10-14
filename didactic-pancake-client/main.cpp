#include <QApplication>
#include <QDebug>
#include <string>

#include "CustomMainWindow.h"
#include "LoginWindow.h"

#include "FriendRequsetsItem.h"

using namespace std;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    FriendRequsetsItem x;
//    x.show();
//    return a.exec();

    LoginWindow login;
    string sessionID = login.exec();
    //string sessionID = "111";
    if (sessionID != "")
    {
        CustomMainWindow w(sessionID);
        w.show();
        return a.exec();
    }

    return 0;
}
