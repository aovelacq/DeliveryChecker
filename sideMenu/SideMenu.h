#ifndef SIDEMENU_H
#define SIDEMENU_H

#include "MenuButton.h"
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QStackedWidget>
#include <QtDebug>

#include "globals/globals.h"
#include "importPage/pillspushbutton.h"
#include "importPage/roundpushbutton.h"

class SideMenu : public QWidget
{
    Q_OBJECT

    public:
        SideMenu(QWidget *parent  = nullptr);
        ~SideMenu();

    private:
        QVBoxLayout *m_Layout;              // Layout inside the menu
        MenuButton  *m_boutonImport;        // Button import
        QSpacerItem *spacer;
        MenuButton  *m_boutonIdentify;      // Button Identify
        MenuButton  *m_boutonScan;          // Button Scan
        MenuButton  *m_boutonIntRepport;       // Button Repport
        MenuButton  *m_boutonFinRepport;         // Button Print

        PillsPushButton *m_ImportPage_checkBox;
        RoundPushButton *m_IdentifyPage_continueButton;
        RoundPushButton *m_IdentifyPage_cancelButton;


    signals:
};

#endif // SIDEMENU_H
