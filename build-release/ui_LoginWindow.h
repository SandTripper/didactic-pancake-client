/********************************************************************************
** Form generated from reading UI file 'LoginWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "LabelPlus.h"

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QPushButton *btn_login;
    QLineEdit *edit_username;
    QLineEdit *edit_password;
    QCheckBox *chk_remember_user;
    QLabel *label;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    LabelPlus *lbl_register;
    QLabel *lbl_wrongtip;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QString::fromUtf8("LoginWindow"));
        LoginWindow->resize(284, 301);
        btn_login = new QPushButton(LoginWindow);
        btn_login->setObjectName(QString::fromUtf8("btn_login"));
        btn_login->setGeometry(QRect(30, 220, 221, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(10);
        btn_login->setFont(font);
        edit_username = new QLineEdit(LoginWindow);
        edit_username->setObjectName(QString::fromUtf8("edit_username"));
        edit_username->setEnabled(true);
        edit_username->setGeometry(QRect(30, 92, 221, 31));
        edit_username->setFont(font);
        edit_username->setEchoMode(QLineEdit::Normal);
        edit_password = new QLineEdit(LoginWindow);
        edit_password->setObjectName(QString::fromUtf8("edit_password"));
        edit_password->setGeometry(QRect(30, 143, 221, 31));
        edit_password->setFont(font);
        edit_password->setEchoMode(QLineEdit::Password);
        chk_remember_user = new QCheckBox(LoginWindow);
        chk_remember_user->setObjectName(QString::fromUtf8("chk_remember_user"));
        chk_remember_user->setGeometry(QRect(30, 175, 71, 31));
        chk_remember_user->setMouseTracking(true);
        label = new QLabel(LoginWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 40, 61, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font1.setPointSize(22);
        label->setFont(font1);
        gridLayoutWidget = new QWidget(LoginWindow);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(90, 260, 104, 21));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(3);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        lbl_register = new LabelPlus(gridLayoutWidget);
        lbl_register->setObjectName(QString::fromUtf8("lbl_register"));

        gridLayout->addWidget(lbl_register, 0, 1, 1, 1);

        lbl_wrongtip = new QLabel(LoginWindow);
        lbl_wrongtip->setObjectName(QString::fromUtf8("lbl_wrongtip"));
        lbl_wrongtip->setGeometry(QRect(100, 182, 151, 16));
        lbl_wrongtip->setLayoutDirection(Qt::LeftToRight);
        lbl_wrongtip->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Form", nullptr));
        btn_login->setText(QCoreApplication::translate("LoginWindow", "\347\231\273\345\275\225", nullptr));
        edit_username->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        edit_password->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\345\257\206\347\240\201", nullptr));
        chk_remember_user->setText(QCoreApplication::translate("LoginWindow", "\350\256\260\344\275\217\350\264\246\345\217\267", nullptr));
        label->setText(QCoreApplication::translate("LoginWindow", "\347\231\273\345\275\225", nullptr));
        label_2->setText(QCoreApplication::translate("LoginWindow", "\346\262\241\346\234\211\350\264\246\345\217\267", nullptr));
        lbl_register->setText(QCoreApplication::translate("LoginWindow", "\347\253\213\345\215\263\346\263\250\345\206\214", nullptr));
        lbl_wrongtip->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
