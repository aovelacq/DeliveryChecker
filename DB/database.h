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
#include <QLabel>
#include <QStackedWidget>
#include <QDateTime>

#include "globals/globals.h"
#include "SQLTable/sqlview.h"
#include "importPage/pillspushbutton.h"
#include "importPage/roundpushbutton.h"
#include "dataBaseWindow/ImprovedLineEdit.h"
#include "dataBaseWindow/databasewindow.h"
#include "popUpWindows/ProductNotFound.h"

class BackgroundColorDelegate;

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

        // Import Page
        const QString   getImportPageDeliveryName();
        const QString   getImportPagePalletQty();
        const QString   getImportPageBoxQty();
        const QString   getImportPagePackQty();
        QSqlQueryModel* getImportPageTableData();

        // Identify page
        const QString   getIdentifyPagePalletId();
        const QString   getIdentifyPageBoxQtyOnPallet();
        const QString   getIdentifyPagePalletValue();

        // Scan Page
        QSqlQueryModel* getScanPageTableData();
        bool            scanPageCheckBoxExists(QString ref);
        void            scanPageUpdateBoxScanned(QString ref);
        // Intermediary repport page

        // Final repport page

        // Database view

        QSqlQueryModel* getDBWindowFilter();
        bool checkDBWindowFilter();

    private slots:
        void sendImportPageInformations();
        void sendIdentifyPageInformations();
        void resetIdentifyPage(QString);
        void sendScanPageInformations();
        void scanPageBoxScanned();
        //void sendIntRepportPageInformations();
        //void sendFinRepportPageInformations();
        void sendDBWindowInformations(int);
        void sendDBWindowNewFilter();
        void sendDBWindowCheckFilter(QString);
        void setDBWindowQueryValidLabel(bool valid);
        void resetDBWindowFilter(bool reset);
        void resetProductNotFound();

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
        void sendIdentifyPagePalletId (QString data);
        void sendIdentifyPageBoxQtyOnPallet (QString data);
        void sendIdentifyPagePalletValue (QString data);
        void sendIdentifyPageDone(bool ok);

        //Related to Scan Page
        void sendScanPageTableData(QSqlQueryModel* data);
        void hideScanPageTableColumn(int index);

        //Related to Intermediary Repport Page

        //Related to Final Repport Page

        //Related to DataBaseWindow
        void sendDBWindowTableData(QSqlQueryModel* data);
        void sendDBWindowFilter(QSqlQueryModel* data);
        void isDBWindowQueryValid(bool);


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
        RoundPushButton *m_IdentifyPage_continueButton;
        QLabel          *m_IdentifyPage_continueLabel;
        RoundPushButton *m_IdentifyPage_closePopUp;
        ProductNotFound *m_IdentifyPage_productNotFound;

        // Pointers to ScanPage elements
        SQLView         *m_ScanPage_Table;
        BackgroundColorDelegate *m_scanPageDeleguate;
        QLineEdit       *m_ScanPage_BoxRef;
        int             palletScanned = 3;
        // Pointers to IntRepportPage elements
        // Pointers to FinRepportPage elements

        //Pointers to dataBaseWindow elements
        SQLView         *m_DBWindow_Table;
        QComboBox       *m_DBWindow_selectTable;
        QPushButton     *m_DBWindow_okButton;
        ImprovedLineEdit*m_DBWindow_filter;
        QLabel          *m_DBWindow_queryLabel;



};

#endif // DATABASE_H
