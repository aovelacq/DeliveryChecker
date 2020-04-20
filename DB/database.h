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

class DataBase : public QObject
{
    Q_OBJECT

    public:
        explicit DataBase(QWidget *parent);
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
        QSqlQueryModel* getTableData();

    private slots:
        void sendInformations();

    signals:
        void tableFillingDone();
        void sendDeliveryName(const QString data);
        void sendPalletQty(const QString data);
        void sendBoxQty(const QString data);
        void sendPackQty(const QString data);
        void sendTableData(QSqlQueryModel* data);

    private:
        QSqlDatabase    m_DB;
        QLineEdit       *m_ImportPage_DeliveryName;
        QLineEdit       *m_ImportPage_PalletQty;
        QLineEdit       *m_ImportPage_BoxQty;
        QLineEdit       *m_ImportPage_PackQty;
        QTableView      *m_ImportPage_Table;

};

#endif // DATABASE_H
