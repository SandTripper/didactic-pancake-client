/********************************************************************************
** Form generated from reading UI file 'StatusBar.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUSBAR_H
#define UI_STATUSBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatusBar
{
public:
    QPushButton *btn_add_friend;
    QLabel *label;
    QPushButton *btn_network_status;
    QPushButton *btn_process_friend_requests;
    QLabel *lbl_red_point;

    void setupUi(QWidget *StatusBar)
    {
        if (StatusBar->objectName().isEmpty())
            StatusBar->setObjectName(QString::fromUtf8("StatusBar"));
        StatusBar->resize(249, 61);
        btn_add_friend = new QPushButton(StatusBar);
        btn_add_friend->setObjectName(QString::fromUtf8("btn_add_friend"));
        btn_add_friend->setGeometry(QRect(200, 20, 25, 25));
        label = new QLabel(StatusBar);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 61, 25));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(10);
        label->setFont(font);
        btn_network_status = new QPushButton(StatusBar);
        btn_network_status->setObjectName(QString::fromUtf8("btn_network_status"));
        btn_network_status->setEnabled(false);
        btn_network_status->setGeometry(QRect(80, 20, 40, 25));
        btn_network_status->setFont(font);
        btn_process_friend_requests = new QPushButton(StatusBar);
        btn_process_friend_requests->setObjectName(QString::fromUtf8("btn_process_friend_requests"));
        btn_process_friend_requests->setGeometry(QRect(160, 20, 25, 25));
        lbl_red_point = new QLabel(StatusBar);
        lbl_red_point->setObjectName(QString::fromUtf8("lbl_red_point"));
        lbl_red_point->setGeometry(QRect(180, 18, 7, 7));

        retranslateUi(StatusBar);

        QMetaObject::connectSlotsByName(StatusBar);
    } // setupUi

    void retranslateUi(QWidget *StatusBar)
    {
        StatusBar->setWindowTitle(QCoreApplication::translate("StatusBar", "Form", nullptr));
        btn_add_friend->setText(QString());
        label->setText(QCoreApplication::translate("StatusBar", "\347\275\221\347\273\234\347\212\266\345\206\265:", nullptr));
        btn_network_status->setText(QCoreApplication::translate("StatusBar", "\344\274\230\347\247\200", nullptr));
        btn_process_friend_requests->setText(QString());
        lbl_red_point->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StatusBar: public Ui_StatusBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSBAR_H
