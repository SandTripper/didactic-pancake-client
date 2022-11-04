/********************************************************************************
** Form generated from reading UI file 'SideBar.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDEBAR_H
#define UI_SIDEBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "LabelPlus.h"
#include "RedPoint.h"

QT_BEGIN_NAMESPACE

class Ui_SideBar
{
public:
    QPushButton *btn_change_to_chat;
    QPushButton *btn_change_to_friend;
    LabelPlus *lbl_user_avatar;
    RedPoint *lbl_redpoint;

    void setupUi(QWidget *SideBar)
    {
        if (SideBar->objectName().isEmpty())
            SideBar->setObjectName(QString::fromUtf8("SideBar"));
        SideBar->setEnabled(true);
        SideBar->resize(54, 500);
        btn_change_to_chat = new QPushButton(SideBar);
        btn_change_to_chat->setObjectName(QString::fromUtf8("btn_change_to_chat"));
        btn_change_to_chat->setGeometry(QRect(2, 89, 51, 41));
        btn_change_to_friend = new QPushButton(SideBar);
        btn_change_to_friend->setObjectName(QString::fromUtf8("btn_change_to_friend"));
        btn_change_to_friend->setGeometry(QRect(2, 130, 51, 41));
        lbl_user_avatar = new LabelPlus(SideBar);
        lbl_user_avatar->setObjectName(QString::fromUtf8("lbl_user_avatar"));
        lbl_user_avatar->setEnabled(true);
        lbl_user_avatar->setGeometry(QRect(10, 37, 36, 36));
        lbl_redpoint = new RedPoint(SideBar);
        lbl_redpoint->setObjectName(QString::fromUtf8("lbl_redpoint"));
        lbl_redpoint->setGeometry(QRect(32, 96, 16, 16));

        retranslateUi(SideBar);

        QMetaObject::connectSlotsByName(SideBar);
    } // setupUi

    void retranslateUi(QWidget *SideBar)
    {
        SideBar->setWindowTitle(QCoreApplication::translate("SideBar", "Form", nullptr));
        btn_change_to_chat->setText(QString());
        btn_change_to_friend->setText(QString());
        lbl_user_avatar->setText(QString());
        lbl_redpoint->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SideBar: public Ui_SideBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEBAR_H
