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

        const QString   getImportPageDeliveryName();
        const QString   getImportPagePalletQty();
        const QString   getImportPageBoxQty();
        const QString   getImportPagePackQty();
        QSqlQueryModel* getImportPageTableData();

    private slots:
        void sendImportPageInformations();

    signals:
        //Internal
        void tableFillingDone();
        // Related to Import Page
        void sendImportPageDeliveryName(const QString data);
        void sendImportPagePalletQty(const QString data);
        void sendImportPageBoxQty(const QString data);
        void sendImportPagePackQty(const QString data);
        void sendImportPageTableData(QSqlQueryModel* data);
        void sendImportPageDone(bool ok);

        //Related to Identify Page

        //Related to Scan Page
        void sendScanPageTableData(QSqlQueryModel* data);

        //Related to Intermediary Repport Page

        //Related to Final Repport Page



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
        // Pointers to ScanPage elements
        SQLView         *m_ScanPage_Table;
        int             palletScanned = 3;
        // Pointers to IntRepportPage elements
        // Pointers to FinRepportPage elements




};

#endif // DATABASE_H
