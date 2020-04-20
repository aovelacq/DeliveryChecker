#include "identifypage.h"

IdentifyPage::IdentifyPage(QWidget *parent)
    : QWidget(parent)
{
    temp = new QLabel("PAGE IDENTIFY", this);
    temp -> setAlignment(Qt::AlignCenter);
    temp -> setStyleSheet("border: 1px solid black");
}
