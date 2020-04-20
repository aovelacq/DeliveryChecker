#ifndef INFOBAR_H
#define INFOBAR_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>


#include "globals/globals.h"

class InfoBar : public QWidget
{
    Q_OBJECT

    public:
        explicit InfoBar(QWidget *parent = nullptr);
        ~InfoBar();

    private:
        QLabel          *m_Copyright;
        QHBoxLayout     *m_Layout;

    signals:

};

#endif // INFOBAR_H
