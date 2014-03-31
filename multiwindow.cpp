#include "multiwindow.h"
#include "ui_multiwindow.h"
#include <ch2_1.h>
#include <ch2_2.h>


#include <QLabel>
#include <QtGui>
#include <QPainter>
#include <stdio.h>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QtGui/QApplication>
#include <QFileInfo>
#include <QDebug>
#include <QTextCodec>
#include <QStringList>
#include <QDateTime>
#include <qapplication.h>
#include <qlayout.h>

MultiWindow::MultiWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiWindow)
{
    ui->setupUi(this);
    Ch2_1 *w1 = new Ch2_1(this);
     Ch2_2 *w2 = new Ch2_2(this);



    QGridLayout *layout = new QGridLayout;
 //   Plot *plot = new Plot();
 //   layout->addWidget( plot,1,0 );
    layout->addWidget(w1, 1, 0);
    layout->addWidget(w2, 2, 0);

    setLayout(layout);

    setWindowTitle(tr("System Status"));
    setGeometry(100,100,800+60,600+45);

}

MultiWindow::~MultiWindow()
{
    delete ui;
}
