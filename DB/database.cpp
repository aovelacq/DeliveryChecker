#include "database.h"

int DataBase::palletScanned=-1;

class OKColorDelegate : public QStyledItemDelegate {

public:
    OKColorDelegate(QObject *parent = 0)
        : QStyledItemDelegate(parent)
    {
    }

    void initStyleOption(QStyleOptionViewItem *option,
                         const QModelIndex &index) const
    {
        QStyledItemDelegate::initStyleOption(option, index);

        if (index.data().toString()=="OK")

        option->backgroundBrush = QBrush(QColor(0,175,80));
    }
};

class NOKColorDelegate : public QStyledItemDelegate {

public:
    NOKColorDelegate(QObject *parent = 0)
        : QStyledItemDelegate(parent)
    {
    }

    void initStyleOption(QStyleOptionViewItem *option,
                         const QModelIndex &index) const
    {
        QStyledItemDelegate::initStyleOption(option, index);

        if (index.data().toString()=="")

        option->backgroundBrush = QBrush(QColor(255,0,0));
    }
};

class OKNOKColorDelegate : public QStyledItemDelegate {

public:
    OKNOKColorDelegate(QObject *parent = 0)
        : QStyledItemDelegate(parent)
    {
    }

    void initStyleOption(QStyleOptionViewItem *option,
                         const QModelIndex &index) const
    {
        QStyledItemDelegate::initStyleOption(option, index);

        if (index.data().toString()=="")
            option->backgroundBrush = QBrush(QColor(255,0,0));
        else if (index.data().toString()=="OK")
            option->backgroundBrush = QBrush(QColor(0,175,80));
    }
};


