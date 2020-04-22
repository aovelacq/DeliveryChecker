#include "database.h"

DataBase::DataBase(QWidget *parent)
    :QObject(parent)
{
    // Set element name
    setObjectName("DataBase");

    // Pointers to ImportPage elements
    QList<QLineEdit*> ImportPageIOFieldsList = this->parent()->findChildren<QLineEdit*>();
    for(int i = 0; i < ImportPageIOFieldsList.size() ; ++i)
    {
        if (ImportPageIOFieldsList.at(i)->objectName()=="ImportPage_LineEdit_deliveryName")
        {
            m_ImportPage_DeliveryName   = ImportPageIOFieldsList.at(i);
            QObject::connect(this, SIGNAL(sendImportPageDeliveryName(const QString)), m_ImportPage_DeliveryName,  SLOT(setText(const QString)));
        }
        if (ImportPageIOFieldsList.at(i)->objectName()=="ImportPage_LineEdit_palletQty")
        {
            m_ImportPage_PalletQty      = ImportPageIOFieldsList.at(i);
            QObject::connect(this, SIGNAL(sendImportPagePalletQty(const QString)), m_ImportPage_PalletQty, SLOT(setText(const QString)));
        }
        if (ImportPageIOFieldsList.at(i)->objectName()=="ImportPage_LineEdit_boxQty")
        {
            m_ImportPage_BoxQty         = ImportPageIOFieldsList.at(i);
            QObject::connect(this, SIGNAL(sendImportPageBoxQty(const QString)), m_ImportPage_BoxQty, SLOT(setText(const QString)));
        }
        if (ImportPageIOFieldsList.at(i)->objectName()=="ImportPage_LineEdit_packQty")
        {
            m_ImportPage_PackQty        = ImportPageIOFieldsList.at(i);
            QObject::connect(this, SIGNAL(sendImportPagePackQty(const QString)), m_ImportPage_PackQty, SLOT(setText(const QString)));
        }
    }
    QList<SQLView*> ImportPageTableList = this->parent()->findChildren<SQLView*>();
    for(int i = 0; i < ImportPageTableList.size() ; ++i)
    {
        if (ImportPageTableList.at(i)->objectName()=="ImportPage_SQLView_Table")
        {
            m_ImportPage_Table   = ImportPageTableList.at(i);
            QObject::connect(this, SIGNAL(sendImportPageTableData(QSqlQueryModel*)), m_ImportPage_Table, SLOT(setResults(QSqlQueryModel*)));
        }
    }
    QList<PillsPushButton*> ImportPagePillsPushButtonList = this->parent()->findChildren<PillsPushButton*>();
    for(int i = 0; i < ImportPagePillsPushButtonList.size() ; ++i)
    {
        if (ImportPagePillsPushButtonList.at(i)->objectName()=="pillsButton_Check")
        {
            m_ImportPage_CheckBox = ImportPagePillsPushButtonList.at(i);
            QObject::connect(this, SIGNAL(sendImportPageDone(bool)), m_ImportPage_CheckBox, SLOT(setVisible(bool)));
        }
    }

    // Pointers to IdentifyPage elements
    // Pointers to ScanPage elements
//    QList<SQLView*> ScanPageTableList = this->parent()->findChildren<SQLView*>();
//    for(int i = 0; i < ScanPageTableList.size() ; ++i)
//    {
//        if (ScanPageTableList.at(i)->objectName()=="ScanPage_SQLView_Table")
//        {
//            m_ScanPage_Table   = ScanPageTableList.at(i);
//            QObject::connect(this, SIGNAL(sendImportPageTableData(QSqlQueryModel*)), m_ScanPage_Table, SLOT(setResults(QSqlQueryModel*)));
//        }
//    }
    // Pointers to IntRepportPage elements
    // Pointers to FinRepportPage elements


    QObject::connect(this, SIGNAL(tableFillingDone()), this, SLOT(sendInformations()));
}

