#ifndef ROUNDPUSHBUTTON_H
#define ROUNDPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include "globals/globals.h"

class RoundPushButton : public QPushButton
{
    Q_OBJECT
public:
    RoundPushButton(const QString &text, QWidget *parent);
};

#endif // ROUNDPUSHBUTTON_H
