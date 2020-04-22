#ifndef FINREPPORTPAGE_H
#define FINREPPORTPAGE_H

#include <QWidget>
#include <QLabel>

class FinRepportPage : public QWidget
{
        Q_OBJECT
    public:
        explicit FinRepportPage(QWidget *parent = nullptr);


    private:
         QLabel *temp;

};

#endif // FINREPPORTPAGE_H
