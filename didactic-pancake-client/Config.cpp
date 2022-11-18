#include "Config.h"

QString Config::loginedUserName = "";
QString Config::loginedSessionID = "";

std::list<PictureViewingWindow *> Config::openedPictureViewingWindow;

int Config::mainWindowPosX = 0;

int Config::mainWindowPosY = 0;

bool Config::isVoiceChatting = false;
