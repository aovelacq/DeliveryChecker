#ifndef IDENTIFYPAGE_H
#define IDENTIFYPAGE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

#include "globals/globals.h"
#include "sideMenu/MenuButton.h"
#include "importPage/roundpushbutton.h"
#include "DB/database.h"

class IdentifyPage : public QWidget
{
    Q_OBJECT
public:
    IdentifyPage(QWidget *parent = nullptr);

public slots :
    void accessContinue();
    void noaccessContinue(const QString i);
    bool getData();

private:
     //QLabel *temp;

     QVBoxLayout         *m_layout;
     RoundPushButton     *m_cancelButton;
     QLabel              *m_cancelLabel;
     RoundPushButton     *m_continueButton;
     QLabel              *m_continueLabel;
     QLabel              *m_scanText;
     QLabel              *m_boxIdLabel;
     QLineEdit           *m_boxIdIO;
     QLabel              *m_palletIdLabel;
     QLineEdit           *m_palletIdIO;
     QLabel              *m_boxQtyLabel;
     QLineEdit           *m_boxQtyIO;
     QLabel              *m_totalValueLabel;
     QLineEdit           *m_totalValueIO;

};

#endif // IDENTIFYPAGE_H
