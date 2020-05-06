#ifndef FINREPPORTPAGE_H
#define FINREPPORTPAGE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>

#include "SQLTable/sqlview.h"
#include "importPage/roundpushbutton.h"

class FinRepportPage : public QWidget
{
        Q_OBJECT
    public:
        explicit FinRepportPage(QWidget *parent = nullptr);


    private:
         QVBoxLayout        *m_Layout;

         QLabel             *m_titleLabel;
         QLabel             *m_PalletLabel;
         SQLView            *m_PalletView;
         QLabel             *m_BoxScannedLabel;
         SQLView            *m_BoxScannedView;
         QLabel             *m_BoxMissingLabel;
         SQLView            *m_BoxMissingView;

         QLabel             *m_CancelLabel;
         RoundPushButton    *m_CancelButton;
         QLabel             *m_SaveLabel;
         RoundPushButton    *m_SaveButton;

};

#endif // FINREPPORTPAGE_H
