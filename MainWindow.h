#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sideMenu/SideMenu.h"
#include "info/infobar.h"
#include "importPage/importpage.h"
#include "identifyPage/identifypage.h"
#include "scanPage/scanpage.h"
#include "intRepport/intrepportpage.h"
#include "finRepport/finrepportpage.h"
#include "DB/database.h"
#include "dataBaseWindow/databasewindow.h"
#include "loadAnim/loadanim.h"
#include "popUpWindows/SureToCancel.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QStackedWidget>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>
#include <QPainter>

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
       explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        bool createLogFile(const QString);
        static void appendLogFile (const QString path, const QString data);
        LoadAnim            *Loading;

    public slots:
        void setImportPage();
        void setIdentifyPage();
        void setScanPage();
        void setIntRepportPage();
        void setFinRepportPage();

    private:
        QHBoxLayout         *m_mainLayout;              // Layout for side menu
        SideMenu            *m_menu;                   // Side menu
        QStackedWidget      *stackedWidget;

        QVBoxLayout         *m_infoLayout;              // Layout for info bar

        ImportPage          *importPage;
        IdentifyPage        *identifyPage;
        ScanPage            *scanPage;
        IntRepportPage      *intRepportPage;
        FinRepportPage      *finRepportPage;
        InfoBar             *m_infobar;                 // infobar

        DataBase            *DB;

        DataBaseWindow      *m_windowDB;

        QLineEdit           *m_IdentifyPage_PalletID;
        QLineEdit           *m_IdentifyPage_BoxID;
        QLineEdit           *m_IdentifyPage_TotalValue;
        QLineEdit           *m_IdentifyPage_BoxQty;


    protected:
        void paintEvent(QPaintEvent *event);

};

#endif // MAINWINDOW_H
