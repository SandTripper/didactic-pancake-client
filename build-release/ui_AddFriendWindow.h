/********************************************************************************
** Form generated from reading UI file 'AddFriendWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRIENDWINDOW_H
#define UI_ADDFRIENDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddFriendWindow
{
public:
    QPushButton *btn_add_friend;
    QLineEdit *edit_user_name;
    QLabel *label;
    QPushButton *btn_search;
    QLabel *lbl_user_name;
    QLabel *lbl_user_avatar;
    QLabel *lbl_wrongtip;

    void setupUi(QWidget *AddFriendWindow)
    {
        if (AddFriendWindow->objectName().isEmpty())
            AddFriendWindow->setObjectName(QString::fromUtf8("AddFriendWindow"));
        AddFriendWindow->resize(284, 301);
        btn_add_friend = new QPushButton(AddFriendWindow);
        btn_add_friend->setObjectName(QString::fromUtf8("btn_add_friend"));
        btn_add_friend->setGeometry(QRect(80, 228, 121, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(10);
        btn_add_friend->setFont(font);
        edit_user_name = new QLineEdit(AddFriendWindow);
        edit_user_name->setObjectName(QString::fromUtf8("edit_user_name"));
        edit_user_name->setEnabled(true);
        edit_user_name->setGeometry(QRect(30, 89, 161, 31));
        edit_user_name->setFont(font);
        edit_user_name->setEchoMode(QLineEdit::Normal);
        label = new QLabel(AddFriendWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 30, 161, 48));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font1.setPointSize(22);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        btn_search = new QPushButton(AddFriendWindow);
        btn_search->setObjectName(QString::fromUtf8("btn_search"));
        btn_search->setGeometry(QRect(203, 89, 51, 31));
        btn_search->setFont(font);
        lbl_user_name = new QLabel(AddFriendWindow);
        lbl_user_name->setObjectName(QString::fromUtf8("lbl_user_name"));
        lbl_user_name->setGeometry(QRect(110, 153, 141, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font2.setPointSize(11);
        lbl_user_name->setFont(font2);
        lbl_user_name->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lbl_user_avatar = new QLabel(AddFriendWindow);
        lbl_user_avatar->setObjectName(QString::fromUtf8("lbl_user_avatar"));
        lbl_user_avatar->setGeometry(QRect(30, 148, 60, 60));
        lbl_wrongtip = new QLabel(AddFriendWindow);
        lbl_wrongtip->setObjectName(QString::fromUtf8("lbl_wrongtip"));
        lbl_wrongtip->setGeometry(QRect(30, 128, 201, 20));
        lbl_wrongtip->setLayoutDirection(Qt::LeftToRight);
        lbl_wrongtip->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(AddFriendWindow);

        QMetaObject::connectSlotsByName(AddFriendWindow);
    } // setupUi

    void retranslateUi(QWidget *AddFriendWindow)
    {
        AddFriendWindow->setWindowTitle(QCoreApplication::translate("AddFriendWindow", "\346\267\273\345\212\240\345\245\275\345\217\213", nullptr));
        btn_add_friend->setText(QCoreApplication::translate("AddFriendWindow", "\346\267\273\345\212\240\345\210\260\351\200\232\350\256\257\345\275\225", nullptr));
        edit_user_name->setPlaceholderText(QCoreApplication::translate("AddFriendWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        label->setText(QCoreApplication::translate("AddFriendWindow", "\346\267\273\345\212\240\345\245\275\345\217\213", nullptr));
        btn_search->setText(QCoreApplication::translate("AddFriendWindow", "\346\220\234\347\264\242", nullptr));
        lbl_user_name->setText(QString());
        lbl_user_avatar->setText(QString());
        lbl_wrongtip->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AddFriendWindow: public Ui_AddFriendWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRIENDWINDOW_H
