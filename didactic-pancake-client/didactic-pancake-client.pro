QT       += core gui
QT += network
QT += multimedia
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddFriendWindow.cpp \
    AutoWrapLabel.cpp \
    BaseTitleBar.cpp \
    BaseWindow.cpp \
    ChatBar.cpp \
    ChatItem.cpp \
    Config.cpp \
    FileProcess.cpp \
    FriendBar.cpp \
    FriendInformation.cpp \
    FriendItem.cpp \
    FriendRequestsWindow.cpp \
    FriendRequsetsItem.cpp \
    LabelPlus.cpp \
    LoginWindow.cpp \
    MessageBar.cpp \
    MessageItem.cpp \
    MessageWidget.cpp \
    PictureViewingWindow.cpp \
    RedPoint.cpp \
    RegisterWindow.cpp \
    SQLConnect.cpp \
    SelectNewAvatarWindow.cpp \
    SideBar.cpp \
    SoundPlayer.cpp \
    StatusBar.cpp \
    SuspendedScrollbar.cpp \
    TcpConnect.cpp \
    main.cpp \
    CustomMainWindow.cpp

HEADERS += \
    AddFriendWindow.h \
    AutoWrapLabel.h \
    BaseTitleBar.h \
    BaseWindow.h \
    ChatBar.h \
    ChatItem.h \
    Config.h \
    CustomMainWindow.h \
    FileProcess.h \
    FriendBar.h \
    FriendInformation.h \
    FriendItem.h \
    FriendRequestsWindow.h \
    FriendRequsetsItem.h \
    LabelPlus.h \
    LoginWindow.h \
    MessageBar.h \
    MessageItem.h \
    MessageWidget.h \
    PictureViewingWindow.h \
    RedPoint.h \
    RegisterWindow.h \
    SQLConnect.h \
    SelectNewAvatarWindow.h \
    SideBar.h \
    SoundPlayer.h \
    StatusBar.h \
    SuspendedScrollbar.h \
    TcpConnect.h

FORMS += \
    AddFriendWindow.ui \
    ChatBar.ui \
    ChatItem.ui \
    CustomMainWindow.ui \
    FriendBar.ui \
    FriendInformation.ui \
    FriendItem.ui \
    FriendRequestsWindow.ui \
    FriendRequsetsItem.ui \
    LoginWindow.ui \
    MessageBar.ui \
    MessageWidget.ui \
    PictureViewingWindow.ui \
    RegisterWindow.ui \
    SelectNewAvatarWindow.ui \
    SideBar.ui \
    StatusBar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc

RC_FILE += icon.rc

