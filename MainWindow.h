#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sideMenu/SideMenu.h"
#include "info/infobar.h"
#include "importPage/importpage.h"
#include "identifyPage/identifypage.h"
#include "DB/database.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QStackedWidget>
#include <QDebug>
#include <QDateTime>

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
       explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        bool createLogFile(const QString);
        static void appendLogFile (const QString path, const QString data);

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
        QPushButton         *temp;                      // TEMPORARY
        QSpacerItem         *m_spacer;

        ImportPage          *importPage;
        IdentifyPage        *identifyPage;
        QWidget             *scanPage;
        QWidget             *intermediaryRepportPage;
        QWidget             *finalRepportPage;
        InfoBar             *m_infobar;                 // infobar

        DataBase            *DB;
};

#endif // MAINWINDOW_H
