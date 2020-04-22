#ifndef INTREPPORT_H
#define INTREPPORT_H

#include <QWidget>
#include <QLabel>

class IntRepportPage : public QWidget
{
        Q_OBJECT
    public:
        explicit IntRepportPage(QWidget *parent = nullptr);

    private:
         QLabel *temp;

};

#endif // INTREPPORT_H
