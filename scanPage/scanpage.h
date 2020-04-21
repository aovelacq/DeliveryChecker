#ifndef SCANPAGE_H
#define SCANPAGE_H

#include <QWidget>
#include <QLabel>

class ScanPage : public QWidget
{
        Q_OBJECT
    public:
        explicit ScanPage(QWidget *parent = nullptr);

    private:
         QLabel *temp;

};

#endif // SCANPAGE_H
