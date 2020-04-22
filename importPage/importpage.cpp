#include "importpage.h"
#include "DB/database.h"

QString CSV_FOLDER_PATH;

ImportPage::ImportPage(QWidget *parent)
    : QWidget(parent)
{
    // Set element name
    setObjectName("ImportPage");
    // Set elements size policy
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Creates all children
    m_layout        = new QVBoxLayout(this);
    m_plusButton    = new RoundPushButton("+", this);
    m_addButton     = new PillsPushButton("Import\nData", this, "Add");
    m_deliveryInfo  = new DeliveryInfo(this);
    m_checkBox      = new PillsPushButton("Check boxes", this, "Check");
    QSizePolicy sp_retain = m_checkBox->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    m_checkBox->setSizePolicy(sp_retain);
    m_checkBox      ->setVisible(false);

    // Signal & slot connection
    QList<MenuButton *> menuButtons = this->parent()->findChildren<MenuButton *>();
    MenuButton *identifyButton;
    for(int i = 0; i < menuButtons.size() ; ++i)
    {
        if (menuButtons.at(i)->objectName()=="menuButton_Identify")
        {
            identifyButton = menuButtons.at(i);
            QObject::connect(m_checkBox,  SIGNAL(clicked()),    identifyButton,   SLOT(enable()));
            QObject::connect(m_checkBox,  SIGNAL(clicked()),    this->parent(),   SLOT(setIdentifyPage()));
        }
    }
    QObject::connect(m_plusButton,  SIGNAL(clicked()), this, SLOT(getData()));
    QObject::connect(m_addButton,   SIGNAL(clicked()), this, SLOT(getData()));


    // Layout management
    m_layout        ->addWidget(m_plusButton);
    m_layout        ->addWidget(m_addButton);
    m_layout        ->addWidget(m_deliveryInfo);
    m_layout        ->addWidget(m_checkBox);
    m_layout        ->setAlignment(m_plusButton, Qt::AlignHCenter);
    m_layout        ->setAlignment(m_addButton, Qt::AlignHCenter);
    m_layout        ->setAlignment(m_deliveryInfo, Qt::AlignHCenter);
    m_layout        ->setAlignment(m_checkBox, Qt::AlignHCenter);
    setLayout(m_layout);
}

bool ImportPage::getData()
{
    bool success = false;
    do
    {
        getPath();
        if (!checkFilesExists()) return false;
        QList<DataBase *> dataBase = this->parent()->parent()->findChildren<DataBase *>();
        if (dataBase.count()!=1)
        {
            QMessageBox::critical(nullptr, QObject::tr("Database error"),
                                  QObject::tr("Unable to access database\n"
                                              "CODE : 12345\n\n"
                                              "Click OK to exit."), QMessageBox::Ok);
            return false;
        }
        success = dataBase.first()->fillTables();
    } while (!success);
    

    return true;
}

void ImportPage::getPath()
{
    CSV_FOLDER_PATH = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        QDir::homePath()+"\\"+QStandardPaths::displayName(QStandardPaths::DesktopLocation),
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
}

