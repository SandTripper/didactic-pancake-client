/********************************************************************************
** Form generated from reading UI file 'FriendItem.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDITEM_H
#define UI_FRIENDITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FriendItem
{
public:
    QLabel *lbl_user_avatar;
    QLabel *lbl_user_name;

    void setupUi(QWidget *FriendItem)
    {
        if (FriendItem->objectName().isEmpty())
            FriendItem->setObjectName(QString::fromUtf8("FriendItem"));
        FriendItem->resize(249, 60);
        lbl_user_avatar = new QLabel(FriendItem);
        lbl_user_avatar->setObjectName(QString::fromUtf8("lbl_user_avatar"));
        lbl_user_avatar->setGeometry(QRect(12, 13, 34, 34));
        lbl_user_name = new QLabel(FriendItem);
        lbl_user_name->setObjectName(QString::fromUtf8("lbl_user_name"));
        lbl_user_name->setGeometry(QRect(58, 20, 171, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(10);
        lbl_user_name->setFont(font);

        retranslateUi(FriendItem);

        QMetaObject::connectSlotsByName(FriendItem);
    } // setupUi

    void retranslateUi(QWidget *FriendItem)
    {
        FriendItem->setWindowTitle(QCoreApplication::translate("FriendItem", "Form", nullptr));
        lbl_user_avatar->setText(QString());
        lbl_user_name->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FriendItem: public Ui_FriendItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDITEM_H
