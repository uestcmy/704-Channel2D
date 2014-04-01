/********************************************************************************
** Form generated from reading UI file 'channel2d.ui'
**
** Created: Mon Mar 31 16:39:23 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANNEL2D_H
#define UI_CHANNEL2D_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Channel2D
{
public:

    void setupUi(QWidget *Channel2D)
    {
        if (Channel2D->objectName().isEmpty())
            Channel2D->setObjectName(QString::fromUtf8("Channel2D"));
        Channel2D->resize(400, 300);

        retranslateUi(Channel2D);

        QMetaObject::connectSlotsByName(Channel2D);
    } // setupUi

    void retranslateUi(QWidget *Channel2D)
    {
        Channel2D->setWindowTitle(QApplication::translate("Channel2D", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Channel2D: public Ui_Channel2D {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANNEL2D_H