bool ImportPage::checkFilesExists()
{
    bool found;
    QDir Folder(CSV_FOLDER_PATH);
    QFileInfoList FileList = Folder.entryInfoList(QDir::Files);
    QRegExp ExpFileSearch;
    QString FileSearch;
    // Allowed file name pattern : NAME.csv OR NAME_JJMMAAAA_hhmmss.csv OR NAME_JJMMAA_hhmmss.csv

    // Check if file ITEMS exists
    FileSearch = CSV_ITEMS_NAME;
    found = false;
    ExpFileSearch.setPattern("("+FileSearch+"){1}((_)*(\\d){6,8}(_)*(\\d){6})?(.csv)$");
    for (int i = 0; i < FileList.size(); ++i)
    {
        if (ExpFileSearch.exactMatch(FileList.at(i).fileName())) found = true;
    }
    if (!found)
    {
        QMessageBox::critical(nullptr, QObject::tr("Main error"),
                              QObject::tr("File %1 not found\n"
                                          "CODE : 12345\n\n"
                                          "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
        return false;
    }


    // Check if file JOBORDER.csv exists
    FileSearch = CSV_JOBORDER_NAME;
    found = false;
    ExpFileSearch.setPattern("("+FileSearch+"){1}((_)*(\\d){6,8}(_)*(\\d){6})?(.csv)$");
    for (int i = 0; i < FileList.size(); ++i)
    {
        if (ExpFileSearch.exactMatch(FileList.at(i).fileName())) found = true;
    }
    if (!found)
    {
        QMessageBox::critical(nullptr, QObject::tr("Main error"),
                              QObject::tr("File %1 not found\n"
                                          "CODE : 12345\n\n"
                                          "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
        return false;
    }

    // Check if file TRACEABILITY_BATCH.csv exists
    FileSearch = CSV_TRACEABILITY_BATCH_NAME;
    found = false;
    ExpFileSearch.setPattern("("+FileSearch+"){1}((_)*(\\d){6,8}(_)*(\\d){6})?(.csv)$");
    for (int i = 0; i < FileList.size(); ++i)
    {
        if (ExpFileSearch.exactMatch(FileList.at(i).fileName())) found = true;
    }
    if (!found)
    {
        QMessageBox::critical(nullptr, QObject::tr("Main error"),
                              QObject::tr("File %1 not found\n"
                                          "CODE : 12345\n\n"
                                          "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
        return false;
    }

    // Check if file TRACEABILITY_BOX.csv exists
    FileSearch = CSV_TRACEABILITY_BOX_NAME;
    found = false;
    ExpFileSearch.setPattern("("+FileSearch+"){1}((_)*(\\d){6,8}(_)*(\\d){6})?(.csv)$");
    for (int i = 0; i < FileList.size(); ++i)
    {
        if (ExpFileSearch.exactMatch(FileList.at(i).fileName())) found = true;
    }
    if (!found)
    {
        QMessageBox::critical(nullptr, QObject::tr("Main error"),
                              QObject::tr("File %1 not found\n"
                                          "CODE : 12345\n\n"
                                          "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
        return false;
    }

    // Check if file TRACEABILITY_PALLET.csv exists
    FileSearch = CSV_TRACEABILITY_PALLET_NAME;
    found = false;
    ExpFileSearch.setPattern("("+FileSearch+"){1}((_)*(\\d){6,8}(_)*(\\d){6})?(.csv)$");
    for (int i = 0; i < FileList.size(); ++i)
    {
        if (ExpFileSearch.exactMatch(FileList.at(i).fileName())) found = true;
    }
    if (!found)
    {
        QMessageBox::critical(nullptr, QObject::tr("Main error"),
                              QObject::tr("File %1 not found\n"
                                          "CODE : 12345\n\n"
                                          "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
        return false;
    }

    // Check if file DELIVERY.csv exists
    FileSearch = CSV_DELIVERY_NAME;
    found = false;
    ExpFileSearch.setPattern("("+FileSearch+"){1}((_)*(\\d){6,8}(_)*(\\d){6})?(.csv)$");
    for (int i = 0; i < FileList.size(); ++i)
    {
        if (ExpFileSearch.exactMatch(FileList.at(i).fileName())) found = true;
    }
    if (!found)
    {
        QMessageBox::critical(nullptr, QObject::tr("Main error"),
                              QObject::tr("File %1 not found\n"
                                          "CODE : 12345\n\n"
                                          "Click OK to exit.").arg(FileSearch), QMessageBox::Ok);
        return false;
    }

    // Check if file DELIVERY_LIST.csv exists
    FileSearch = CSV_DELIVERY_LIST_NAME;
    found = false;
    ExpFileSearch.setPattern("("+FileSearch+"){1}((_)*(\\d){6,8}(_)*(\\d){6})?(.csv)$");
    for (int i = 0; i < FileList.size(); ++i)
    {
        if (ExpFileSearch.exactMatch(FileList.at(i).fileName())) found = true;
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
