#include "finrepportpage.h"

FinRepportPage::FinRepportPage(QWidget *parent)
    : QWidget(parent)
{
    temp = new QLabel("PAGE FINAL REPPORT", this);
    temp -> setAlignment(Qt::AlignCenter);
    temp -> setStyleSheet("border: 1px solid black");
}