bool DataBase::createConnection()
{
    const QString DRIVER("QSQLITE");
    if(!QSqlDatabase::isDriverAvailable(DRIVER))
    {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                    QObject::tr("Driver not available\n"
                                "CODE : 12345\n\n"
                                "Click OK to exit."), QMessageBox::Ok);
        QApplication::quit();
        return false;
    }

    m_DB = QSqlDatabase::addDatabase(DRIVER);
    m_DB.setDatabaseName(":memory:");

    if (!m_DB.open())
    {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                    QObject::tr("Unable to establish a database connection.\n"
                                "CODE : 12345\n\n"
                                "Click OK to exit."), QMessageBox::Ok);
        QApplication::quit();
        return false;
    }
    QSqlQuery query;
    // Create ITEMS TABLE
    if(!query.exec("CREATE TABLE IF NOT EXISTS ITEMS ("
                   "IT_ID               INT             NOT NULL, "
                   "IT_NAME             VARCHAR(40)     NOT NULL, "
                   "IT_WEIGHT           REAL            NOT NULL, "
                   "IT_VALUE            REAL            NOT NULL, "
                   "IT_ROLL_Q           INT             NOT NULL, "
                   "IT_PACK_Q           INT             NOT NULL, "
                   "IT_BOX_Q            INT             NOT NULL, "
                   "IT_PALLET_Q         INT             NOT NULL, "
                   "IT_BA_WEIGHT        REAL            NOT NULL, "
                   "IT_BA_TO            REAL            NOT NULL, "
                   "IT_BO_WEIGHT        REAL            NOT NULL, "
                   "IT_BO_TO            REAL            NOT NULL, "
                   "IT_COLOR            INT             NOT NULL, "
                   "IT_BA_CFG           INT             NOT NULL, "
                   "IT_BO_CFG           INT             NOT NULL, "
                   "IT_PA_CFG           INT             NOT NULL, "
                   "IT_LA_CFG           INT             NOT NULL, "
                   "IT_YEAR             INT             NOT NULL, "
//               "IT_DATE             DATETIME, "
               "PRIMARY KEY(IT_ID)"
               ")"))
    {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                    QObject::tr("Unable to create ITEMS table\n"
                                "CODE : 12345\n\n"
                                "Database details : %1\n"
                                "Driver details : %2\n\n"
                                "Click OK to exit.").arg(query.lastError().databaseText(), query.lastError().driverText()), QMessageBox::Ok);
        QApplication::quit();
        return false;
    }

    // Create JOBORDER TABLE
    if(!query.exec("CREATE TABLE IF NOT EXISTS JOBORDER ("
                   "JO_ID               INT             NOT NULL, "
                   "JO_NAME             VARCHAR(40)     NOT NULL, "
                   "JO_IT_ID            INT             NOT NULL, "
                   "JO_DESC             VARCHAR(80),              "
                   "JO_WEIGHT           REAL            NOT NULL, "
                   "JO_STATUS           SMALLINT,                 "
                   "JO_STATUS_S         VARCHAR(40),              "
                   "JO_DATE_EDITION     DATETIME,                 "
                   "JO_DATE_START       DATETIME,                 "
                   "JO_DATE_STOP        DATETIME,                 "
                   "SH_ID               INT,                      "
                   "OP_ID               INT,                      "
                   "PRIMARY KEY(JO_ID),"
                   "FOREIGN KEY(JO_IT_ID) REFERENCES ITEMS(IT_ID)"
                   ")"))
    {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                    QObject::tr("Unable to create JOBORDER table\n"
                                "CODE : 12345\n\n"
                                "Database details : %1\n"
                                "Driver details : %2\n\n"
                                "Click OK to exit.").arg(query.lastError().databaseText(), query.lastError().driverText()), QMessageBox::Ok);
        QApplication::quit();
                return false;
    }

    // Create TRACEABILITY_PALLET TABLE
    if(!query.exec("CREATE TABLE IF NOT EXISTS TRACEABILITY_PALLET ("
                   "PA_ID               INT             NOT NULL, "
                   "JO_ID               INT             NOT NULL, "
                   "TR_PA_EXIT          SMALLINT,                 "
                   "TR_PA_STATUS        SMALLINT,                 "
                   "TR_PA_STATUS_S      VARCHAR(40),              "
                   "TR_PA_DATE_IN       DATETIME,                 "
                   "TR_PA_DATE_OUT      DATETIME,                 "
                   "SH_ID               INT,                      "
                   "OP_ID               INT,                      "
                   "SCANNED             BOOLEAN,                  "
                   "PRIMARY KEY(PA_ID),"
                   "FOREIGN KEY(JO_ID) REFERENCES JOBORDER(JO_ID)"
                   ")"))
    {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                    QObject::tr("Unable to create TRACEABILITY_PALLET table\n"
                                "CODE : 12345\n\n"
                                "Database details : %1\n"
                                "Driver details : %2\n\n"
                                "Click OK to exit.").arg(query.lastError().databaseText(), query.lastError().driverText()), QMessageBox::Ok);
        QApplication::quit();
                return false;
    }

    // Create TRACEABILITY_BOX TABLE
    if(!query.exec("CREATE TABLE IF NOT EXISTS TRACEABILITY_BOX ("
                   "BO_ID               INT             NOT NULL, "
                   "TR_BO_ID            VARCHAR(80)     NOT NULL, "
                   "JO_ID               INT             NOT NULL, "
                   "PA_ID               INT             NOT NULL, "
                   "TR_BO_WEIGHT        REAL            NOT NULL, "
                   "TR_BO_STATUS        SMALLINT,                 "
                   "TR_BO_STATUS_S      VARCHAR(40),              "
                   "TR_BO_DATE          DATETIME,                 "
                   "SH_ID               INT,                      "
                   "OP_ID               INT,                      "
                   "SCANNED             BOOLEAN,                  "
                   "PRIMARY KEY(BO_ID),"
                   "FOREIGN KEY(JO_ID) REFERENCES JOBORDER(JO_ID),"
                   "FOREIGN KEY(PA_ID) REFERENCES TRACEABILITY_PALLET(PA_ID)"
                   ")"))
    {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                    QObject::tr("Unable to create TRACEABILITY_BOX table\n"
                                "CODE : 12345\n\n"
                                "Database details : %1\n"
                                "Driver details : %2\n\n"
                                "Click OK to exit.").arg(query.lastError().databaseText(), query.lastError().driverText()), QMessageBox::Ok);
        QApplication::quit();
                return false;
    }

    // Create TRACEABILITY_BATCH TABLE
    if(!query.exec("CREATE TABLE IF NOT EXISTS TRACEABILITY_BATCH ("
                   "TR_BA_ID            VARCHAR(80)     NOT NULL, "
                   "JO_ID               INT             NOT NULL, "
                   "BO_ID               INT             NOT NULL, "
                   "TR_BA_WEIGHT        REAL            NOT NULL, "
                   "TR_BA_STATUS        SMALLINT,                 "
                   "TR_BA_STATUS_S      VARCHAR(40),              "
                   "TR_BA_DATE          DATETIME,                 "
                   "SH_ID               INT,                      "
                   "OP_ID               INT,                      "
                   "SCANNED             BOOLEAN,                  "
                   "PRIMARY KEY(TR_BA_ID),"
                   "FOREIGN KEY(JO_ID) REFERENCES JOBORDER(JO_ID),"
                   "FOREIGN KEY(BO_ID) REFERENCES TRACEABILITY_BOX(BO_ID)"
                   ")"))
    {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                    QObject::tr("Unable to create TRACEABILITY_BATCH table\n"
                                "CODE : 12345\n\n"
                                "Database details : %1\n"
                                "Driver details : %2\n\n"
                                "Click OK to exit.").arg(query.lastError().databaseText(), query.lastError().driverText()), QMessageBox::Ok);
        QApplication::quit();
                return false;
    }

    // Create DELIVERY TABLE
    if(!query.exec("CREATE TABLE IF NOT EXISTS DELIVERY ("
                   "DE_ID               INT             NOT NULL, "
                   "DE_NAME             INT             NOT NULL, "
                   "DE_CUSTOMER         SMALLINT        NOT NULL, "
                   "DE_STATUS           SMALLINT,                 "
                   "DE_STATUS_S         VARCHAR(40),              "
                   "DE_DATE             DATETIME,                 "
                   "PRIMARY KEY(DE_ID)"
                   ")"))
    {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                    QObject::tr("Unable to create DELIVERY table\n"
                                "CODE : 12345\n\n"
                                "Database details : %1\n"
                                "Driver details : %2\n\n"
                                "Click OK to exit.").arg(query.lastError().databaseText(), query.lastError().driverText()), QMessageBox::Ok);
        QApplication::quit();
                return false;
    }

    // Create DELIVERY_LIST TABLE
    if(!query.exec("CREATE TABLE IF NOT EXISTS DELIVERY_LIST ("
                   "DL_ID               INT             NOT NULL, "
                   "DL_DE_ID            INT             NOT NULL, "
                   "DL_PA_ID            SMALLINT        NOT NULL, "
                   "DL_DATE             DATETIME,                 "
                   "PRIMARY KEY(DL_ID),"
                   "FOREIGN KEY(DL_DE_ID) REFERENCES DELIVERY(DE_ID),"
                   "FOREIGN KEY(DL_PA_ID) REFERENCES TRACEABILITY_PALLET(PA_ID)"
                   ")"))
    {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                    QObject::tr("Unable to create DELIVERY_LIST table\n"
                                "CODE : 12345\n\n"
                                "Database details : %1\n"
                                "Driver details : %2\n\n"
                                "Click OK to exit.").arg(query.lastError().databaseText(), query.lastError().driverText()), QMessageBox::Ok);
        QApplication::quit();
                return false;
    }

        return true;
}

