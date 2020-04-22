#include "intrepportpage.h"


IntRepportPage::IntRepportPage(QWidget *parent)
    : QWidget(parent)
{
   //QObject::connect(this, SIGNAL(resizeEvent()), this, SLOT(settempvalue()));
    temp = new QLabel("PAGE INTERMEDIARY REPPORT", this);
    temp->setText(QString("size = %1").arg(parentWidget()->height()));
    temp -> setAlignment(Qt::AlignCenter);
    temp -> setStyleSheet("border: 1px solid black");
}

void IntRepportPage::settempvalue()
{;
}
