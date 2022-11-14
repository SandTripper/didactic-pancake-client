#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

#include <list>

class PictureViewingWindow;

class Config
{
public:
    //当前已登录的用户名
    static QString loginedUserName;

    //当前登录的sessionID
    static QString loginedSessionID;

    //已打开的图片查看器
    static std::list<PictureViewingWindow *> openedPictureViewingWindow;
};

#endif // CONFIG_H
