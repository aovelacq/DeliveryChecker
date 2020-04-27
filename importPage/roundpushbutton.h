#ifndef ROUNDPUSHBUTTON_H
#define ROUNDPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include "globals/globals.h"

class RoundPushButton : public QPushButton
{
    Q_OBJECT
public:
    RoundPushButton(const QString &imgURLOff, const QString &imgURLOn, QWidget *parent = nullptr);
};

#endif // ROUNDPUSHBUTTON_H
