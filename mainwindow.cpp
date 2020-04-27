#include "MainWindow.h"
#include "globals/globals.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    if(!createLogFile(LOG_PATH))
    {
        QMessageBox::critical(nullptr, QObject::tr("Main error"),
                    QObject::tr("Unable to create log file at path : %1\n"
                                "CODE : 12345\n\n"
                                "Click OK to exit.").arg(LOG_PATH), QMessageBox::Ok);
        QApplication::quit();
    }
    MainWindow::appendLogFile(LOG_PATH,"blblbl. CODE 12345");
    MainWindow::appendLogFile(LOG_PATH,"Unable to create ITEMS table. CODE : 12345");

    setWindowTitle("VELEC SYSTEMS - Delivery Checker - v1.0");
    setObjectName("MainWindow");

    m_infobar       = new InfoBar(this);
    importPage      = new ImportPage(this);
    identifyPage    = new IdentifyPage(this);
    scanPage        = new ScanPage(this);
    intRepportPage  = new IntRepportPage(this);
    finRepportPage  = new FinRepportPage(this);
    stackedWidget   = new QStackedWidget(this);
    m_windowDB      = new DataBaseWindow(this);
    DB              = new DataBase(this);
    m_menu          = new SideMenu(this);

    if (!DB->createConnection()) return;
    stackedWidget->addWidget(importPage);
    stackedWidget->addWidget(identifyPage);
    stackedWidget->addWidget(scanPage);
    stackedWidget->addWidget(intRepportPage);
    stackedWidget->addWidget(finRepportPage);

    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setSpacing(0);
    m_mainLayout->setMargin(0);

    m_infoLayout = new QVBoxLayout;
    m_infoLayout->addWidget(stackedWidget);
    m_infoLayout->addWidget(m_infobar);

    m_mainLayout->addWidget(m_menu, 10);
    m_mainLayout->addLayout(m_infoLayout, 90);

    setLayout(m_mainLayout);

    stackedWidget->setCurrentIndex(0);
    m_windowDB->show();

    m_popUp = new SureToCancel(this);
    m_popUp->show();


    //looking for QLineEdit in IdentifyPage
    QList<QLineEdit*> IdentifyPageIOFieldsList = this->findChildren<QLineEdit*>();
    for(int i = 0; i < IdentifyPageIOFieldsList.size() ; ++i)
    {
        if (IdentifyPageIOFieldsList.at(i)->objectName()=="IdentifyPage_LineEdit_palletID")
        {
            m_IdentifyPage_PalletID     = IdentifyPageIOFieldsList.at(i);
        }
        if (IdentifyPageIOFieldsList.at(i)->objectName()=="IdentifyPage_LineEdit_boxQtyOnPallet")
        {
            m_IdentifyPage_BoxQty       = IdentifyPageIOFieldsList.at(i);
        }
        if (IdentifyPageIOFieldsList.at(i)->objectName()=="IdentifyPage_LineEdit_totalValue")
        {
            m_IdentifyPage_TotalValue   = IdentifyPageIOFieldsList.at(i);
        }
        if (IdentifyPageIOFieldsList.at(i)->objectName()=="IdentifyPage_LineEdit_boxID")
        {
            m_IdentifyPage_BoxID        = IdentifyPageIOFieldsList.at(i);
        }
    }
}

MainWindow::~MainWindow()
{
    delete m_menu;
    delete m_mainLayout;
}

void MainWindow::setImportPage()
{
    int currentIndex = stackedWidget->currentIndex();
    int setIndex = 0;
    if ((currentIndex >= 0 && currentIndex < stackedWidget->count()) && (setIndex >= 0 && setIndex < stackedWidget->count()))
    {
        stackedWidget->setCurrentIndex(setIndex);
    }
}

void MainWindow::setIdentifyPage()
{
    int currentIndex = stackedWidget->currentIndex();
    int setIndex = 1;
    if ((currentIndex >= 0 && currentIndex < stackedWidget->count()) && (setIndex >= 0 && setIndex < stackedWidget->count()))
    {
        stackedWidget->setCurrentIndex(setIndex);
    }
    m_IdentifyPage_PalletID->clear();
    m_IdentifyPage_BoxID->clear();
    m_IdentifyPage_TotalValue->clear();
    m_IdentifyPage_BoxQty->clear();
    m_IdentifyPage_BoxID->setFocus();

}

void MainWindow::setScanPage()
{
    int currentIndex = stackedWidget->currentIndex();
    int setIndex = 2;
    if ((currentIndex >= 0 && currentIndex < stackedWidget->count()) && (setIndex >= 0 && setIndex < stackedWidget->count()))
    {
        stackedWidget->setCurrentIndex(setIndex);
    }
}

void MainWindow::setIntRepportPage()
{
    int currentIndex = stackedWidget->currentIndex();
    int setIndex = 3;
    if ((currentIndex >= 0 && currentIndex < stackedWidget->count()) && (setIndex >= 0 && setIndex < stackedWidget->count()))
    {
        stackedWidget->setCurrentIndex(setIndex);
    }
}

void MainWindow::setFinRepportPage()
{
    int currentIndex = stackedWidget->currentIndex();
    int setIndex = 4;
    if ((currentIndex >= 0 && currentIndex < stackedWidget->count()) && (setIndex >= 0 && setIndex < stackedWidget->count()))
    {
        stackedWidget->setCurrentIndex(setIndex);
    }
}


bool MainWindow::createLogFile(const QString path)
{
    QString pathName = path + "LogFile.txt";
    QFile file (pathName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Error : could not open file " << pathName ;
        return false;
    }

    file.close();
    qDebug() << "Success creating file " << pathName;
    return true;
}

void MainWindow::appendLogFile(const QString path, const QString data)
{
    QString pathName = path + "LogFile.txt";
    QFile file (pathName);

    if (!file.exists() || !file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Error : file " << pathName << " does not exist or is unable to be opened";
        return;
    }

    QString date = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss:zzz");//"dddd dd MMMM yyyy hh:mm:ss.zzz"
    QTextStream out(&file);
    out << "\n" << date << " | " << data;
    file.close();

    qDebug() << "Success writting in file " << pathName;
}
