#ifndef SCANPAGE_H
#define SCANPAGE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>

#include "importPage/roundpushbutton.h"
#include "SQLTable/sqlview.h"

class ScanPage : public QWidget
{
        Q_OBJECT
    public:
        explicit ScanPage(QWidget *parent = nullptr);

    private:
         QGridLayout        *m_layout;

         QHBoxLayout        *m_layoutTextQR;
         QLabel             *m_TextQR;
         QLabel             *m_ImageQR;

         QHBoxLayout        *m_layoutTextIO;
         QLabel             *m_TextIO;
         QLineEdit          *m_BoxRef;

         SQLView            *m_Table;

         QVBoxLayout        *m_CancelButtonLayout;
         RoundPushButton    *m_CancelButton;
         QLabel             *m_CancelButtonText;

         QVBoxLayout        *m_ContinueButtonLayout;
         RoundPushButton    *m_ContinueButton;
         QLabel             *m_ContinueButtonText;



};

#endif // SCANPAGE_H
