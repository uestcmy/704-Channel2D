/********************************************************************************
** Form generated from reading UI file 'subwindow.ui'
**
** Created: Sat Apr 12 10:30:41 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBWINDOW_H
#define UI_SUBWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SubWindow
{
public:

    void setupUi(QWidget *SubWindow)
    {
        if (SubWindow->objectName().isEmpty())
            SubWindow->setObjectName(QString::fromUtf8("SubWindow"));
        SubWindow->resize(400, 300);

        retranslateUi(SubWindow);

        QMetaObject::connectSlotsByName(SubWindow);
    } // setupUi

    void retranslateUi(QWidget *SubWindow)
    {
        SubWindow->setWindowTitle(QApplication::translate("SubWindow", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SubWindow: public Ui_SubWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBWINDOW_H
