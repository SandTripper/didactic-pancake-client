/********************************************************************************
** Form generated from reading UI file 'FriendInformation.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDINFORMATION_H
#define UI_FRIENDINFORMATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "LabelPlus.h"

QT_BEGIN_NAMESPACE

class Ui_FriendInformation
{
public:
    LabelPlus *lbl_user_avatar;
    QLabel *lbl_user_name;
    QPushButton *btn_send_message;
    QLabel *lbl_background;

    void setupUi(QWidget *FriendInformation)
    {
        if (FriendInformation->objectName().isEmpty())
            FriendInformation->setObjectName(QString::fromUtf8("FriendInformation"));
        FriendInformation->resize(396, 439);
        lbl_user_avatar = new LabelPlus(FriendInformation);
        lbl_user_avatar->setObjectName(QString::fromUtf8("lbl_user_avatar"));
        lbl_user_avatar->setGeometry(QRect(60, 110, 100, 100));
        lbl_user_name = new QLabel(FriendInformation);
        lbl_user_name->setObjectName(QString::fromUtf8("lbl_user_name"));
        lbl_user_name->setGeometry(QRect(180, 130, 191, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(14);
        lbl_user_name->setFont(font);
        btn_send_message = new QPushButton(FriendInformation);
        btn_send_message->setObjectName(QString::fromUtf8("btn_send_message"));
        btn_send_message->setGeometry(QRect(143, 270, 110, 32));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font1.setPointSize(10);
        btn_send_message->setFont(font1);
        lbl_background = new QLabel(FriendInformation);
        lbl_background->setObjectName(QString::fromUtf8("lbl_background"));
        lbl_background->setGeometry(QRect(70, 80, 256, 256));

        retranslateUi(FriendInformation);

        QMetaObject::connectSlotsByName(FriendInformation);
    } // setupUi

    void retranslateUi(QWidget *FriendInformation)
    {
        FriendInformation->setWindowTitle(QCoreApplication::translate("FriendInformation", "Form", nullptr));
        lbl_user_avatar->setText(QString());
        lbl_user_name->setText(QString());
        btn_send_message->setText(QCoreApplication::translate("FriendInformation", "\345\217\221\346\266\210\346\201\257", nullptr));
        lbl_background->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FriendInformation: public Ui_FriendInformation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDINFORMATION_H
