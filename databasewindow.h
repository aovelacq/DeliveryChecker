#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QLabel>

#include <info/infobar.h>
#include "globals/globals.h"
#include "SQLTable/sqlview.h"
#include "ImprovedLineEdit.h"

class DataBaseWindow : public QDialog
{
    Q_OBJECT

public:
    DataBaseWindow(QWidget *parent = nullptr);
    //~DataBaseWindow();

    private:
    InfoBar             *m_infobar;

    QVBoxLayout         *m_dbLayout;

    QComboBox           *m_selectTable;
    SQLView             *m_table;
    ImprovedLineEdit    *m_filter;
    QLabel              *m_filterCheck;
    QPushButton         *m_okButton;


};

#endif // DATABASEWINDOW_H
