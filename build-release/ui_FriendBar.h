/********************************************************************************
** Form generated from reading UI file 'FriendBar.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDBAR_H
#define UI_FRIENDBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include "FriendItem.h"

QT_BEGIN_NAMESPACE

class Ui_FriendBar
{
public:
    FriendListWidget *listWidget;

    void setupUi(QWidget *FriendBar)
    {
        if (FriendBar->objectName().isEmpty())
            FriendBar->setObjectName(QString::fromUtf8("FriendBar"));
        FriendBar->resize(249, 438);
        listWidget = new FriendListWidget(FriendBar);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 249, 438));

        retranslateUi(FriendBar);

        QMetaObject::connectSlotsByName(FriendBar);
    } // setupUi

    void retranslateUi(QWidget *FriendBar)
    {
        FriendBar->setWindowTitle(QCoreApplication::translate("FriendBar", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FriendBar: public Ui_FriendBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDBAR_H