DataBase::DataBase(QWidget *parent, QDialog* DBWindow)
    :QObject(parent)
{
    // Set element name
    setObjectName("DataBase");

    m_scanPageDeleguate = new OKColorDelegate();

    // Pointers to ImportPage elements
   { QList<QLineEdit*> ImportPageIOFieldsList = this->parent()->findChildren<QLineEdit*>();
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
    }

    // Pointers to IdentifyPage elements
   {
    QList<IdentifyPage*> IdentifyPageList = this->parent()->findChildren<IdentifyPage*>();
    for(int i = 0; i < IdentifyPageList.size() ; ++i)
        {
            if (IdentifyPageList.at(i)->objectName()=="IdentifyPage")
            {
                m_IdentifyPage = IdentifyPageList.at(i);
            }
        }
    QList<ProductNotFound*> IdentifyPageProductNotFoundList = this->parent()->findChildren<ProductNotFound*>();
    for(int i = 0; i < IdentifyPageProductNotFoundList.size() ; ++i)
        {
            if (IdentifyPageProductNotFoundList.at(i)->objectName()=="IdentifyPage_ProductNotFound")
            {
                m_IdentifyPage_productNotFound = IdentifyPageProductNotFoundList.at(i);
            }
        }
    QList<RoundPushButton*> IdentifyPageRoundPushButtonList = this->parent()->findChildren<RoundPushButton*>();
    for(int i = 0; i < IdentifyPageRoundPushButtonList.size() ; ++i)
    {
        if (IdentifyPageRoundPushButtonList.at(i)->objectName()=="IdentifyPage_RoundPushButton_continueButton")
        {
            m_IdentifyPage_continueButton = IdentifyPageRoundPushButtonList.at(i);
            QObject::connect(this, SIGNAL(sendIdentifyPageDone(bool)), m_IdentifyPage_continueButton, SLOT(setVisible(bool)));
            QObject::connect(m_IdentifyPage_continueButton, SIGNAL(clicked()), this, SLOT(sendScanPageInformations()));
        }
        if (IdentifyPageRoundPushButtonList.at(i)->objectName()=="IdentifyPage_RoundPushButton_cancelButton")
        {
            m_IdentifyPage_cancelButton = IdentifyPageRoundPushButtonList.at(i);
        }
    }
    QList<QLabel*> IdentifyPageLabelList = this->parent()->findChildren<QLabel*>();
    for(int i = 0; i < IdentifyPageLabelList.size() ; ++i)
    {
        if (IdentifyPageLabelList.at(i)->objectName()=="IdentifyPage_Label_continueLabel")
        {
            m_IdentifyPage_continueLabel = IdentifyPageLabelList.at(i);
            QObject::connect(this, SIGNAL(sendIdentifyPageDone(bool)), m_IdentifyPage_continueLabel, SLOT(setVisible(bool)));
        }
    }
    QList<QLineEdit*> IdentifyPageIOFieldsList = this->parent()->findChildren<QLineEdit*>();
    for(int i = 0; i < IdentifyPageIOFieldsList.size() ; ++i)
    {      
        if (IdentifyPageIOFieldsList.at(i)->objectName()=="IdentifyPage_LineEdit_palletID")
        {
            m_IdentifyPage_PalletID      = IdentifyPageIOFieldsList.at(i);
            QObject::connect(this, SIGNAL(sendIdentifyPagePalletId(const QString)), m_IdentifyPage_PalletID, SLOT(setText(const QString)));

        }
        if (IdentifyPageIOFieldsList.at(i)->objectName()=="IdentifyPage_LineEdit_boxQtyOnPallet")
        {
            m_IdentifyPage_BoxQty         = IdentifyPageIOFieldsList.at(i);
            QObject::connect(this, SIGNAL(sendIdentifyPageBoxQtyOnPallet(const QString)), m_IdentifyPage_BoxQty, SLOT(setText(const QString)));
        }
        if (IdentifyPageIOFieldsList.at(i)->objectName()=="IdentifyPage_LineEdit_totalValue")
        {
            m_IdentifyPage_TotalValue        = IdentifyPageIOFieldsList.at(i);
            QObject::connect(this, SIGNAL(sendIdentifyPagePalletValue(const QString)), m_IdentifyPage_TotalValue, SLOT(setText(const QString)));
        }
        if (IdentifyPageIOFieldsList.at(i)->objectName()=="IdentifyPage_LineEdit_boxID")
        {
            m_IdentifyPage_BoxID   = IdentifyPageIOFieldsList.at(i);
            QObject::connect(m_IdentifyPage_BoxID,  SIGNAL(returnPressed()),    this,   SLOT(sendIdentifyPageInformations()));
            //QObject::connect(m_IdentifyPage_BoxID,  SIGNAL(textChanged(QString)),    this,   SLOT(resetIdentifyPage(QString)));
        }
    }}

    // Pointers to ScanPage elements
   { QList<SQLView*> ScanPageTableList = this->parent()->findChildren<SQLView*>();
    for(int i = 0; i < ScanPageTableList.size() ; ++i)
    {
        if (ScanPageTableList.at(i)->objectName()=="ScanPage_SQLView_Table")
        {
            m_ScanPage_Table   = ScanPageTableList.at(i);
            QObject::connect(this, SIGNAL(sendScanPageTableData(QSqlQueryModel*)), m_ScanPage_Table, SLOT(setResults(QSqlQueryModel*)));
            QObject::connect(this, SIGNAL(hideScanPageTableColumn(int)), m_ScanPage_Table, SLOT(hideColumn(int)));
        }
    }
    QList<QLineEdit*> ScanPageIOFieldsList = this->parent()->findChildren<QLineEdit*>();
    for(int i = 0; i < ScanPageIOFieldsList.size() ; ++i)
    {
        if (ScanPageIOFieldsList.at(i)->objectName()=="ScanPage_LineEdit_BoxRef")
        {
            m_ScanPage_BoxRef = ScanPageIOFieldsList.at(i);
            QObject::connect(m_ScanPage_BoxRef, SIGNAL(returnPressed()), this, SLOT(scanPageBoxScanned()));
        }
    }
    QList<SureToCancel*> ScanPageSureToCancelList = this->parent()->findChildren<SureToCancel*>();
    for(int i = 0; i < ScanPageSureToCancelList.size() ; ++i)
    {
        if (ScanPageSureToCancelList.at(i)->objectName()=="ScanPage_SureToCancel")
        {
            m_ScanPage_sureToCancel   = ScanPageSureToCancelList.at(i);
            QObject::connect(m_ScanPage_sureToCancel, SIGNAL(sureToCancel_yes()), this, SLOT(scanPageCancelScanning()));
            QObject::connect(m_ScanPage_sureToCancel, SIGNAL(sureToCancel_yes()), this, SLOT(scanPageClearData()));
            QObject::connect(m_ScanPage_sureToCancel, SIGNAL(sureToCancel_yes()), this, SLOT(resetPalletScanned()));
        }
    }
    QList<SureToContinue*> ScanPageSureToContinueList = this->parent()->findChildren<SureToContinue*>();
    for(int i = 0; i < ScanPageSureToContinueList.size() ; ++i)
    {
        if (ScanPageSureToContinueList.at(i)->objectName()=="ScanPage_SureToContinue")
        {
            m_ScanPage_sureToContinue   = ScanPageSureToContinueList.at(i);
            QObject::connect(m_ScanPage_sureToContinue, SIGNAL(sureToContinue_yes()), this, SLOT(sendIntRepportPageInformations()));
        }
    }
    QList<RoundPushButton*> ScanPageRoundPushButtonList = this->parent()->findChildren<RoundPushButton*>();
    for(int i = 0; i < ScanPageRoundPushButtonList.size() ; ++i)
    {
        if (ScanPageRoundPushButtonList.at(i)->objectName()=="ScanPage_RoundPushButton_Cancel")
        {
            m_ScanPage_cancel = ScanPageRoundPushButtonList.at(i);
            QObject::connect(m_ScanPage_cancel, SIGNAL(clicked()), m_ScanPage_sureToCancel, SLOT(exec()));
        }
        if (ScanPageRoundPushButtonList.at(i)->objectName()=="ScanPage_RoundPushButton_Continue")
        {
            m_ScanPage_continue = ScanPageRoundPushButtonList.at(i);
            QObject::connect(m_ScanPage_continue, SIGNAL(clicked()), this, SLOT(scanPageEndScanning()));
        }

    }   
    QList<ProductNotFound*> ScanPageProductNotFoundList = this->parent()->findChildren<ProductNotFound*>();
    for(int i = 0; i < ScanPageProductNotFoundList.size() ; ++i)
        {
            if (ScanPageProductNotFoundList.at(i)->objectName()=="ScanPage_ProductNotFound")
            {
                m_ScanPage_productNotFound = ScanPageProductNotFoundList.at(i);
            }
        }
    }

    // Pointers to IntRepportPage elements
    {
    QList<QLineEdit*> IntReportPageIOFieldsList = this->parent()->findChildren<QLineEdit*>();
        for(int i = 0; i < IntReportPageIOFieldsList.size() ; ++i)
        {
            if (IntReportPageIOFieldsList.at(i)->objectName()=="IntRepportPage_LineEdit_palletIdIO")
            {
                m_IntReportPage_PalletID   = IntReportPageIOFieldsList.at(i);
                QObject::connect(this, SIGNAL(sendIntReportPagePalletId(const QString)), m_IntReportPage_PalletID,  SLOT(setText(const QString)));
            }
            if (IntReportPageIOFieldsList.at(i)->objectName()=="IntRepportPage_LineEdit_m_boxQtyIO")
            {
                m_IntReportPage_TotalBox      = IntReportPageIOFieldsList.at(i);
                QObject::connect(this, SIGNAL(sendIntReportPageTotalBox(const QString)), m_IntReportPage_TotalBox, SLOT(setText(const QString)));
            }
            if (IntReportPageIOFieldsList.at(i)->objectName()=="IntRepportPage_LineEdit_boxScannedQtyIO")
            {
                m_IntReportPage_BoxScanned         = IntReportPageIOFieldsList.at(i);
                QObject::connect(this, SIGNAL(sendIntReportPageBoxScanned(const QString)), m_IntReportPage_BoxScanned, SLOT(setText(const QString)));
            }
            if (IntReportPageIOFieldsList.at(i)->objectName()=="IntRepportPage_LineEdit_boxMissingQtyIO")
            {
                m_IntReportPage_BoxMissing        = IntReportPageIOFieldsList.at(i);
                QObject::connect(this, SIGNAL(sendIntReportPageBoxMissing(const QString)), m_IntReportPage_BoxMissing, SLOT(setText(const QString)));
            }
            if (IntReportPageIOFieldsList.at(i)->objectName()=="IntRepportPage_LineEdit_valueQtyIO")
            {
                m_IntReportPage_TotalValue        = IntReportPageIOFieldsList.at(i);
                QObject::connect(this, SIGNAL(sendIntReportPageTotalValue(const QString)), m_IntReportPage_TotalValue, SLOT(setText(const QString)));
            }
            if (IntReportPageIOFieldsList.at(i)->objectName()=="IntRepportPage_LineEdit_valueScannedQtyIO")
            {
                m_IntReportPage_ValueScanned        = IntReportPageIOFieldsList.at(i);
                QObject::connect(this, SIGNAL(sendIntReportPageScannedValue(const QString)), m_IntReportPage_ValueScanned, SLOT(setText(const QString)));
            }
            if (IntReportPageIOFieldsList.at(i)->objectName()=="IntRepportPage_LineEdit_valueMissingQtyIO")
            {
                m_IntReportPage_ValueMissing        = IntReportPageIOFieldsList.at(i);
                QObject::connect(this, SIGNAL(sendIntReportPageMissingValue(const QString)), m_IntReportPage_ValueMissing, SLOT(setText(const QString)));
            }
        }
    QList<SureToCancel*> IntReportSureToCancelList = this->parent()->findChildren<SureToCancel*>();
    for(int i = 0; i < IntReportSureToCancelList.size() ; ++i)
    {
        if (IntReportSureToCancelList.at(i)->objectName()=="IntRepportPage_SureToCancel")
        {
            m_IntReportPage_SureToCancel = IntReportSureToCancelList.at(i);
            QObject::connect(m_IntReportPage_SureToCancel, SIGNAL(sureToCancel_yes()), this, SLOT(scanPageCancelScanning()));
        }
    }
    QList<RoundPushButton*> IntReportPageRoundPushButtonList = this->parent()->findChildren<RoundPushButton*>();
    for(int i = 0; i < IntReportPageRoundPushButtonList.size() ; ++i)
    {
        if (IntReportPageRoundPushButtonList.at(i)->objectName()=="IntRepportPage_RoundPushButton_cancelButton")
        {
            m_IntReportPage_Cancel = IntReportPageRoundPushButtonList.at(i);
            QObject::connect(m_IntReportPage_Cancel, SIGNAL(clicked()), m_IntReportPage_SureToCancel, SLOT(exec()));
        }
        if (IntReportPageRoundPushButtonList.at(i)->objectName()=="IntRepportPage_RoundPushButton_rescanButton")
        {
            m_IntReportPage_Rescan = IntReportPageRoundPushButtonList.at(i);
            QObject::connect(m_IntReportPage_Rescan, SIGNAL(clicked()), this, SLOT(IntRepportPageSetPalletDone()));
            QObject::connect(m_IntReportPage_Rescan, SIGNAL(clicked()), this, SLOT(resetPalletScanned()));

        }
        if (IntReportPageRoundPushButtonList.at(i)->objectName()=="IntRepportPage_RoundPushButton_continueButton")
        {
            m_IntReportPage_Continue = IntReportPageRoundPushButtonList.at(i);
            QObject::connect(m_IntReportPage_Continue, SIGNAL(clicked()), this, SLOT(IntRepportPageSetPalletDone()));
            QObject::connect(m_IntReportPage_Continue, SIGNAL(clicked()), this, SLOT(resetPalletScanned()));
            QObject::connect(m_IntReportPage_Continue, SIGNAL(clicked()), this, SLOT(sendFinRepportPageInformations()));
        }
    }

    }

    // Pointers to FinRepportPage elements
    QList<SQLView*> FinRepportPageTableList = this->parent()->findChildren<SQLView*>();
    for(int i = 0; i < FinRepportPageTableList.size() ; ++i)
    {
        if (FinRepportPageTableList.at(i)->objectName()=="FinReportPage_SQLView_palletView")
        {
            m_FinReportPage_PalletView = FinRepportPageTableList.at(i);
            QObject::connect(this, SIGNAL(sendFinReportPagePalletTableData(QSqlQueryModel*)), m_FinReportPage_PalletView, SLOT(setResults(QSqlQueryModel*)));

        }
        if (FinRepportPageTableList.at(i)->objectName()=="FinReportPage_SQLView_boxScanned")
        {
            m_FinReportPage_BoxScannedView = FinRepportPageTableList.at(i);
            QObject::connect(this, SIGNAL(sendFinReportPageBoxScannedTableData(QSqlQueryModel*)), m_FinReportPage_BoxScannedView, SLOT(setResults(QSqlQueryModel*)));
        }
        if (FinRepportPageTableList.at(i)->objectName()=="FinReportPage_SQLView_boxMissing")
        {
            m_FinReportPage_BoxMissingView = FinRepportPageTableList.at(i);
            QObject::connect(this, SIGNAL(sendFinReportPageBoxMissingTableData(QSqlQueryModel*)), m_FinReportPage_BoxMissingView, SLOT(setResults(QSqlQueryModel*)));
        }
    }
    QList<PdfReport*> FinRepportPagePDFReportList = this->parent()->findChildren<PdfReport*>();
    for(int i = 0; i < FinRepportPagePDFReportList.size() ; ++i)
    {
        if (FinRepportPagePDFReportList.at(i)->objectName()=="PDFReport")
        {
            qDebug() << "PDFREPORT CONNECTED";
            m_FinReportPage_PDFReport = FinRepportPagePDFReportList.at(i);
            QObject::connect(this, SIGNAL(sendPDFInformationDone()), m_FinReportPage_PDFReport, SLOT(createDocument()));
        }
    }
    QList<RoundPushButton*> FinRepportPageRoundPushButtonList = this->parent()->findChildren<RoundPushButton*>();
    for(int i = 0; i < FinRepportPageRoundPushButtonList.size() ; ++i)
    {
        if (FinRepportPageRoundPushButtonList.at(i)->objectName()=="FinReportPage_RoundPushButton_saveButton")
        {
            m_FinReportPage_Save = FinRepportPageRoundPushButtonList.at(i);
            QObject::connect(m_FinReportPage_Save, SIGNAL(clicked()), this, SLOT(sendPDFInformations()));
        }
    }

    //Pointers to PDF elements
    {
        QList<PDFTableView*> PDFTableList = this->parent()->findChildren<PDFTableView*>();
        for(int i = 0; i < PDFTableList.size() ; ++i)
        {
            if (PDFTableList.at(i)->objectName()=="tabletemp")
            {
                m_PDF_DeliveryTable = PDFTableList.at(i);
                qDebug() << "Connected";
            }
        }
    }

    //Pointers to DataBaseWindow elements
  {
    QList<SQLView*> DataBaseWindowTableList = DBWindow->findChildren<SQLView*>();
    for(int i = 0; i < DataBaseWindowTableList.size() ; ++i)
    {
        if (DataBaseWindowTableList.at(i)->objectName()=="DataBaseWindow_SQLView_TableDataBase")
        {
            m_DBWindow_Table   = DataBaseWindowTableList.at(i);
            QObject::connect(this, SIGNAL(sendDBWindowTableData(QSqlQueryModel*)), m_DBWindow_Table, SLOT(setResults(QSqlQueryModel*)));
        }
    }
    QList<QComboBox*> DataBaseWindowComboBox = DBWindow->findChildren<QComboBox*>();
    for(int i = 0; i < DataBaseWindowComboBox.size() ; ++i)
    {
        if (DataBaseWindowComboBox.at(i)->objectName()=="DataBaseWindow_ComboBox_TableIndex")
        {
            m_DBWindow_selectTable   = DataBaseWindowComboBox.at(i);
            QObject::connect(m_DBWindow_selectTable,  SIGNAL(currentIndexChanged(int)),    this,   SLOT(sendDBWindowInformations(int)));
        }
    }
    QList<ImprovedLineEdit*> DataBaseWindowImprovedLineEdit = DBWindow->findChildren<ImprovedLineEdit*>();
    for(int i = 0; i < DataBaseWindowImprovedLineEdit.size() ; ++i)
    {
        if (DataBaseWindowImprovedLineEdit.at(i)->objectName()=="DataBaseWindow_LineEdit_Filter")
        {
            m_DBWindow_filter   = DataBaseWindowImprovedLineEdit.at(i);
            QObject::connect(m_DBWindow_filter,  SIGNAL(focussed(bool)),    this,   SLOT(resetDBWindowFilter(bool)));

        }
    }
    QList<QLabel*> DataBaseWindowLabel = DBWindow->findChildren<QLabel*>();
    for(int i = 0; i < DataBaseWindowLabel.size() ; ++i)
    {
        if (DataBaseWindowLabel.at(i)->objectName()=="DataBaseWindow_Label_FilterCheck")
        {
            m_DBWindow_queryLabel   = DataBaseWindowLabel.at(i);
            QObject::connect(m_DBWindow_filter,  SIGNAL(textChanged(QString)),    this,   SLOT(sendDBWindowCheckFilter(QString)));
            QObject::connect(this,  SIGNAL(isDBWindowQueryValid(bool)),    this,   SLOT(setDBWindowQueryValidLabel(bool)));
        }
    }
    QList<QPushButton*> DataBaseWindowPushButton = DBWindow->findChildren<QPushButton*>();
    for(int i = 0; i < DataBaseWindowPushButton.size() ; ++i)
    {
        if (DataBaseWindowPushButton.at(i)->objectName()=="DataBaseWindow_PushButton_okButton")
        {
            m_DBWindow_okButton   = DataBaseWindowPushButton.at(i);
            QObject::connect(m_DBWindow_okButton,  SIGNAL(clicked()),    this,   SLOT(sendDBWindowNewFilter()));
            QObject::connect(this,  SIGNAL(sendDBWindowFilter(QSqlQueryModel*)),    m_DBWindow_Table,   SLOT(setResults(QSqlQueryModel*)));

        }
    }
    }


    QObject::connect(this, SIGNAL(tableFillingDone()), this, SLOT(sendImportPageInformations()));
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
                   "IT_BA_Q             INT             NOT NULL, "
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
//                 "IT_DATE             DATETIME, "
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
                   "JO_Q                LONG INT        NOT NULL, "
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
                   "PA_ID               INT             NOT NULL, "//
                   "JO_ID               INT             NOT NULL, "
                   "TR_PA_EXIT          SMALLINT,                 "
                   "TR_PA_STATUS        SMALLINT,                 "
                   "TR_PA_STATUS_S      VARCHAR(40),              "
                   "TR_PA_DATE_IN       DATETIME,                 "
                   "TR_PA_DATE_OUT      DATETIME,                 "
                   "SH_ID               INT,                      "
                   "OP_ID               INT,                      "
                   "SCANNED             VARCHAR(10),              "
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
                   "SCANNED             VARCHAR(10),              "
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
                qry.append("\"\"");
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
                qry.append("\"\"");
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

void DataBase::resetPalletScanned()
{
    DataBase::setPalletScanned(-1);
}
/////////////////////////////////////////////////////////

void DataBase::sendImportPageInformations()
{
    emit sendImportPageDeliveryName(getImportPageDeliveryName());
    emit sendImportPagePalletQty(getImportPagePalletQty());
    emit sendImportPageBoxQty(getImportPageBoxQty());
    emit sendImportPagePackQty(getImportPagePackQty());
    emit sendImportPageTableData(getImportPageTableData());
    emit sendImportPageDone(true);
}

const QString DataBase::getImportPageDeliveryName()
{
    QSqlQuery query;
    QString qry = "SELECT DE_NAME "
                  "FROM DELIVERY;";
    if(!query.exec(qry)) return "Error";
    query.first();
    return query.value(0).toString().length()<1?"Error":query.value(0).toString();
}

const QString DataBase::getImportPagePalletQty()
{
    QSqlQuery query;
    QString qry = "SELECT COUNT(DL_PA_ID) "
                  "FROM DELIVERY_LIST;";
    if(!query.exec(qry)) return "Error";
    query.first();
    return query.value(0).toString().length()<1?"Error":query.value(0).toString();
}

const QString DataBase::getImportPageBoxQty()
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

const QString DataBase::getImportPagePackQty()
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

QSqlQueryModel* DataBase::getImportPageTableData()
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

/////////////////////////////////////////////////////////

void DataBase::sendIdentifyPageInformations()
{
    emit sendIdentifyPagePalletId(getIdentifyPagePalletId());
    emit sendIdentifyPageBoxQtyOnPallet(getIdentifyPageBoxQtyOnPallet());
    emit sendIdentifyPagePalletValue(getIdentifyPagePalletValue());
    if ((getIdentifyPagePalletId()=="") || (getIdentifyPageBoxQtyOnPallet()=="") || (getIdentifyPagePalletValue()==""))
    {
        emit sendIdentifyPageDone(false);
        m_IdentifyPage_productNotFound->exec();
        m_IdentifyPage->clearIdentifyPage("");
    }
    else
    {
        emit sendIdentifyPageDone(true);
        setPalletScanned(m_IdentifyPage_PalletID->text().toInt());
    }

}

const QString DataBase::getIdentifyPagePalletId()
{
    QSqlQuery query;
    QString qry = "SELECT TRACEABILITY_PALLET.PA_ID "
                   "FROM "
                    "(TRACEABILITY_PALLET INNER JOIN TRACEABILITY_BOX "
                        "ON TRACEABILITY_PALLET.PA_ID = TRACEABILITY_BOX.PA_ID) "
                            "INNER JOIN DELIVERY_LIST "
                                "ON TRACEABILITY_PALLET.PA_ID = DELIVERY_LIST.DL_PA_ID "
                                    "WHERE (((TRACEABILITY_BOX.TR_BO_ID)=\""
                                        + m_IdentifyPage_BoxID->text()
                                            +"\"));";

    if(!query.exec(qry))
    {
        qDebug() << query.lastError().text();
        return "Error";
    }
    if (!query.first()) return "";

    return query.value(0).toString().length()<1?"":query.value(0).toString();
}

const QString DataBase::getIdentifyPageBoxQtyOnPallet()
{
    if (m_IdentifyPage_PalletID->text().isEmpty()) return "";

    QSqlQuery query;
    QString qry = "SELECT Count(TRACEABILITY_BOX.BO_ID) AS CompteDeBO_ID "
                    "FROM "
                        "(TRACEABILITY_PALLET INNER JOIN TRACEABILITY_BOX "
                            "ON TRACEABILITY_PALLET.PA_ID = TRACEABILITY_BOX.PA_ID) "
                                "INNER JOIN DELIVERY_LIST "
                                    "ON TRACEABILITY_PALLET.PA_ID = DELIVERY_LIST.DL_PA_ID "
                                        "GROUP BY TRACEABILITY_PALLET.PA_ID "
                                            "HAVING (((TRACEABILITY_PALLET.PA_ID)=" + m_IdentifyPage_PalletID->text() + "));";

    if(!query.exec(qry))
    {
        qDebug() << query.lastError().text();
        return "Error";
    }
    query.first();
    return query.value(0).toString().length()<1?"":query.value(0).toString();
}

const QString DataBase::getIdentifyPagePalletValue()
{
    if (m_IdentifyPage_PalletID->text().isEmpty()) return "";
    QSqlQuery query;
    QString qry = "SELECT SUM(ITEMS.IT_ROLL_Q*ITEMS.IT_BA_Q*ITEMS.IT_VALUE) AS Total "
                    "FROM "
                        "ITEMS INNER JOIN "
                            "(JOBORDER INNER JOIN "
                                  "(((TRACEABILITY_PALLET INNER JOIN DELIVERY_LIST "
                                        "ON TRACEABILITY_PALLET.PA_ID = DELIVERY_LIST.DL_PA_ID) "
                                            "INNER JOIN TRACEABILITY_BOX "
                                                "ON TRACEABILITY_PALLET.PA_ID = TRACEABILITY_BOX.PA_ID) "
                                                    "INNER JOIN TRACEABILITY_BATCH "
                                                        "ON TRACEABILITY_BOX.BO_ID = TRACEABILITY_BATCH.BO_ID) "
                                  "ON (JOBORDER.JO_ID = TRACEABILITY_PALLET.JO_ID) AND (JOBORDER.JO_ID = TRACEABILITY_BOX.JO_ID) AND (JOBORDER.JO_ID = TRACEABILITY_BATCH.JO_ID)) "
                            "ON ITEMS.IT_ID = JOBORDER.JO_IT_ID "
                                "GROUP BY TRACEABILITY_PALLET.PA_ID "
                                    "HAVING (((TRACEABILITY_PALLET.PA_ID)=" + m_IdentifyPage_PalletID->text() + "));";

    if(!query.exec(qry))
    {
        qDebug() << query.lastError().text();
        return "";
    }
    query.first();
    if (query.value(0).toString().length()<1)
    {
        return "";
    }
    else
    {
        return (QString::number(query.value(0).toString().toDouble(),'f',2)) + " Rp";
    }
}

void DataBase::setPalletScanned (int scannedValue)
{
    palletScanned = scannedValue;
}

/////////////////////////////////////////////////////////

void DataBase::sendScanPageInformations()
{
    emit sendScanPageTableData(getScanPageTableData());
    emit hideScanPageTableColumn(1);

}

QSqlQueryModel* DataBase::getScanPageTableData()
{
    QSqlQuery *query = new QSqlQuery;
    QSqlQueryModel *Results = new QSqlQueryModel();
    QString qry = QString("SELECT TRACEABILITY_BOX.SCANNED AS [Status], TRACEABILITY_PALLET.PA_ID AS [Pallet ID], TRACEABILITY_BOX.TR_BO_ID AS [Box Reference], ITEMS.IT_VALUE || \" Rp\" AS Denomination, COUNT(TRACEABILITY_BATCH.TR_BA_ID) AS [Pack Qty], (COUNT(TRACEABILITY_BATCH.TR_BA_ID)*ITEMS.IT_BA_Q) AS [Roll Qty], (COUNT(TRACEABILITY_BATCH.TR_BA_ID)*ITEMS.IT_BA_Q*ITEMS.IT_ROLL_Q) AS [Coin Qty], (COUNT(TRACEABILITY_BATCH.TR_BA_ID)*ITEMS.IT_BA_Q*ITEMS.IT_ROLL_Q*ITEMS.IT_VALUE)  || \" Rp\" AS [Total value], ITEMS.IT_YEAR AS [Coin Year] "
                 "FROM "
                    "((ITEMS INNER JOIN "
                        "(JOBORDER INNER JOIN "
                            "(TRACEABILITY_PALLET INNER JOIN DELIVERY_LIST "
                            "ON TRACEABILITY_PALLET.PA_ID = DELIVERY_LIST.DL_PA_ID) "
                        "ON JOBORDER.JO_ID = TRACEABILITY_PALLET.JO_ID) "
                    "ON ITEMS.IT_ID = JOBORDER.JO_IT_ID) "
                    "INNER JOIN TRACEABILITY_BATCH ON JOBORDER.JO_ID = TRACEABILITY_BATCH.JO_ID) "
                    "INNER JOIN TRACEABILITY_BOX ON (TRACEABILITY_PALLET.PA_ID = TRACEABILITY_BOX.PA_ID) AND (TRACEABILITY_BOX.BO_ID = TRACEABILITY_BATCH.BO_ID) AND (JOBORDER.JO_ID = TRACEABILITY_BOX.JO_ID) "
                 "GROUP BY TRACEABILITY_BOX.SCANNED, TRACEABILITY_PALLET.PA_ID, TRACEABILITY_BOX.TR_BO_ID, ITEMS.IT_VALUE, ITEMS.IT_BA_Q, ITEMS.IT_ROLL_Q, ITEMS.IT_YEAR "
                    "HAVING (((TRACEABILITY_PALLET.PA_ID)=%1)) "
                 "ORDER BY TRACEABILITY_BOX.TR_BO_ID;").arg(palletScanned);
    if(!query->exec(qry))
    {
        qDebug() << query->lastError().text();
    }
    Results->setQuery(*query);
    return Results;
}

void DataBase::scanPageBoxScanned()
{
    qDebug() << "pallet scanned : " << palletScanned;
    if(!scanPageCheckBoxExists(m_ScanPage_BoxRef->text()))
    {
        m_ScanPage_productNotFound->exec();
        m_ScanPage_BoxRef->clear();
        return;
    }
    scanPageUpdateBoxScanned(m_ScanPage_BoxRef->text());
    emit sendScanPageTableData(getScanPageTableData());

    m_ScanPage_Table->scrollTo(m_ScanPage_Table->model()->match(m_ScanPage_Table->model()->index(0,2),Qt::DisplayRole, m_ScanPage_BoxRef->text(), 1, Qt::MatchStartsWith).at(0));
    m_ScanPage_BoxRef->clear();
    m_ScanPage_Table->setItemDelegate(m_scanPageDeleguate);
}

bool DataBase::scanPageCheckBoxExists(QString ref)
{
    QSqlQuery query;
    QString qry = QString("SELECT COUNT(TRACEABILITY_BOX.BO_ID) "
                  "FROM TRACEABILITY_BOX "
                  "WHERE (((TRACEABILITY_BOX.TR_BO_ID)=\"" + ref +"\") AND ((TRACEABILITY_BOX.PA_ID)= %1 ));").arg(palletScanned);

    if(!query.exec(qry))
    {
        qDebug() << query.lastError().text();
        return false;
    }
    query.first();
    if (query.value(0).toInt() != 1) return  false;
    return true;
}

void DataBase::scanPageUpdateBoxScanned(QString ref)
{
    QSqlQuery query;
    QString qry = "UPDATE TRACEABILITY_BOX "
                  "SET SCANNED = \"OK\" "
                  "WHERE TR_BO_ID=\"" + ref +"\";";

    if(!query.exec(qry))
    {
        qDebug() << query.lastError().text();
        return;
    }
}

void DataBase::scanPageClearData()
{
    m_ScanPage_BoxRef->clear();
    QSqlQueryModel *Results = new QSqlQueryModel();
    Results->clear();
    emit sendScanPageTableData(Results);
}

void DataBase::scanPageCancelScanning()
{
    QSqlQuery query;
    QString qry = QString("UPDATE TRACEABILITY_BOX "
                  "SET SCANNED = \"\" "
                  "WHERE PA_ID = %1 ;").arg(palletScanned);
    if(!query.exec(qry))
    {
        qDebug() << query.lastError().text();
        return;
    }
}

void DataBase::scanPageEndScanning()
{
    int TotalBox = 0, BoxScanned=0;
    QSqlQuery query;
    QString qry;
    qry = QString("SELECT COUNT(TRACEABILITY_BOX.BO_ID) "
                  "FROM TRACEABILITY_BOX "
                  "WHERE (((TRACEABILITY_BOX.SCANNED)=\"OK\") AND ((TRACEABILITY_BOX.PA_ID)= %1 ));").arg(palletScanned);
    if(!query.exec(qry))
    {
        qDebug() << query.lastError().text();
        return;
    }
    query.first();
    BoxScanned = query.value(0).toInt();

    qry = QString("SELECT COUNT(TRACEABILITY_BOX.BO_ID) "
                  "FROM TRACEABILITY_BOX "
                  "WHERE (((TRACEABILITY_BOX.PA_ID)= %1 ));").arg(palletScanned);
    if(!query.exec(qry))
    {
        qDebug() << query.lastError().text();
        return;
    }
    query.first();
    TotalBox = query.value(0).toInt();

    if (TotalBox > BoxScanned)
        m_ScanPage_sureToContinue->exec();
    else
    {
        QList<MenuButton *> menuButtons = this->parent()->findChildren<MenuButton *>();
        MenuButton *intRepportButton;
        for(int i = 0; i < menuButtons.size() ; ++i)
        {
            if (menuButtons.at(i)->objectName()=="menuButton_IntRepport")
            {
                intRepportButton = menuButtons.at(i);
                intRepportButton->enable();
                static_cast<MainWindow*>(this->parent())->setIntRepportPage();
                sendIntRepportPageInformations();
            }
        }
    }
}


/////////////////////////////////////////////////////////

void DataBase::sendIntRepportPageInformations()
{
    emit sendIntReportPagePalletId(getIntReportPagePalletId());
    emit sendIntReportPageTotalBox(getIntReportPageTotalBox());
    emit sendIntReportPageBoxScanned(getIntReportPageBoxScanned());
    emit sendIntReportPageBoxMissing(getIntReportPageBoxMissing());
    emit sendIntReportPageTotalValue(getIntReportPageTotalValue());
    emit sendIntReportPageScannedValue(getIntReportPageScannedValue());
    emit sendIntReportPageMissingValue(getIntReportPageMissingValue());
}

const QString   DataBase::getIntReportPagePalletId()
{
    return QString("%1").arg(palletScanned);
}

const QString   DataBase::getIntReportPageTotalBox()
{
    QSqlQuery query;
    QString qry = QString("SELECT COUNT(TR_BO_ID) "
                          "FROM TRACEABILITY_BOX "
                          "WHERE PA_ID = %1;").arg(palletScanned);
    if(!query.exec(qry)) return "Error";
    query.first();
    return query.value(0).toString().length()<1?"Error":query.value(0).toString();
}

const QString   DataBase::getIntReportPageBoxScanned()
{
    QSqlQuery query;
    QString qry = QString("SELECT COUNT(TR_BO_ID) "
                          "FROM TRACEABILITY_BOX "
                          "WHERE PA_ID = %1 AND SCANNED = \"OK\";").arg(palletScanned);
    if(!query.exec(qry)) return "Error";
    query.first();
    return query.value(0).toString().length()<1?"Error":query.value(0).toString();
}

const QString   DataBase::getIntReportPageBoxMissing()
{
    int BoxTotal = 0, BoxScanned = 0;
    QSqlQuery query;
    QString qry;
    qry = QString("SELECT COUNT(TR_BO_ID) "
                  "FROM TRACEABILITY_BOX "
                  "WHERE PA_ID = %1;").arg(palletScanned);
    if(!query.exec(qry)) return "Error";
    query.first();
    BoxTotal = query.value(0).toInt();

    qry = QString("SELECT COUNT(TR_BO_ID) "
                  "FROM TRACEABILITY_BOX "
                  "WHERE PA_ID = %1 AND SCANNED = \"OK\";").arg(palletScanned);
    if(!query.exec(qry)) return "Error";
    query.first();
    BoxScanned = query.value(0).toInt();

    return QString("%1").arg(BoxTotal-BoxScanned);
}

const QString   DataBase::getIntReportPageTotalValue()
{
    QSqlQuery query;
    QString qry = QString("SELECT SUM(ITEMS.IT_VALUE*ITEMS.IT_ROLL_Q*ITEMS.IT_BA_Q*ITEMS.IT_BOX_Q) || \" Rp\" "
                          "FROM "
                            "((ITEMS INNER JOIN JOBORDER ON ITEMS.IT_ID = JOBORDER.JO_IT_ID) "
                                "INNER JOIN TRACEABILITY_BOX ON JOBORDER.JO_ID = TRACEABILITY_BOX.JO_ID) "
                                    "INNER JOIN TRACEABILITY_PALLET ON (TRACEABILITY_PALLET.PA_ID = TRACEABILITY_BOX.PA_ID) AND (JOBORDER.JO_ID = TRACEABILITY_PALLET.JO_ID) "
                          "GROUP BY TRACEABILITY_PALLET.PA_ID "
                          "HAVING (((TRACEABILITY_PALLET.PA_ID)=%1));").arg(palletScanned);
    if(!query.exec(qry)) return "Error";
    query.first();
    return query.value(0).toString();
}

const QString   DataBase::getIntReportPageScannedValue()
{
    QSqlQuery query;
    QString qry = QString("SELECT SUM(ITEMS.IT_VALUE*ITEMS.IT_ROLL_Q*ITEMS.IT_BA_Q*ITEMS.IT_BOX_Q) || \" Rp\" "
                          "FROM "
                            "((ITEMS INNER JOIN JOBORDER ON ITEMS.IT_ID = JOBORDER.JO_IT_ID) "
                                "INNER JOIN TRACEABILITY_BOX ON JOBORDER.JO_ID = TRACEABILITY_BOX.JO_ID) "
                                    "INNER JOIN TRACEABILITY_PALLET ON (TRACEABILITY_PALLET.PA_ID = TRACEABILITY_BOX.PA_ID) AND (JOBORDER.JO_ID = TRACEABILITY_PALLET.JO_ID) "
                          "GROUP BY TRACEABILITY_PALLET.PA_ID, TRACEABILITY_BOX.SCANNED "
                          "HAVING (((TRACEABILITY_PALLET.PA_ID)=%1) AND ((TRACEABILITY_BOX.SCANNED)= \"OK\"));").arg(palletScanned);
    if(!query.exec(qry)) return "Error";
    query.first();
    return query.value(0).toString();
}

const QString   DataBase::getIntReportPageMissingValue()
{
    double ValueTotal = 0, ValueScanned = 0;
    QSqlQuery query;
    QString qry;
    qry = QString("SELECT SUM(ITEMS.IT_VALUE*ITEMS.IT_ROLL_Q*ITEMS.IT_BA_Q*ITEMS.IT_BOX_Q) "
                  "FROM "
                  "((ITEMS INNER JOIN JOBORDER ON ITEMS.IT_ID = JOBORDER.JO_IT_ID) "
                  "INNER JOIN TRACEABILITY_BOX ON JOBORDER.JO_ID = TRACEABILITY_BOX.JO_ID) "
                  "INNER JOIN TRACEABILITY_PALLET ON (TRACEABILITY_PALLET.PA_ID = TRACEABILITY_BOX.PA_ID) AND (JOBORDER.JO_ID = TRACEABILITY_PALLET.JO_ID) "
                  "GROUP BY TRACEABILITY_PALLET.PA_ID "
                  "HAVING (((TRACEABILITY_PALLET.PA_ID)=%1));").arg(palletScanned);
    if(!query.exec(qry)) return "Error";
    query.first();
    ValueTotal = query.value(0).toDouble();

    qry = QString("SELECT SUM(ITEMS.IT_VALUE*ITEMS.IT_ROLL_Q*ITEMS.IT_BA_Q*ITEMS.IT_BOX_Q) "
                  "FROM "
                  "((ITEMS INNER JOIN JOBORDER ON ITEMS.IT_ID = JOBORDER.JO_IT_ID) "
                  "INNER JOIN TRACEABILITY_BOX ON JOBORDER.JO_ID = TRACEABILITY_BOX.JO_ID) "
                  "INNER JOIN TRACEABILITY_PALLET ON (TRACEABILITY_PALLET.PA_ID = TRACEABILITY_BOX.PA_ID) AND (JOBORDER.JO_ID = TRACEABILITY_PALLET.JO_ID) "
                  "GROUP BY TRACEABILITY_PALLET.PA_ID, TRACEABILITY_BOX.SCANNED "
                  "HAVING (((TRACEABILITY_PALLET.PA_ID)=%1) AND ((TRACEABILITY_BOX.SCANNED)=\"OK\"));").arg(palletScanned);
    if(!query.exec(qry)) return "Error";
    query.first();
    ValueScanned = query.value(0).toDouble();
    return QString::number(ValueTotal-ValueScanned,'f',1) + " Rp";
}

bool DataBase::IntRepportPageSetPalletDone()
{
    QSqlQuery query;
    QString qry = QString("UPDATE TRACEABILITY_PALLET "
                          "SET SCANNED = \"OK\" "
                          "WHERE PA_ID = %1 ;").arg(palletScanned);
    if(!query.exec(qry))
    {
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}

/////////////////////////////////////////////////////////

void DataBase::sendFinRepportPageInformations()
{
    QSqlQueryModel *Empty = new QSqlQueryModel();
    Empty->clear();
    OKNOKColorDelegate *Delegate = new OKNOKColorDelegate(this);
    emit sendFinReportPagePalletTableData(getFinReportPagePalletTableData());
    QObject::connect(m_FinReportPage_PalletView->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(FinReportPagePalletSelected(const QModelIndex &, const QModelIndex &)));
    m_FinReportPage_PalletView->setItemDelegate(Delegate);
    emit sendFinReportPageBoxScannedTableData(Empty);
    emit sendFinReportPageBoxMissingTableData(Empty);

}

void DataBase::FinReportPagePalletSelected(const QModelIndex &current, const QModelIndex &previous)
{
    OKColorDelegate *OKDelegate = new OKColorDelegate(this);
    NOKColorDelegate *NOKDelegate = new NOKColorDelegate(this);
    Q_UNUSED(previous)
    unsigned int palletID = m_FinReportPage_PalletView->model()->index(current.row(),1).data().toUInt();
    emit sendFinReportPageBoxScannedTableData(getFinReportPageBoxScannedTableData(palletID));
    emit sendFinReportPageBoxMissingTableData(getFinReportPageBoxMissingTableData(palletID));
    m_FinReportPage_BoxScannedView->setItemDelegate(OKDelegate);
    m_FinReportPage_BoxMissingView->setItemDelegate(NOKDelegate);
}

QSqlQueryModel* DataBase::getFinReportPagePalletTableData()
{
    QSqlQuery *query = new QSqlQuery;
    QSqlQueryModel *Results = new QSqlQueryModel();
    QString qry = "SELECT TRACEABILITY_PALLET.SCANNED AS Status, TRACEABILITY_PALLET.PA_ID AS [Pallet ID], Count(TRACEABILITY_BOX.BO_ID) AS [Box Qty], ITEMS.IT_VALUE || \" Rp\" AS Denomination "//, Count(TRACEABILITY_BOX.SCANNED) AS [Box Scanned], ((Count(TRACEABILITY_BOX.BO_ID))-(Count(TRACEABILITY_BOX.SCANNED))) AS [Box Missing] "
                  "FROM "
                    "(ITEMS INNER JOIN JOBORDER ON ITEMS.IT_ID = JOBORDER.JO_IT_ID) "
                        "INNER JOIN (TRACEABILITY_PALLET INNER JOIN TRACEABILITY_BOX ON TRACEABILITY_PALLET.PA_ID = TRACEABILITY_BOX.PA_ID) "
                        "ON (JOBORDER.JO_ID = TRACEABILITY_PALLET.JO_ID) AND (JOBORDER.JO_ID = TRACEABILITY_BOX.JO_ID) "
                  "GROUP BY TRACEABILITY_PALLET.SCANNED, TRACEABILITY_PALLET.PA_ID, ITEMS.IT_VALUE "
                  "ORDER BY TRACEABILITY_PALLET.PA_ID;";
    if(!query->exec(qry))
    {
        qDebug() << query->lastError().text();
    }
    Results->setQuery(*query);
    return Results;
}

QSqlQueryModel* DataBase::getFinReportPageBoxScannedTableData(unsigned int palletID)
{
    QSqlQuery *query = new QSqlQuery;
    QSqlQueryModel *Results = new QSqlQueryModel();
    QString qry = QString("SELECT TRACEABILITY_BOX.SCANNED AS Status, TRACEABILITY_PALLET.PA_ID, TRACEABILITY_BOX.BO_ID AS [Box ID], ITEMS.IT_BOX_Q AS [Pack Qty], (IT_BA_Q*(ITEMS.IT_BOX_Q)) AS [Roll Qty], (IT_ROLL_Q*(IT_BA_Q*(ITEMS.IT_BOX_Q))) AS [Coin Qty], ITEMS.IT_VALUE || \" Rp\" AS Denomination, (ITEMS.IT_VALUE*(IT_ROLL_Q*(IT_BA_Q*(ITEMS.IT_BOX_Q)))) || \" Rp\" AS [Value], ITEMS.IT_YEAR AS [Year] "
                          "FROM "
                            "ITEMS INNER JOIN "
                                "(JOBORDER INNER JOIN "
                                    "(TRACEABILITY_PALLET INNER JOIN TRACEABILITY_BOX "
                                    "ON TRACEABILITY_PALLET.PA_ID = TRACEABILITY_BOX.PA_ID) "
                                "ON (JOBORDER.JO_ID = TRACEABILITY_PALLET.JO_ID) AND (JOBORDER.JO_ID = TRACEABILITY_BOX.JO_ID)) "
                            "ON ITEMS.IT_ID = JOBORDER.JO_IT_ID "
                          "WHERE (((TRACEABILITY_PALLET.PA_ID)=%1) AND ((TRACEABILITY_BOX.SCANNED)=\"OK\"));").arg(palletID);
    if(!query->exec(qry))
    {
        qDebug() << query->lastError().text();
    }
    Results->setQuery(*query);
    return Results;
}

QSqlQueryModel* DataBase::getFinReportPageBoxMissingTableData(unsigned int palletID)
{
    QSqlQuery *query = new QSqlQuery;
    QSqlQueryModel *Results = new QSqlQueryModel();
    QString qry = QString("SELECT TRACEABILITY_BOX.SCANNED AS Status, TRACEABILITY_PALLET.PA_ID, TRACEABILITY_BOX.BO_ID AS [Box ID], ITEMS.IT_BOX_Q AS [Pack Qty], (IT_BA_Q*(ITEMS.IT_BOX_Q)) AS [Roll Qty], (IT_ROLL_Q*(IT_BA_Q*(ITEMS.IT_BOX_Q))) AS [Coin Qty], ITEMS.IT_VALUE || \" Rp\" AS Denomination, (ITEMS.IT_VALUE*(IT_ROLL_Q*(IT_BA_Q*(ITEMS.IT_BOX_Q)))) || \" Rp\" AS [Value], ITEMS.IT_YEAR AS [Year] "
                          "FROM "
                            "ITEMS INNER JOIN "
                                "(JOBORDER INNER JOIN "
                                    "(TRACEABILITY_PALLET INNER JOIN TRACEABILITY_BOX "
                                    "ON TRACEABILITY_PALLET.PA_ID = TRACEABILITY_BOX.PA_ID) "
                                "ON (JOBORDER.JO_ID = TRACEABILITY_PALLET.JO_ID) AND (JOBORDER.JO_ID = TRACEABILITY_BOX.JO_ID)) "
                            "ON ITEMS.IT_ID = JOBORDER.JO_IT_ID "
                          "WHERE (((TRACEABILITY_PALLET.PA_ID)=%1) AND ((TRACEABILITY_BOX.SCANNED)=\"\"));").arg(palletID);
    if(!query->exec(qry))
    {
        qDebug() << query->lastError().text();
    }
    Results->setQuery(*query);
    return Results;
}

/////////////////////////////////////////////////////////

void DataBase::sendPDFInformations()
{
    m_PDF_DeliveryTable->setModel(getFinReportPagePalletTableData());

    emit sendPDFInformationDone();
}
/////////////////////////////////////////////////////////

void DataBase::sendDBWindowInformations(int)
{
  m_DBWindow_filter->setText("PERSONALIZED SQL STATEMENT");
  emit sendDBWindowTableData(getDBWindowFilter());
}

void DataBase::sendDBWindowNewFilter()
{
    emit sendDBWindowFilter(getDBWindowFilter());
}

void DataBase::sendDBWindowCheckFilter(QString)
{
    emit isDBWindowQueryValid(checkDBWindowFilter());
}

void DataBase::setDBWindowQueryValidLabel(bool valid)
{
    QPalette pal;
    if (valid)
    {
        m_DBWindow_queryLabel->setText("QUERY OK");

        pal = m_DBWindow_queryLabel  ->palette();
        pal.setColor(m_DBWindow_queryLabel->foregroundRole(),Qt::darkGreen);
        m_DBWindow_queryLabel->setPalette(pal);
    }
    else
    {
        m_DBWindow_queryLabel->setText("QUERY NOT OK");

        pal = m_DBWindow_queryLabel  ->palette();
        pal.setColor(m_DBWindow_queryLabel->foregroundRole(),Qt::red);
        m_DBWindow_queryLabel->setPalette(pal);
    }
}

void DataBase::resetDBWindowFilter(bool reset)
{
    if (reset)
    {
        m_DBWindow_filter->clear();
    }

}

QSqlQueryModel* DataBase::getDBWindowFilter()
{
    QSqlQuery *query = new QSqlQuery;
    QSqlQueryModel *Results = new QSqlQueryModel();

    QString qry = "";
    QString Filter = m_DBWindow_filter->text();
    int index = m_DBWindow_selectTable->currentIndex();

    switch(index)
    {
        case 0:
        qry="";
        break;

        case 1:
        // CSV_ITEMS_NAME;
        qry = "SELECT "
                "ITEMS.IT_NAME AS [Name], ITEMS.IT_VALUE || \" Rp\" AS [Value], "
                        "ITEMS.IT_ROLL_Q AS [Qty per Roll], ITEMS.IT_BA_Q AS [Qty per Pack], ITEMS.IT_BOX_Q AS [Qty per Box], "
                        "ITEMS.IT_YEAR AS [Year] "
                            "FROM ITEMS";
        break;

        case 2:
        //CSV_JOBORDER_NAME;
        qry = "SELECT "
                "JOBORDER.JO_NAME AS [Name], JOBORDER.JO_DESC AS [Description] "
                            "FROM JOBORDER";
        break;

        case 3:
        // CSV_TRACEABILITY_BATCH_NAME;
        qry = "SELECT "
                "TRACEABILITY_BATCH.TR_BA_ID AS [ID], TRACEABILITY_BATCH.JO_ID AS [Job Order ID], "
                    "TRACEABILITY_BATCH.BO_ID AS [Box ID], TRACEABILITY_BATCH.TR_BA_STATUS_S AS [Status] "
                        "FROM TRACEABILITY_BATCH";
        break;

        case 4:
        //CSV_TRACEABILITY_BOX_NAME;
        qry = "SELECT "
                "TRACEABILITY_BOX.TR_BO_ID AS [ID], TRACEABILITY_BOX.JO_ID AS [Job Order ID], "
                    "TRACEABILITY_BOX.PA_ID AS [Pallet ID], TRACEABILITY_BOX.TR_BO_STATUS_S AS [Status] "
                        "FROM TRACEABILITY_BOX";
        break;

        case 5:
        //CSV_TRACEABILITY_PALLET_NAME;
        qry = "SELECT "
                "TRACEABILITY_PALLET.PA_ID AS [ID], TRACEABILITY_PALLET.JO_ID AS [Job Order ID], "
                    "TRACEABILITY_PALLET.TR_PA_EXIT AS [Exit], TRACEABILITY_PALLET.TR_PA_STATUS_S AS [Status] "
                        "FROM TRACEABILITY_PALLET";

        break;

        case 6:
        //CSV_DELIVERY_NAME;
        qry = "SELECT "
                "DELIVERY.DE_ID AS [ID], DELIVERY.DE_NAME AS [Name], DELIVERY.DE_CUSTOMER AS [Customer], "
                    "DELIVERY.DE_STATUS_S AS [Status], DELIVERY.DE_DATE AS [Date] "
                        "FROM DELIVERY";
        break;

        case 7:
        //CSV_DELIVERY_LIST_NAME;
        qry = "SELECT "
                "DELIVERY_LIST.DL_ID AS [ID], DELIVERY_LIST.DL_DE_ID AS [Delivery ID], "
                    "DELIVERY_LIST.DL_PA_ID AS [Pallet ID], DELIVERY_LIST.DL_DATE AS [Date] "
                     "FROM DELIVERY_LIST";

        break;
    }
   if (Filter == "PERSONALIZED SQL STATEMENT")
    {
        qry+=";";
    }
    else
    {
        qry += " " + Filter + ";";

    }
    if(!query->exec(qry))
    {
        qDebug() << query->lastError().text();
    }
    Results->setQuery(*query);
    return Results;
}

bool DataBase::checkDBWindowFilter()
{
    QSqlQuery *query = new QSqlQuery;

    QString qry = "";
    QString Filter = m_DBWindow_filter->text();
    int index = m_DBWindow_selectTable->currentIndex();

    if (Filter == "PERSONALIZED SQL STATEMENT")
     {
        return true;
     }
    switch(index)
    {
        case 0:
        break;

        case 1:
        // CSV_ITEMS_NAME;
        qry = "SELECT "
                "ITEMS.IT_NAME AS [Name], ITEMS.IT_VALUE || \" Rp\" AS [Value], "
                        "ITEMS.IT_ROLL_Q AS [Qty per Roll], ITEMS.IT_BA_Q AS [Qty per Pack], ITEMS.IT_BOX_Q AS [Qty per Box], "
                        "ITEMS.IT_YEAR AS [Year] "
                            "FROM ITEMS";
        break;

        case 2:
        //CSV_JOBORDER_NAME;
        qry = "SELECT "
                "JOBORDER.JO_NAME AS [Name], JOBORDER.JO_DESC AS [Description] "
                            "FROM JOBORDER";
        break;

        case 3:
        // CSV_TRACEABILITY_BATCH_NAME;
        qry = "SELECT "
                "TRACEABILITY_BATCH.TR_BA_ID AS [ID], TRACEABILITY_BATCH.JO_ID AS [Job Order ID], "
                    "TRACEABILITY_BATCH.BO_ID AS [Box ID], TRACEABILITY_BATCH.TR_BA_STATUS_S AS [Status] "
                        "FROM TRACEABILITY_BATCH";
        break;

        case 4:
        //CSV_TRACEABILITY_BOX_NAME;
        qry = "SELECT "
                "TRACEABILITY_BOX.TR_BO_ID AS [ID], TRACEABILITY_BOX.JO_ID AS [Job Order ID], "
                    "TRACEABILITY_BOX.PA_ID AS [Pallet ID], TRACEABILITY_BOX.TR_BO_STATUS_S AS [Status] "
                        "FROM TRACEABILITY_BOX";
        break;

        case 5:
        //CSV_TRACEABILITY_PALLET_NAME;
        qry = "SELECT "
                "TRACEABILITY_PALLET.PA_ID AS [ID], TRACEABILITY_PALLET.JO_ID AS [Job Order ID], "
                    "TRACEABILITY_PALLET.TR_PA_EXIT AS [Exit], TRACEABILITY_PALLET.TR_PA_STATUS_S AS [Status] "
                        "FROM TRACEABILITY_PALLET";

        break;

        case 6:
        //CSV_DELIVERY_NAME;
        qry = "SELECT "
                "DELIVERY.DE_ID AS [ID], DELIVERY.DE_NAME AS [Name], DELIVERY.DE_CUSTOMER AS [Customer], "
                    "DELIVERY.DE_STATUS_S AS [Status], DELIVERY.DE_DATE AS [Date] "
                        "FROM DELIVERY";
        break;

        case 7:
        //CSV_DELIVERY_LIST_NAME;
        qry = "SELECT "
                "DELIVERY_LIST.DL_ID AS [ID], DELIVERY_LIST.DL_DE_ID AS [Delivery ID], "
                    "DELIVERY_LIST.DL_PA_ID AS [Pallet ID], DATE(DELIVERY_LIST.DL_DATE) AS [Date] "
                     "FROM DELIVERY_LIST";

        break;
    }

    qry += " " + Filter + ";";
    if(!query->exec(qry))
    {
        return false;
    }
    return true;
}

/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////





