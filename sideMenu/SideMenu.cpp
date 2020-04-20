#include "SideMenu.h"
#include "../MainWindow.h"

SideMenu::SideMenu(QWidget *parent)
    : QWidget(parent)
{
    // Set name
    setObjectName("sideMenu");

    // Set menu background
    QPalette pal = palette();
    pal.setColor(QPalette::Background, MENU_BACKGROUND_COLOR);
    setAutoFillBackground(true);
    setPalette(pal);

    // Create elements
    m_boutonImport      = new MenuButton("1", "Import Data",            this, "Import");
    m_boutonIdentify    = new MenuButton("2", "Identify",               this, "Identify");
    m_boutonScan        = new MenuButton("3", "Scan Products",          this, "Scan");
    m_boutonIntRepport  = new MenuButton("4", "Intermediary\nRepport",  this, "IntRepport");
    m_boutonFinRepport  = new MenuButton("5", "Final\nRepport",         this, "FinRepport");

    // Set elements size policy
    m_boutonImport      -> setSizePolicy(QSizePolicy ::Minimum, QSizePolicy ::Fixed);
    m_boutonIdentify    -> setSizePolicy(QSizePolicy ::Minimum, QSizePolicy ::Fixed);
    m_boutonScan        -> setSizePolicy(QSizePolicy ::Minimum, QSizePolicy ::Fixed);
    m_boutonIntRepport  -> setSizePolicy(QSizePolicy ::Minimum, QSizePolicy ::Fixed);
    m_boutonFinRepport  -> setSizePolicy(QSizePolicy ::Minimum, QSizePolicy ::Fixed);

    if (CLICK_SIDEMENU_ALLOWED)
    {
        QObject::connect(m_boutonImport,    SIGNAL(clicked()),  m_boutonImport,     SLOT(enable()));
        QObject::connect(m_boutonIdentify,  SIGNAL(clicked()),  m_boutonIdentify,   SLOT(enable()));
        QObject::connect(m_boutonScan,      SIGNAL(clicked()),  m_boutonScan,       SLOT(enable()));
        QObject::connect(m_boutonIntRepport,SIGNAL(clicked()),  m_boutonIntRepport, SLOT(enable()));
        QObject::connect(m_boutonFinRepport,SIGNAL(clicked()),  m_boutonFinRepport, SLOT(enable()));

        MainWindow *mainWindow = dynamic_cast<MainWindow *> (parent);
        if (0 != mainWindow)
        {
            QObject::connect(m_boutonImport,    SIGNAL(clicked()),  mainWindow,   SLOT(setImportPage()));
            QObject::connect(m_boutonIdentify,  SIGNAL(clicked()),  mainWindow,   SLOT(setIdentifyPage()));
            QObject::connect(m_boutonScan,      SIGNAL(clicked()),  mainWindow,   SLOT(setScanPage()));
            QObject::connect(m_boutonIntRepport,SIGNAL(clicked()),  mainWindow,   SLOT(setIntRepportPage()));
            QObject::connect(m_boutonFinRepport,SIGNAL(clicked()),  mainWindow,   SLOT(setFinRepportPage()));
        }
    }


    // Create layout and place elements
    m_Layout = new QVBoxLayout;
    m_Layout->addWidget(m_boutonImport);
    m_Layout->addWidget(m_boutonIdentify);
    m_Layout->addWidget(m_boutonScan);
    m_Layout->addWidget(m_boutonIntRepport);
    m_Layout->addWidget(m_boutonFinRepport);
    m_Layout->addStretch();
    m_Layout->setSpacing(0);
    m_Layout->setMargin(0);
    setLayout(m_Layout);

    m_boutonImport->enable();
}

SideMenu::~SideMenu()
{
    delete m_boutonImport;
    delete m_boutonIdentify;
    delete m_boutonScan;
    delete m_boutonIntRepport;
    delete m_boutonFinRepport;
    delete m_Layout;
}
