/********************************************************************************
** Form generated from reading UI file 'multiwindow.ui'
**
** Created: Mon Mar 31 16:39:23 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTIWINDOW_H
#define UI_MULTIWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MultiWindow
{
public:

    void setupUi(QWidget *MultiWindow)
    {
        if (MultiWindow->objectName().isEmpty())
            MultiWindow->setObjectName(QString::fromUtf8("MultiWindow"));
        MultiWindow->resize(400, 300);

        retranslateUi(MultiWindow);

        QMetaObject::connectSlotsByName(MultiWindow);
    } // setupUi

    void retranslateUi(QWidget *MultiWindow)
    {
        MultiWindow->setWindowTitle(QApplication::translate("MultiWindow", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MultiWindow: public Ui_MultiWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTIWINDOW_H
