#include "identifypage.h"

IdentifyPage::IdentifyPage(QWidget *parent)
    : QWidget(parent)
{
    QPalette pal;
    QFont font;
    QString styleSheet;

    // Set element name
    setObjectName("IdentifyPage");
    // Set element size policy
    setMinimumWidth(1100);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Creates all children
    m_layout        = new QVBoxLayout(this);

    m_scanText      = new QLabel("Scan the QR code on a box to identify the pallet",this);

    QGridLayout * m_layoutButton = new QGridLayout();

    m_cancelButton  = new RoundPushButton("x", this);
    m_cancelLabel   = new QLabel ("Cancel",this);

    m_continueButton= new RoundPushButton(">", this);
    m_continueLabel = new QLabel ("Continue",this);

    QGridLayout * m_layoutPallet = new QGridLayout();
    QWidget * m_rectangle = new QWidget();

    m_boxIdLabel     = new QLabel("Box ID", this);
    m_boxIdIO        = new QLineEdit(this);
    m_boxIdIO        ->setObjectName("LineEdit_boxID");
    m_boxIdIO       ->setText("1");

    m_palletIdLabel  = new QLabel("Pallet ID", this);
    m_palletIdIO     = new QLineEdit(this);
    m_palletIdIO     ->setObjectName("LineEdit_palletID");

    m_boxQtyLabel    = new QLabel("Box quantity", this);
    m_boxQtyIO       = new QLineEdit(this);
    m_boxQtyIO       ->setObjectName("LineEdit_boxQtyOnPallet");

    m_totalValueLabel= new QLabel("Total value", this);
    m_totalValueIO   = new QLineEdit(this);
    m_totalValueIO   ->setObjectName("LineEdit_totalValue");


    //PalletInfo Design
    pal.setColor(QPalette::Background, MENU_BACKGROUND_COLOR);
    m_rectangle->setAutoFillBackground(true);
    setPalette(pal);

    pal = m_boxIdLabel->palette();
    pal.setColor(m_boxIdLabel->foregroundRole(), MENU_FONT_COLOR);
    m_boxIdLabel        ->setPalette(pal);
    m_palletIdLabel     ->setPalette(pal);
    m_boxQtyLabel       ->setPalette(pal);
    m_totalValueLabel   ->setPalette(pal);

    pal = m_boxIdLabel->palette();
    pal.setColor(m_boxIdLabel->backgroundRole(), MENU_BACKGROUND_COLOR);
    m_boxIdLabel        ->setPalette(pal);
    m_palletIdLabel     ->setPalette(pal);
    m_boxQtyLabel       ->setPalette(pal);
    m_totalValueLabel   ->setPalette(pal);

    font = m_boxIdLabel->font();
    font.setPointSize(16);
    m_boxIdLabel        ->setFont(font);
    m_palletIdLabel     ->setFont(font);
    m_boxQtyLabel        ->setFont(font);
    m_totalValueLabel   ->setFont(font);

    font = m_boxIdIO->font();
    font.setPointSize(16);
    m_boxIdIO           ->setFont(font);
    m_palletIdIO        ->setFont(font);
    m_boxQtyIO          ->setFont(font);
    m_totalValueIO      ->setFont(font);

    m_boxIdLabel        ->setMinimumHeight(40);
    m_boxIdIO           ->setMinimumHeight(40);
    m_palletIdLabel     ->setMinimumHeight(40);
    m_palletIdIO        ->setMinimumHeight(40);
    m_boxQtyLabel       ->setMinimumHeight(40);
    m_boxQtyIO          ->setMinimumHeight(40);
    m_totalValueLabel   ->setMinimumHeight(40);
    m_totalValueIO      ->setMinimumHeight(40);

    m_boxIdLabel        ->setAlignment(Qt::AlignCenter);
    m_boxIdIO           ->setAlignment(Qt::AlignCenter);
    m_palletIdLabel     ->setAlignment(Qt::AlignCenter);
    m_palletIdIO        ->setAlignment(Qt::AlignCenter);
    m_boxQtyLabel       ->setAlignment(Qt::AlignCenter);
    m_boxQtyIO          ->setAlignment(Qt::AlignCenter);
    m_totalValueLabel   ->setAlignment(Qt::AlignCenter);
    m_totalValueIO      ->setAlignment(Qt::AlignCenter);

    m_boxIdLabel        ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_boxIdIO           ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_palletIdLabel     ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_palletIdIO        ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_boxQtyLabel       ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_boxQtyIO          ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_totalValueLabel   ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_totalValueIO      ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    m_boxIdIO           ->setReadOnly(false);
    m_palletIdIO        ->setReadOnly(true);
    m_boxQtyIO          ->setReadOnly(true);
    m_totalValueIO      ->setReadOnly(true);

    m_layoutPallet->addWidget(m_boxIdLabel,    0, 1, 1, 3);
    m_layoutPallet->addWidget(m_boxIdIO,       1, 1, 1, 3);
    m_layoutPallet->addWidget(m_palletIdLabel, 2, 0, 1, 1);
    m_layoutPallet->addWidget(m_palletIdIO,    3, 0, 1, 1);
    m_layoutPallet->addWidget(m_boxQtyLabel,   2, 2, 1, 1);
    m_layoutPallet->addWidget(m_boxQtyIO,      3, 2, 1, 1);
    m_layoutPallet->addWidget(m_totalValueLabel,2, 4, 1, 1);
    m_layoutPallet->addWidget(m_totalValueIO,  3, 4, 1, 1);

    m_layoutPallet->setColumnStretch(0,28);
    m_layoutPallet->setColumnStretch(1,8);
    m_layoutPallet->setColumnStretch(2,28);
    m_layoutPallet->setColumnStretch(3,8);
    m_layoutPallet->setColumnStretch(4,28);




    //Design Buttons
    pal.setColor(m_cancelLabel->foregroundRole(), MENU_BACKGROUND_COLOR);
    m_continueLabel     ->setPalette(pal);
    m_cancelLabel       ->setPalette(pal);
    m_scanText          ->setPalette(pal);

    font.setPointSize(16);
    m_continueLabel     ->setFont(font);
    m_cancelLabel       ->setFont(font);
    m_scanText          ->setFont(font);

    m_cancelLabel       ->setMinimumHeight(40);
    m_continueLabel     ->setMinimumHeight(40);
    m_scanText          ->setMinimumHeight(40);

    m_layoutButton->addWidget(m_cancelButton,   0, 0, 2, 1, Qt::AlignCenter);
    m_layoutButton->addWidget(m_cancelLabel,    2, 0, 1, 1, Qt::AlignCenter);
    m_layoutButton->addWidget(m_continueButton, 0, 4, 2, 1, Qt::AlignCenter);
    m_layoutButton->addWidget(m_continueLabel,  2, 4, 1, 1, Qt::AlignCenter);

    m_layoutButton->setColumnStretch(0,28);
    m_layoutButton->setColumnStretch(1,8);
    m_layoutButton->setColumnStretch(2,28);
    m_layoutButton->setColumnStretch(3,8);
    m_layoutButton->setColumnStretch(4,28);

    m_continueButton->setVisible(false);
    m_continueLabel ->setVisible(false);


    // Signal & slot connection
    QList<MenuButton *> menuButtons = this->parent()->findChildren<MenuButton *>();
    MenuButton *button;
    for(int i = 0; i < menuButtons.size() ; ++i)
    {
        if (menuButtons.at(i)->objectName()=="menuButton_Scan")
        {
            button = menuButtons.at(i);
            QObject::connect(m_continueButton,  SIGNAL(clicked()),    button,   SLOT(enable()));
            QObject::connect(m_continueButton,  SIGNAL(clicked()),    this->parent(),   SLOT(setScanPage()));
        }
        else if (menuButtons.at(i)->objectName()=="menuButton_Import")
        {
            button = menuButtons.at(i);
            QObject::connect(m_cancelButton,  SIGNAL(clicked()),    button,   SLOT(enable()));
            QObject::connect(m_cancelButton,  SIGNAL(clicked()),    this->parent(),   SLOT(setImportPage()));
        }
    }
    QObject::connect(m_boxIdIO,  SIGNAL(returnPressed()),    this,   SLOT(accessContinue()));
    QObject::connect(m_boxIdIO,  SIGNAL(textChanged(QString)),    this,   SLOT(noaccessContinue(QString)));
    QObject::connect(m_boxIdIO,  SIGNAL(returnPressed()),    this,   SLOT(getData()));

    // Layout management
    m_rectangle->setLayout(m_layoutPallet);

    m_layout        ->addWidget(m_scanText);
    m_layout        ->addWidget(m_rectangle);
    m_layout        ->addSpacing(180);
    m_layout        ->addLayout(m_layoutButton);

    m_layout        ->setAlignment(m_scanText, Qt::AlignHCenter);
    m_layout        ->setAlignment(m_layoutButton, Qt::AlignHCenter);

    //m_boxIdIO       ->setFocus(Qt::TabFocusReason);
    //QTest::keyClick(m_boxIdIO, Qt::Key_Tab);
}

void IdentifyPage::accessContinue()
{
    m_continueButton->setVisible(true);
    m_continueLabel->setVisible(true);
}

void IdentifyPage::noaccessContinue(const QString)
{
    m_continueButton->setVisible(false);
    m_continueLabel->setVisible(false);

    //m_boxIdIO        ->setText("");
    m_palletIdIO     ->setText("");
    m_boxQtyIO       ->setText("");
    m_totalValueIO   ->setText("");
}

bool IdentifyPage::getData()
{
    bool success = false;
    //do
    {
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
    } //while (!success);


    return true;
}
