#ifndef IDENTIFYPAGE_H
#define IDENTIFYPAGE_H

#include <QWidget>
#include <QLabel>

class IdentifyPage : public QWidget
{
    Q_OBJECT
public:
    IdentifyPage(QWidget *parent = nullptr);
private:
     QLabel *temp;
};

#endif // IDENTIFYPAGE_H
