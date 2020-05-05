#ifndef INTREPPORT_H
#define INTREPPORT_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>

#include "importPage/roundpushbutton.h"
#include "popUpWindows/SureToCancel.h"

class IntRepportPage : public QWidget
{
        Q_OBJECT
    public:
        explicit IntRepportPage(QWidget *parent = nullptr);

    private:
         QLabel *temp;
         QVBoxLayout        *m_layout;

         RoundPushButton    *m_cancelButton;
         QLabel             *m_cancelLabel;
         RoundPushButton    *m_rescanButton;
         QLabel             *m_rescanLabel;
         RoundPushButton    *m_continueButton;
         QLabel             *m_continueLabel;

         QLabel             *m_titleLabel;
         QLabel             *m_palletIdLabel;
         QLineEdit          *m_palletIdIO;
         QLabel             *m_boxQtyLabel;
         QLineEdit          *m_boxQtyIO;
         QLabel             *m_boxScannedQtyLabel;
         QLineEdit          *m_boxScannedQtyIO;
         QLabel             *m_boxMissingQtyLabel;
         QLineEdit          *m_boxMissingQtyIO;
         QLabel             *m_valueQtyLabel;
         QLineEdit          *m_valueQtyIO;
         QLabel             *m_valueScannedQtyLabel;
         QLineEdit          *m_valueScannedQtyIO;
         QLabel             *m_valueMissingQtyLabel;
         QLineEdit          *m_valueMissingQtyIO;

         SureToCancel       *m_sureToCancel;

    public slots:
         void settempvalue();


};

#endif // INTREPPORT_H
