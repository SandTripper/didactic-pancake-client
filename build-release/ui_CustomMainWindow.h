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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomMainWindow
{
public:

    void setupUi(QWidget *CustomMainWindow)
    {
        if (CustomMainWindow->objectName().isEmpty())
            CustomMainWindow->setObjectName(QString::fromUtf8("CustomMainWindow"));
        CustomMainWindow->resize(702, 502);

        retranslateUi(CustomMainWindow);

        QMetaObject::connectSlotsByName(CustomMainWindow);
    } // setupUi

    void retranslateUi(QWidget *CustomMainWindow)
    {
        CustomMainWindow->setWindowTitle(QCoreApplication::translate("CustomMainWindow", "CustomMainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CustomMainWindow: public Ui_CustomMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMMAINWINDOW_H
