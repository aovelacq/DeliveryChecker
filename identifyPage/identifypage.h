#ifndef IDENTIFYPAGE_H
#define IDENTIFYPAGE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QDialog>

#include "globals/globals.h"
#include "sideMenu/MenuButton.h"
#include "importPage/roundpushbutton.h"
#include "popUpWindows/ProductNotFound.h"

class IdentifyPage : public QWidget
{
    Q_OBJECT
public:
    IdentifyPage(QWidget *parent = nullptr);

public slots:
    void clearIdentifyPage(const QString);

private:
     QVBoxLayout         *m_layout;

     QLabel              *m_scanText;
     QLabel              *m_ImageQR;

     RoundPushButton     *m_cancelButton;
     QLabel              *m_cancelLabel;
     RoundPushButton     *m_continueButton;
     QLabel              *m_continueLabel;

     QLabel              *m_boxIdLabel;
     QLineEdit           *m_boxIdIO;
     QLabel              *m_palletIdLabel;
     QLineEdit           *m_palletIdIO;
     QLabel              *m_boxQtyLabel;
     QLineEdit           *m_boxQtyIO;
     QLabel              *m_totalValueLabel;
     QLineEdit           *m_totalValueIO;

     ProductNotFound     *m_productNotFound;
};

#endif // IDENTIFYPAGE_H
