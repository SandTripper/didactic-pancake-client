/********************************************************************************
** Form generated from reading UI file 'FriendRequsetsItem.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDREQUSETSITEM_H
#define UI_FRIENDREQUSETSITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "LabelPlus.h"

QT_BEGIN_NAMESPACE

class Ui_FriendRequsetsItem
{
public:
    LabelPlus *lbl_user_avatar;
    QLabel *lbl_user_name;
    QPushButton *btn_accept;
    QPushButton *btn_reject;

    void setupUi(QWidget *FriendRequsetsItem)
    {
        if (FriendRequsetsItem->objectName().isEmpty())
            FriendRequsetsItem->setObjectName(QString::fromUtf8("FriendRequsetsItem"));
        FriendRequsetsItem->resize(330, 80);
        lbl_user_avatar = new LabelPlus(FriendRequsetsItem);
        lbl_user_avatar->setObjectName(QString::fromUtf8("lbl_user_avatar"));
        lbl_user_avatar->setGeometry(QRect(14, 14, 50, 50));
        lbl_user_name = new QLabel(FriendRequsetsItem);
        lbl_user_name->setObjectName(QString::fromUtf8("lbl_user_name"));
        lbl_user_name->setGeometry(QRect(80, 10, 241, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(11);
        lbl_user_name->setFont(font);
        btn_accept = new QPushButton(FriendRequsetsItem);
        btn_accept->setObjectName(QString::fromUtf8("btn_accept"));
        btn_accept->setGeometry(QRect(190, 44, 51, 23));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font1.setPointSize(10);
        btn_accept->setFont(font1);
        btn_reject = new QPushButton(FriendRequsetsItem);
        btn_reject->setObjectName(QString::fromUtf8("btn_reject"));
        btn_reject->setGeometry(QRect(250, 44, 51, 23));
        btn_reject->setFont(font1);

        retranslateUi(FriendRequsetsItem);

        QMetaObject::connectSlotsByName(FriendRequsetsItem);
    } // setupUi

    void retranslateUi(QWidget *FriendRequsetsItem)
    {
        FriendRequsetsItem->setWindowTitle(QCoreApplication::translate("FriendRequsetsItem", "Form", nullptr));
        lbl_user_avatar->setText(QString());
        lbl_user_name->setText(QString());
        btn_accept->setText(QCoreApplication::translate("FriendRequsetsItem", "\346\216\245\345\217\227\342\210\232", nullptr));
        btn_reject->setText(QCoreApplication::translate("FriendRequsetsItem", "\346\213\222\347\273\235\303\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FriendRequsetsItem: public Ui_FriendRequsetsItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDREQUSETSITEM_H
