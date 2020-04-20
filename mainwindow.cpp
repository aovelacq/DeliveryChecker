#include "MainWindow.h"
#include "globals/globals.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    createLogFile(CSV_LOG_PATH);
    MainWindow::appendLogFile(CSV_LOG_PATH,"blblbl. CODE 12345");
    MainWindow::appendLogFile(CSV_LOG_PATH,"Unable to create ITEMS table. CODE : 12345");

    setWindowTitle("VELEC SYSTEMS - Delivery Checker - v1.0");
    setObjectName("MainWindow");


    temp = new QPushButton(this);

    m_menu = new SideMenu(this);
    m_infobar = new InfoBar(this);
    m_spacer = new QSpacerItem(20,20,QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

    importPage = new ImportPage(this);
    identifyPage = new IdentifyPage(this);
    stackedWidget = new QStackedWidget(this);
    DB = new DataBase(this);
    if (!DB->createConnection()) return;
    stackedWidget->addWidget(importPage);
    stackedWidget->addWidget(identifyPage);


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
    bool res;
    QString pathName = path + "LogFile.txt";
    QFile file (pathName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << "FILE LOG\n";
        file.close();
        res = true;
        qDebug() << "Success creating file " << pathName;
    }
    else
    {
        res = false;
        qDebug() << "Error : could not open file " << pathName ;
    }

    return res;
}

void MainWindow::appendLogFile(const QString path, const QString data)
{
    QString pathName = path + "LogFile.txt";
    QFile file (pathName);

    if (!file.exists())
    {
        qDebug() << "Error : file " << pathName << " does not exist";
        return;
    }

    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QString date = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss:zzz");//"dddd dd MMMM yyyy hh:mm:ss.zzz"

        QTextStream out(&file);
        out << "\n" << date << " | " << data;
        file.close();

        qDebug() << "Success writting in file " << pathName;
    }
    else
    {
        qDebug() << "Error : could not open file " << pathName;
    }
    return;
}
