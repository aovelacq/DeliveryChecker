#include "intrepportpage.h"

IntRepportPage::IntRepportPage(QWidget *parent)
    : QWidget(parent)
{
    temp = new QLabel("PAGE INTERMEDIARY REPPORT", this);
    temp -> setAlignment(Qt::AlignCenter);
    temp -> setStyleSheet("border: 1px solid black");
}
