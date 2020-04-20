#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

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
