#ifndef PILLSPUSHBUTTON_H
#define PILLSPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include "globals/globals.h"

class PillsPushButton : public QPushButton
{
    Q_OBJECT
public:
    PillsPushButton(const QString &text, QWidget *parent);
};

#endif // PILLSPUSHBUTTON_H
