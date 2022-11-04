/********************************************************************************
** Form generated from reading UI file 'CustomMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMMAINWINDOW_H
#define UI_CUSTOMMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomMainWindow
{
public:
    QLabel *lbl_chatUsername;

    void setupUi(QWidget *CustomMainWindow)
    {
        if (CustomMainWindow->objectName().isEmpty())
            CustomMainWindow->setObjectName(QString::fromUtf8("CustomMainWindow"));
        CustomMainWindow->resize(702, 502);
        lbl_chatUsername = new QLabel(CustomMainWindow);
        lbl_chatUsername->setObjectName(QString::fromUtf8("lbl_chatUsername"));
        lbl_chatUsername->setGeometry(QRect(329, 24, 281, 18));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(12);
        lbl_chatUsername->setFont(font);

        retranslateUi(CustomMainWindow);

        QMetaObject::connectSlotsByName(CustomMainWindow);
    } // setupUi

    void retranslateUi(QWidget *CustomMainWindow)
    {
        CustomMainWindow->setWindowTitle(QCoreApplication::translate("CustomMainWindow", "CustomMainWindow", nullptr));
        lbl_chatUsername->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CustomMainWindow: public Ui_CustomMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMMAINWINDOW_H