bool DataBase::fillTables()
{
    if(!deleteAllData())                return false;
    if(!fillItemsTable())               return false;
    if(!fillJoborderTable())            return false;
    if(!fillTraceabilityPalletTable())  return false;
    if(!fillTraceabilityBoxTable())     return false;
    if(!fillTraceabilityBatchTable())   return false;
    if(!fillDeliveryTable())            return false;
    if(!fillDeliveryListTable())        return false;

    emit tableFillingDone();

    return true;

}

bool DataBase::deleteAllData()
{
    QSqlQuery query;
    QString qry;

    qry = "DELETE FROM ITEMS;";
    if (!query.exec(qry))
    {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                    QObject::tr("Error during clearing ITEMS table %1.\n"
                                "CODE : 12345\n\n"
                                "Click OK to exit.").arg(query.lastError().text()), QMessageBox::Ok);
        QApplication::quit();
        return false;
    }

    qry = "DELETE FROM JOBORDER;";
    if (!query.exec(qry))
    {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                    QObject::tr("Error during clearing JOBORDER table %1.\n"
                                "CODE : 12345\n\n"
                                "Click OK to exit.").arg(query.lastError().text()), QMessageBox::Ok);
        QApplication::quit();
        return false;
    }

    qry = "DELETE FROM TRACEABILITY_PALLET;";
    if (!query.exec(qry))
    {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                    QObject::tr("Error during clearing TRACEABILITY_PALLET table %1.\n"
                                "CODE : 12345\n\n"
                                "Click OK to exit.").arg(query.lastError().text()), QMessageBox::Ok);
        QApplication::quit();
        return false;
    }

    qry = "DELETE FROM TRACEABILITY_BOX;";
    if (!query.exec(qry))
    {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                    QObject::tr("Error during clearing TRACEABILITY_BOX table %1.\n"
                                "CODE : 12345\n\n"
                                "Click OK to exit.").arg(query.lastError().text()), QMessageBox::Ok);
        QApplication::quit();
        return false;
    }

    qry = "DELETE FROM TRACEABILITY_BATCH;";
    if (!query.exec(qry))
    {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                    QObject::tr("Error during clearing TRACEABILITY_BATCH table %1.\n"
                                "CODE : 12345\n\n"
                                "Click OK to exit.").arg(query.lastError().text()), QMessageBox::Ok);
        QApplication::quit();
        return false;
    }

    qry = "DELETE FROM DELIVERY;";
    if (!query.exec(qry))
    {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                    QObject::tr("Error during clearing DELIVERY table %1.\n"
                                "CODE : 12345\n\n"
                                "Click OK to exit.").arg(query.lastError().text()), QMessageBox::Ok);
        QApplication::quit();
        return false;
    }

    qry = "DELETE FROM DELIVERY_LIST;";
    if (!query.exec(qry))
    {
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                    QObject::tr("Error during clearing DELIVERY_LIST table %1.\n"
                                "CODE : 12345\n\n"
                                "Click OK to exit.").arg(query.lastError().text()), QMessageBox::Ok);
        QApplication::quit();
        return false;
    }

    return true;
}

