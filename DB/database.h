#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QMessageBox>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QStringList>
#include <QApplication>
#include <QLineEdit>
#include <QTableView>
#include <QSqlQueryModel>
#include <QComboBox>

#include "globals/globals.h"
#include "SQLTable/sqlview.h"
#include "importPage/pillspushbutton.h"

class DataBase : public QObject
{
    Q_OBJECT

    public:
        explicit DataBase(QWidget *parent = nullptr);
        bool createConnection();
        bool fillTables();
        bool deleteAllData();
        bool fillItemsTable();
        bool fillJoborderTable();
        bool fillTraceabilityBatchTable();
        bool fillTraceabilityBoxTable();
        bool fillTraceabilityPalletTable();
        bool fillDeliveryTable();
        bool fillDeliveryListTable();
        QString convertDate(QString date);

        const QString getDeliveryName();
        const QString getPalletQty();
        const QString getBoxQty();
        const QString getPackQty();
        const QString getPalletId();
        const QString getBoxQtyOnPallet();
        const QString getPalletValue();
        QSqlQueryModel* getTableData();
        QSqlQueryModel* getDBTableData(int index);

    private slots:
        void sendInformations();

    signals:
        void tableFillingDone();
        void sendDeliveryName(const QString data);
        void sendPalletQty(const QString data);
        void sendBoxQty(const QString data);
        void sendPackQty(const QString data);
        void sendPalletId (QString data);
        void sendBoxQtyOnPallet (QString data);
        void sendPalletValue (QString data);
        void sendTableData(QSqlQueryModel* data);
        void sendDBTableData(QSqlQueryModel* data);
        void sendDone(bool ok);


    private:
        QSqlDatabase    m_DB;
        // Pointers to ImportPage elements
        QLineEdit       *m_ImportPage_DeliveryName;
        QLineEdit       *m_ImportPage_PalletQty;
        QLineEdit       *m_ImportPage_BoxQty;
        QLineEdit       *m_ImportPage_PackQty;
        SQLView         *m_ImportPage_Table;
        PillsPushButton *m_ImportPage_CheckBox;
        // Pointers to IdentifyPage elements
        QLineEdit       *m_IdentifyPage_PalletID;
        QLineEdit       *m_IdentifyPage_BoxID;
        QLineEdit       *m_IdentifyPage_TotalValue;
        QLineEdit       *m_IdentifyPage_BoxQty;
        // Pointers to ScanPage elements
        SQLView         *m_ScanPage_Table;
        // Pointers to IntRepportPage elements
        // Pointers to FinRepportPage elements

        //Pointers to dataBaseWindow elements
        SQLView         *m_DBWindow_Table;
        QComboBox       *m_selectTable;



};

#endif // DATABASE_H
