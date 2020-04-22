#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

#include <info/infobar.h>
#include "globals/globals.h"
#include "SQLTable/sqlview.h"

class DataBaseWindow : public QWidget
{
    Q_OBJECT

public:
    DataBaseWindow(QWidget *parent = nullptr);
    //~DataBaseWindow();

public slots:
    void changeTable(int index);
    void filterTable();

    private:
    InfoBar             *m_infobar;

    QVBoxLayout         *m_dbLayout;

    QComboBox           *m_tableChoice;
    SQLView             *m_table;
    QLineEdit           *m_filter;
    QPushButton         *m_okButton;


};

#endif // DATABASEWINDOW_H