bool DataBase::fillItemsTable()
{
    bool found;
    QDir Folder(CSV_FOLDER_PATH);
    QFileInfoList FileList = Folder.entryInfoList(QDir::Files);
    QRegExp ExpFileSearch;
    QString FileSearch = CSV_ITEMS_NAME;
    // Allowed file name pattern : NAME.csv OR NAME_JJMMAAAA_hhmmss.csv OR NAME_JJMMAA_hhmmss.csv

    // Check if file ITEMS exists
    found = false;
    ExpFileSearch.setPattern("("+FileSearch+"){1}((_)*(\\d){6,8}(_)*(\\d){6})?(.csv)$");
    for (int i = 0; i < FileList.size(); ++i)
    {
        if (ExpFileSearch.exactMatch(FileList.at(i).fileName()))
        {
            found = true;
            QFile file(FileList.at(i).absoluteFilePath());
            if(!file.open (QIODevice::ReadOnly))
            {
                QMessageBox::critical(nullptr, QObject::tr("Main error"),
                            QObject::tr("Unable to open file %1.\n"
                                        "CODE : 12345\n\n"
                                        "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
                QApplication::quit();
                return false;
            }

            QSqlQuery query;
            QTextStream ts(&file);
            ts.readLine();
            while (!ts.atEnd())
            {
                QString qry = "INSERT OR ABORT INTO ITEMS VALUES(";
                QString element;
                // Split lines with serapartor
                QStringList line = ts.readLine().split(CSV_DELIMITER);
                int length = CSV_ITEMS_HAS_SYS_FIELDS?line.length()-4:line.length()-2;
                for(int i=1; i<length;i++)
                {
                    element = (QString)(line.at(i));
                    if (element.contains(',')) element.replace(',','.');
                    if (i==2 && element.length()<3) goto next;
                    qry.append(element);
                    qry.append(",");
                }
                qry.chop(1);
                qry.append(");");
                if (CONSOLE_DEBUG) qDebug() << qry;
                if (!query.exec(qry))
                {
                    QMessageBox::critical(nullptr, QObject::tr("Database error"),
                                QObject::tr("Error during ITEMS table populating %1.\n"
                                            "CODE : 12345\n\n"
                                            "Click OK to exit.").arg(query.lastError().text()), QMessageBox::Ok);
                    //QApplication::quit();
                    return false;
                }
                next:;
             }
        }
    }
    if (!found)
    {
        QMessageBox::critical(nullptr, QObject::tr("Main error"),
                              QObject::tr("File %1 not found\n"
                                          "CODE : 12345\n\n"
                                          "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
        //QApplication::quit();
        return false;
    }

    return true;
}

bool DataBase::fillJoborderTable()
{
    bool found;
    QDir Folder(CSV_FOLDER_PATH);
    QFileInfoList FileList = Folder.entryInfoList(QDir::Files);
    QRegExp ExpFileSearch;
    QString FileSearch = CSV_JOBORDER_NAME;
    // Allowed file name pattern : NAME.csv OR NAME_JJMMAAAA_hhmmss.csv OR NAME_JJMMAA_hhmmss.csv

    // Check if file JOBORDER exists
    found = false;
    ExpFileSearch.setPattern("("+FileSearch+"){1}((_)*(\\d){6,8}(_)*(\\d){6})?(.csv)$");
    //QApplication::quit();
    for (int i = 0; i < FileList.size(); ++i)
    {
        if (ExpFileSearch.exactMatch(FileList.at(i).fileName()))
        {
            found = true;
            QFile file(FileList.at(i).absoluteFilePath());
            if(!file.open (QIODevice::ReadOnly))
            {
                QMessageBox::critical(nullptr, QObject::tr("Main error"),
                            QObject::tr("Unable to open file %1.\n"
                                        "CODE : 12345\n\n"
                                        "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
                //QApplication::quit();
                return false;
            }

            QSqlQuery query;
            QTextStream ts(&file);
            ts.readLine();
            while (!ts.atEnd())
            {
                QString qry = "INSERT OR ABORT INTO JOBORDER VALUES(";
                QString element;
                // Split lines with serapartor
                QStringList line = ts.readLine().split(CSV_DELIMITER);
                int length = CSV_JOBORDER_HAS_SYS_FIELDS?line.length()-3:line.length()-1;
                for(int i=1; i<length;i++)
                {
                    element = (QString)(line.at(i));
                    if (i == 8 || i == 9)
                    {
                        element = convertDate(element);
                    }
                    if (element.contains(',')) element.replace(',','.');
                    if (element.isEmpty()) element = "\"\"" ;
                    qry.append(element);
                    qry.append(",");
                }
                qry.chop(1);
                qry.append(");");
                if (CONSOLE_DEBUG) qDebug() << qry;
                if (!query.exec(qry))
                {
                    QMessageBox::critical(nullptr, QObject::tr("Database error"),
                                QObject::tr("Error during JOBORDER table populating %1.\n"
                                            "CODE : 12345\n\n"
                                            "Click OK to exit.").arg(query.lastError().text()), QMessageBox::Ok);
                    //QApplication::quit();
                    return false;
                }
                next:;
             }
        }
    }
    if (!found)
    {
        QMessageBox::critical(nullptr, QObject::tr("Main error"),
                              QObject::tr("File %1 not found\n"
                                          "CODE : 12345\n\n"
                                          "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
        //QApplication::quit();
        return false;
    }

    return true;
}

bool DataBase::fillTraceabilityPalletTable()
{
    bool found;
    QDir Folder(CSV_FOLDER_PATH);
    QFileInfoList FileList = Folder.entryInfoList(QDir::Files);
    QRegExp ExpFileSearch;
    QString FileSearch = CSV_TRACEABILITY_PALLET_NAME;
    // Allowed file name pattern : NAME.csv OR NAME_JJMMAAAA_hhmmss.csv OR NAME_JJMMAA_hhmmss.csv

    // Check if file TRACEABILITY_PALLET exists
    found = false;
    ExpFileSearch.setPattern("("+FileSearch+"){1}((_)*(\\d){6,8}(_)*(\\d){6})?(.csv)$");
    for (int i = 0; i < FileList.size(); ++i)
    {
        if (ExpFileSearch.exactMatch(FileList.at(i).fileName()))
        {
            found = true;
            QFile file(FileList.at(i).absoluteFilePath());
            if(!file.open (QIODevice::ReadOnly))
            {
                QMessageBox::critical(nullptr, QObject::tr("Main error"),
                            QObject::tr("Unable to open file %1.\n"
                                        "CODE : 12345\n\n"
                                        "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
                //QApplication::quit();
                return false;
            }

            QSqlQuery query;
            QTextStream ts(&file);
            ts.readLine();
            while (!ts.atEnd())
            {
                QString qry = "INSERT OR ABORT INTO TRACEABILITY_PALLET VALUES(";
                QString element;
                // Split lines with serapartor
                QStringList line = ts.readLine().split(CSV_DELIMITER);
                int length = CSV_TRACEABILITY_PALLET_HAS_SYS_FIELDS?line.length()-3:line.length()-1;
                for(int i=1; i<length;i++)
                {
                    element = (QString)(line.at(i));
                    if (i == 6 || i == 7)
                    {
                        element = convertDate(element);
                    }
                    if (element.contains(',')) element.replace(',','.');
                    if (element.isEmpty()) element = "\"\"" ;
                    qry.append(element);
                    qry.append(",");
                }
                qry.append("FALSE");
                qry.append(");");
                if (CONSOLE_DEBUG) qDebug() << qry;
                if (!query.exec(qry))
                {
                    QMessageBox::critical(nullptr, QObject::tr("Database error"),
                                QObject::tr("Error during TRACEABILITY_PALLET table populating %1.\n"
                                            "CODE : 12345\n\n"
                                            "Click OK to exit.").arg(query.lastError().text()), QMessageBox::Ok);
                    //QApplication::quit();
                    return false;
                }
                next:;
             }
        }
    }
    if (!found)
    {
        QMessageBox::critical(nullptr, QObject::tr("Main error"),
                              QObject::tr("File %1 not found\n"
                                          "CODE : 12345\n\n"
                                          "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
        //QApplication::quit();
        return false;
    }

    return true;
}

bool DataBase::fillTraceabilityBoxTable()
{
    bool found;
    QDir Folder(CSV_FOLDER_PATH);
    QFileInfoList FileList = Folder.entryInfoList(QDir::Files);
    QRegExp ExpFileSearch;
    QString FileSearch = CSV_TRACEABILITY_BOX_NAME;
    // Allowed file name pattern : NAME.csv OR NAME_JJMMAAAA_hhmmss.csv OR NAME_JJMMAA_hhmmss.csv

    // Check if file TRACEABILITY_BOX exists
    found = false;
    ExpFileSearch.setPattern("("+FileSearch+"){1}((_)*(\\d){6,8}(_)*(\\d){6})?(.csv)$");
    for (int i = 0; i < FileList.size(); ++i)
    {
        if (ExpFileSearch.exactMatch(FileList.at(i).fileName()))
        {
            found = true;
            QFile file(FileList.at(i).absoluteFilePath());
            if(!file.open (QIODevice::ReadOnly))
            {
                QMessageBox::critical(nullptr, QObject::tr("Main error"),
                            QObject::tr("Unable to open file %1.\n"
                                        "CODE : 12345\n\n"
                                        "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
                //QApplication::quit();
                return false;
            }

            QSqlQuery query;
            QTextStream ts(&file);
            ts.readLine();
            while (!ts.atEnd())
            {
                QString qry = "INSERT OR ABORT INTO TRACEABILITY_BOX VALUES(";
                QString element;
                // Split lines with serapartor
                QStringList line = ts.readLine().split(CSV_DELIMITER);
                int length = CSV_TRACEABILITY_BOX_HAS_SYS_FIELDS?line.length()-3:line.length()-1;
                for(int i=1; i<length;i++)
                {
                    element = (QString)(line.at(i));
                    if (i == 8)
                    {
                        element = convertDate(element);
                    }
                    if (element.contains(',')) element.replace(',','.');
                    if (element.isEmpty()) element = "\"\"" ;
                    qry.append(element);
                    qry.append(",");
                }
                qry.append("FALSE");
                qry.append(");");
                if (CONSOLE_DEBUG) qDebug() << qry;
                if (!query.exec(qry))
                {
                    QMessageBox::critical(nullptr, QObject::tr("Database error"),
                                QObject::tr("Error during TRACEABILITY_BOX table populating %1.\n"
                                            "CODE : 12345\n\n"
                                            "Click OK to exit.").arg(query.lastError().text()), QMessageBox::Ok);
                    //QApplication::quit();
                    return false;
                }
                next:;
             }
        }
    }
    if (!found)
    {
        QMessageBox::critical(nullptr, QObject::tr("Main error"),
                              QObject::tr("File %1 not found\n"
                                          "CODE : 12345\n\n"
                                          "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
        //QApplication::quit();
        return false;
    }

    return true;
}

bool DataBase::fillTraceabilityBatchTable()
{
    bool found;
    QDir Folder(CSV_FOLDER_PATH);
    QFileInfoList FileList = Folder.entryInfoList(QDir::Files);
    QRegExp ExpFileSearch;
    QString FileSearch = CSV_TRACEABILITY_BATCH_NAME;
    // Allowed file name pattern : NAME.csv OR NAME_JJMMAAAA_hhmmss.csv OR NAME_JJMMAA_hhmmss.csv

    // Check if file TRACEABILITY_BATCH exists
    found = false;
    ExpFileSearch.setPattern("("+FileSearch+"){1}((_)*(\\d){6,8}(_)*(\\d){6})?(.csv)$");
    for (int i = 0; i < FileList.size(); ++i)
    {
        if (ExpFileSearch.exactMatch(FileList.at(i).fileName()))
        {
            found = true;
            QFile file(FileList.at(i).absoluteFilePath());
            if(!file.open (QIODevice::ReadOnly))
            {
                QMessageBox::critical(nullptr, QObject::tr("Main error"),
                            QObject::tr("Unable to open file %1.\n"
                                        "CODE : 12345\n\n"
                                        "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
                //QApplication::quit();
                return false;
            }

            QSqlQuery query;
            QTextStream ts(&file);
            ts.readLine();
            while (!ts.atEnd())
            {
                QString qry = "INSERT OR ABORT INTO TRACEABILITY_BATCH VALUES(";
                QString element;
                // Split lines with serapartor
                QStringList line = ts.readLine().split(CSV_DELIMITER);
                int length = CSV_TRACEABILITY_BATCH_HAS_SYS_FIELDS?line.length()-3:line.length()-1;
                for(int i=1; i<length;i++)
                {
                    element = (QString)(line.at(i));
                    if (i == 7)
                    {
                        element = convertDate(element);
                    }
                    if (element.contains(',')) element.replace(',','.');
                    if (element.isEmpty()) element = "\"\"" ;
                    qry.append(element);
                    qry.append(",");
                }
                qry.append("FALSE");
                qry.append(");");
                if (CONSOLE_DEBUG) qDebug() << qry;
                if (!query.exec(qry))
                {
                    QMessageBox::critical(nullptr, QObject::tr("Database error"),
                                QObject::tr("Error during TRACEABILITY_BATCH table populating %1.\n"
                                            "CODE : 12345\n\n"
                                            "Click OK to exit.").arg(query.lastError().text()), QMessageBox::Ok);
                    //QApplication::quit();
                    return false;
                }
                next:;
             }
        }
    }
    if (!found)
    {
        QMessageBox::critical(nullptr, QObject::tr("Main error"),
                              QObject::tr("File %1 not found\n"
                                          "CODE : 12345\n\n"
                                          "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
        //QApplication::quit();
        return false;
    }

    return true;
}

bool DataBase::fillDeliveryTable()
{
    bool found;
    QDir Folder(CSV_FOLDER_PATH);
    QFileInfoList FileList = Folder.entryInfoList(QDir::Files);
    QRegExp ExpFileSearch;
    QString FileSearch = CSV_DELIVERY_NAME;
    // Allowed file name pattern : NAME.csv OR NAME_JJMMAAAA_hhmmss.csv OR NAME_JJMMAA_hhmmss.csv

    // Check if file DELIVERY exists
    found = false;
    ExpFileSearch.setPattern("("+FileSearch+"){1}((_)*(\\d){6,8}(_)*(\\d){6})?(.csv)$");
    for (int i = 0; i < FileList.size(); ++i)
    {
        if (ExpFileSearch.exactMatch(FileList.at(i).fileName()))
        {
            found = true;
            QFile file(FileList.at(i).absoluteFilePath());
            if(!file.open (QIODevice::ReadOnly))
            {
                QMessageBox::critical(nullptr, QObject::tr("Main error"),
                            QObject::tr("Unable to open file %1.\n"
                                        "CODE : 12345\n\n"
                                        "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
                return false;
            }

            QSqlQuery query;
            QTextStream ts(&file);
            ts.readLine();
            while (!ts.atEnd())
            {
                QString qry = "INSERT OR ABORT INTO DELIVERY VALUES(";
                QString element;
                // Split lines with serapartor
                QStringList line = ts.readLine().split(CSV_DELIMITER);
                int length = CSV_DELIVERY_HAS_SYS_FIELDS?line.length()-3:line.length()-1;
                for(int i=1; i<length;i++)
                {
                    element = (QString)(line.at(i));
                    if (i == 6)
                    {
                        element = convertDate(element);
                    }
                    if (element.contains(',')) element.replace(',','.');
                    if (element.isEmpty()) element = "\"\"" ;
                    qry.append(element);
                    qry.append(",");
                }
                qry.chop(1);
                qry.append(");");
                if (CONSOLE_DEBUG) qDebug() << qry;
                if (!query.exec(qry))
                {
                    QMessageBox::critical(nullptr, QObject::tr("Database error"),
                                QObject::tr("Error during DELIVERY table populating %1.\n"
                                            "CODE : 12345\n\n"
                                            "Click OK to exit.").arg(query.lastError().text()), QMessageBox::Ok);
                    //QApplication::quit();
                    return false;
                }
                next:;
             }
        }
    }
    if (!found)
    {
        QMessageBox::critical(nullptr, QObject::tr("Main error"),
                              QObject::tr("File %1 not found\n"
                                          "CODE : 12345\n\n"
                                          "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
        //QApplication::quit();
        return false;
    }

    return true;
}

bool DataBase::fillDeliveryListTable()
{
    bool found;
    QDir Folder(CSV_FOLDER_PATH);
    QFileInfoList FileList = Folder.entryInfoList(QDir::Files);
    QRegExp ExpFileSearch;
    QString FileSearch = CSV_DELIVERY_LIST_NAME;
    // Allowed file name pattern : NAME.csv OR NAME_JJMMAAAA_hhmmss.csv OR NAME_JJMMAA_hhmmss.csv

    // Check if file DELIVERY_LIST exists
    found = false;
    ExpFileSearch.setPattern("("+FileSearch+"){1}((_)*(\\d){6,8}(_)*(\\d){6})?(.csv)$");
    for (int i = 0; i < FileList.size(); ++i)
    {
        if (ExpFileSearch.exactMatch(FileList.at(i).fileName()))
        {
            found = true;
            QFile file(FileList.at(i).absoluteFilePath());
            if(!file.open (QIODevice::ReadOnly))
            {
                QMessageBox::critical(nullptr, QObject::tr("Main error"),
                            QObject::tr("Unable to open file %1.\n"
                                        "CODE : 12345\n\n"
                                        "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
                //QApplication::quit();
                return false;
            }

            QSqlQuery query;
            QTextStream ts(&file);
            ts.readLine();
            while (!ts.atEnd())
            {
                QString qry = "INSERT OR ABORT INTO DELIVERY_LIST VALUES(";
                QString element;
                // Split lines with serapartor
                QStringList line = ts.readLine().split(CSV_DELIMITER);
                int length = CSV_DELIVERY_LIST_HAS_SYS_FIELDS?line.length()-3:line.length()-1;
                for(int i=1; i<length;i++)
                {
                    element = (QString)(line.at(i));
                    if (i == 4)
                    {
                        element = convertDate(element);
                    }
                    if (element.contains(',')) element.replace(',','.');
                    if (element.isEmpty()) element = "\"\"" ;
                    qry.append(element);
                    qry.append(",");
                }
                qry.chop(1);
                qry.append(");");
                if (CONSOLE_DEBUG) qDebug() << qry;
                if (!query.exec(qry))
                {
                    QMessageBox::critical(nullptr, QObject::tr("Database error"),
                                QObject::tr("Error during DELIVERY_LIST table populating %1.\n"
                                            "CODE : 12345\n\n"
                                            "Click OK to exit.").arg(query.lastError().text()), QMessageBox::Ok);
                    //QApplication::quit();
                    return false;
                }
                next:;
             }
        }
    }
    if (!found)
    {
        QMessageBox::critical(nullptr, QObject::tr("Main error"),
                              QObject::tr("File %1 not found\n"
                                          "CODE : 12345\n\n"
                                          "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
        return false;
    }

    return true;
}

QString DataBase::convertDate(QString date)
{
    QString Result = "";
    QRegExp rx("^(\\d){1,2}(/|-){1}(\\d){1,2}(/|-){1}(\\d){4}");
    if (rx.indexIn(date) == -1) return "";

    QStringList list = rx.capturedTexts().first().split('/', QString::SkipEmptyParts);
    if (list.size() != 3) return "";
    Result = list.at(2) + "-" + list.at(0) + "-" + list.at(1);
    return Result;
}

void DataBase::sendInformations()
{
    emit sendImportPageDeliveryName(getDeliveryName());
    emit sendImportPagePalletQty(getPalletQty());
    emit sendImportPageBoxQty(getBoxQty());
    emit sendImportPagePackQty(getPackQty());
    emit sendImportPageTableData(getTableData());
    emit sendImportPageDone(true);
}

const QString DataBase::getDeliveryName()
{
    QSqlQuery query;
    QString qry = "SELECT DE_NAME "
                  "FROM DELIVERY;";
    if(!query.exec(qry)) return "Error";
    query.first();
    return query.value(0).toString().length()<1?"Error":query.value(0).toString();
}

const QString DataBase::getPalletQty()
{
    QSqlQuery query;
    QString qry = "SELECT COUNT(DL_PA_ID) "
                  "FROM DELIVERY_LIST;";
    if(!query.exec(qry)) return "Error";
    query.first();
    return query.value(0).toString().length()<1?"Error":query.value(0).toString();
}

const QString DataBase::getBoxQty()
{
    QSqlQuery query;
    QString qry = "SELECT COUNT(BO_ID) "
                  "FROM "
                    "TRACEABILITY_PALLET LEFT JOIN TRACEABILITY_BOX "
                        "ON TRACEABILITY_PALLET.PA_ID = TRACEABILITY_BOX.PA_ID;";
    if(!query.exec(qry))
    {
        qDebug() << query.lastError().text();
        return "Error";
    }
    query.first();
    return query.value(0).toString().length()<1?"Error":query.value(0).toString();
}

const QString DataBase::getPackQty()
{
    QSqlQuery query;
    QString qry = "SELECT COUNT(TR_BA_ID) "
                  "FROM "
                    "((TRACEABILITY_PALLET INNER JOIN DELIVERY_LIST "
                        "ON TRACEABILITY_PALLET.PA_ID = DELIVERY_LIST.DL_PA_ID) "
                            "INNER JOIN TRACEABILITY_BOX "
                                "ON TRACEABILITY_PALLET.PA_ID = TRACEABILITY_BOX.PA_ID) "
                                    "INNER JOIN TRACEABILITY_BATCH "
                                        "ON TRACEABILITY_BOX.BO_ID = TRACEABILITY_BATCH.BO_ID;";
    if(!query.exec(qry))
    {
        qDebug() << query.lastError().text();
        return "Error";
    }
    query.first();
    return query.value(0).toString().length()<1?"Error":query.value(0).toString();
}

QSqlQueryModel* DataBase::getTableData()
{
    QSqlQuery *query = new QSqlQuery;
    QSqlQueryModel *Results = new QSqlQueryModel();
    QString qry ="SELECT TRACEABILITY_PALLET.PA_ID AS [Pallet ID], ROUND(IT_VALUE) || \" Rp\" AS Denomination, COUNT(TRACEABILITY_BOX.BO_ID) AS [Box quantity] "
                 "FROM "
                    "ITEMS INNER JOIN "
                        "(JOBORDER INNER JOIN "
                            "((TRACEABILITY_PALLET INNER JOIN DELIVERY_LIST "
                            "ON TRACEABILITY_PALLET.PA_ID = DELIVERY_LIST.DL_PA_ID) "
                                "INNER JOIN TRACEABILITY_BOX "
                                "ON TRACEABILITY_PALLET.PA_ID = TRACEABILITY_BOX.PA_ID) "
                        "ON (JOBORDER.JO_ID = TRACEABILITY_BOX.JO_ID) AND (JOBORDER.JO_ID = TRACEABILITY_PALLET.JO_ID)) "
                    "ON ITEMS.IT_ID = JOBORDER.JO_IT_ID "
                 "GROUP BY TRACEABILITY_PALLET.PA_ID, ITEMS.IT_VALUE;";
    if(!query->exec(qry))
    {
        qDebug() << query->lastError().text();
    }
    Results->setQuery(*query);
    return Results;
}
