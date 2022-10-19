/********************************************************************************
** Form generated from reading UI file 'RegisterWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWINDOW_H
#define UI_REGISTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterWindow
{
public:
    QPushButton *btn_register;
    QLineEdit *edit_username;
    QLineEdit *edit_password1;
    QLabel *label;
    QLabel *lbl_wrongtip;
    QLineEdit *edit_password2;

    void setupUi(QWidget *RegisterWindow)
    {
        if (RegisterWindow->objectName().isEmpty())
            RegisterWindow->setObjectName(QString::fromUtf8("RegisterWindow"));
        RegisterWindow->resize(284, 301);
        btn_register = new QPushButton(RegisterWindow);
        btn_register->setObjectName(QString::fromUtf8("btn_register"));
        btn_register->setGeometry(QRect(30, 230, 221, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(10);
        btn_register->setFont(font);
        edit_username = new QLineEdit(RegisterWindow);
        edit_username->setObjectName(QString::fromUtf8("edit_username"));
        edit_username->setEnabled(true);
        edit_username->setGeometry(QRect(30, 85, 221, 31));
        edit_username->setFont(font);
        edit_username->setEchoMode(QLineEdit::Normal);
        edit_password1 = new QLineEdit(RegisterWindow);
        edit_password1->setObjectName(QString::fromUtf8("edit_password1"));
        edit_password1->setGeometry(QRect(30, 131, 221, 31));
        edit_password1->setFont(font);
        edit_password1->setEchoMode(QLineEdit::Password);
        label = new QLabel(RegisterWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 30, 161, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font1.setPointSize(22);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        lbl_wrongtip = new QLabel(RegisterWindow);
        lbl_wrongtip->setObjectName(QString::fromUtf8("lbl_wrongtip"));
        lbl_wrongtip->setGeometry(QRect(30, 210, 151, 16));
        lbl_wrongtip->setLayoutDirection(Qt::LeftToRight);
        lbl_wrongtip->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        edit_password2 = new QLineEdit(RegisterWindow);
        edit_password2->setObjectName(QString::fromUtf8("edit_password2"));
        edit_password2->setGeometry(QRect(30, 175, 221, 31));
        edit_password2->setFont(font);
        edit_password2->setEchoMode(QLineEdit::Password);

        retranslateUi(RegisterWindow);

        QMetaObject::connectSlotsByName(RegisterWindow);
    } // setupUi

    void retranslateUi(QWidget *RegisterWindow)
    {
        RegisterWindow->setWindowTitle(QCoreApplication::translate("RegisterWindow", "\346\263\250\345\206\214", nullptr));
        btn_register->setText(QCoreApplication::translate("RegisterWindow", "\346\263\250\345\206\214", nullptr));
        edit_username->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        edit_password1->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "\345\257\206\347\240\201", nullptr));
        label->setText(QCoreApplication::translate("RegisterWindow", "\346\263\250\345\206\214", nullptr));
        lbl_wrongtip->setText(QString());
        edit_password2->setPlaceholderText(QCoreApplication::translate("RegisterWindow", "\345\206\215\346\254\241\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterWindow: public Ui_RegisterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWINDOW_H
