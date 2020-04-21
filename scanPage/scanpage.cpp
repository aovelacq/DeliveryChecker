#include "scanpage.h"

ScanPage::ScanPage(QWidget *parent)
    : QWidget(parent)
{
    temp = new QLabel("PAGE SCAN", this);
    temp -> setAlignment(Qt::AlignCenter);
    temp -> setStyleSheet("border: 1px solid black");
}
