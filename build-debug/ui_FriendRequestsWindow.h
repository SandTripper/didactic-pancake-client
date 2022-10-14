/********************************************************************************
** Form generated from reading UI file 'FriendRequestsWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDREQUESTSWINDOW_H
#define UI_FRIENDREQUESTSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include "FriendRequsetsItem.h"

QT_BEGIN_NAMESPACE

class Ui_FriendRequestsWindow
{
public:
    FriendRequsetsListWidget *listWidget;
    QLabel *label;

    void setupUi(QWidget *FriendRequestsWindow)
    {
        if (FriendRequestsWindow->objectName().isEmpty())
            FriendRequestsWindow->setObjectName(QString::fromUtf8("FriendRequestsWindow"));
        FriendRequestsWindow->resize(400, 300);
        listWidget = new FriendRequsetsListWidget(FriendRequestsWindow);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(35, 90, 330, 191));
        label = new QLabel(FriendRequestsWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 30, 161, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(22);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(FriendRequestsWindow);

        QMetaObject::connectSlotsByName(FriendRequestsWindow);
    } // setupUi

    void retranslateUi(QWidget *FriendRequestsWindow)
    {
        FriendRequestsWindow->setWindowTitle(QCoreApplication::translate("FriendRequestsWindow", "Form", nullptr));
        label->setText(QCoreApplication::translate("FriendRequestsWindow", "\345\245\275\345\217\213\347\224\263\350\257\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FriendRequestsWindow: public Ui_FriendRequestsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDREQUESTSWINDOW_H
