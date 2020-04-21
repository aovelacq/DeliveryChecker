#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>

#include <info/infobar.h>
#include "globals/globals.h"
#include "SQLTable/sqlview.h"

class DataBaseWindow : public QWidget
{
    Q_OBJECT

public:
    DataBaseWindow(QWidget *parent = nullptr);
    //~DataBaseWindow();

    private:
    InfoBar             *m_infobar;

    QVBoxLayout         *m_dbLayout;

    QComboBox           *m_tableChoice;
    SQLView             *m_table;
    QLineEdit           *m_filter;


};

#endif // DATABASEWINDOW_H
