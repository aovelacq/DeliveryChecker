#ifndef FINREPPORTPAGE_H
#define FINREPPORTPAGE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QApplication>

#include "SQLTable/sqlview.h"
#include "importPage/roundpushbutton.h"
#include "pdf/pdfreport.h"

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

         QLabel             *m_ExitLabel;
         RoundPushButton    *m_ExitButton;
         QLabel             *m_SaveLabel;
         RoundPushButton    *m_SaveButton;

         PdfReport          *m_Report;

};

#endif // FINREPPORTPAGE_H
