#include "intrepportpage.h"


IntRepportPage::IntRepportPage(QWidget *parent)
    : QWidget(parent)
{
    QPalette pal;
    QFont font;

    // Set element name
    setObjectName("IntRepportPage");
    // Set element size policy
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // Creates all children
    m_layout                = new QVBoxLayout(this);
    m_cancelButton          = new RoundPushButton(":/img/img/BackOff.png",":/img/img/BackOn.png",this);
    m_cancelLabel           = new QLabel ("Cancel",this);
    m_rescanButton          = new RoundPushButton(":/img/img/NewOff.png",":/img/img/NewOn.png",this);
    m_rescanLabel           = new QLabel ("Scan another\npallet",this);
    m_continueButton        = new RoundPushButton(":/img/img/ArrowOff.png",":/img/img/ArrowOn.png",this);
    m_continueLabel         = new QLabel ("Continue",this);
    m_titleLabel            = new QLabel("Intermediary report", this);
    m_palletIdLabel         = new QLabel("Pallet ID", this);
    m_palletIdIO            = new QLineEdit(this);
    m_boxQtyLabel           = new QLabel("Box quantity", this);
    m_boxQtyIO              = new QLineEdit(this);
    m_boxScannedQtyLabel    = new QLabel("Box scanned", this);
    m_boxScannedQtyIO       = new QLineEdit(this);
    m_boxMissingQtyLabel    = new QLabel("Box missing", this);
    m_boxMissingQtyIO       = new QLineEdit(this);
    m_valueQtyLabel         = new QLabel("Value", this);
    m_valueQtyIO            = new QLineEdit(this);
    m_valueScannedQtyLabel  = new QLabel("Value scanned", this);
    m_valueScannedQtyIO     = new QLineEdit(this);
    m_valueMissingQtyLabel  = new QLabel("Value missing", this);
    m_valueMissingQtyIO     = new QLineEdit(this);
    m_sureToCancel          = new SureToCancel(this);

    QGridLayout * m_layoutInfo      = new QGridLayout();
    QGridLayout * m_layoutButton    = new QGridLayout();
    QWidget     * m_rectangle       = new QWidget();

    m_layout                ->setObjectName("IntRepportPage_VBoxLayout_mainLayout");
    m_cancelButton          ->setObjectName("IntRepportPage_RoundPushButton_cancelButton");
    m_cancelLabel           ->setObjectName("IntRepportPage_Label_cancelLabel");
    m_rescanButton          ->setObjectName("IntRepportPage_RoundPushButton_rescanButton");
    m_rescanLabel           ->setObjectName("IntRepportPage_Label_rescanLabel");
    m_continueButton        ->setObjectName("IntRepportPage_RoundPushButton_continueButton");
    m_continueLabel         ->setObjectName("IntRepportPage_Label_continueLabel");
    m_titleLabel            ->setObjectName("IntRepportPage_Label_titleLabel");
    m_palletIdLabel         ->setObjectName("IntRepportPage_Label_palletIdLabel");
    m_palletIdIO            ->setObjectName("IntRepportPage_LineEdit_palletIdIO");
    m_boxQtyLabel           ->setObjectName("IntRepportPage_Label_boxQtyLabel");
    m_boxQtyIO              ->setObjectName("IntRepportPage_LineEdit_m_boxQtyIO");
    m_boxScannedQtyLabel    ->setObjectName("IntRepportPage_Label_boxScannedQtyLabel");
    m_boxScannedQtyIO       ->setObjectName("IntRepportPage_LineEdit_boxScannedQtyIO");
    m_boxMissingQtyLabel    ->setObjectName("IntRepportPage_Label_boxMissingQtyLabel");
    m_boxMissingQtyIO       ->setObjectName("IntRepportPage_LineEdit_boxMissingQtyIO");
    m_valueQtyLabel         ->setObjectName("IntRepportPage_Label_valueQtyLabel");
    m_valueQtyIO            ->setObjectName("IntRepportPage_LineEdit_valueQtyIO");
    m_valueScannedQtyLabel  ->setObjectName("IntRepportPage_Label_valueScannedQtyLabel");
    m_valueScannedQtyIO     ->setObjectName("IntRepportPage_LineEdit_valueScannedQtyIO");
    m_valueMissingQtyLabel  ->setObjectName("IntRepportPage_Label_valueMissingQtyLabel");
    m_valueMissingQtyIO     ->setObjectName("IntRepportPage_LineEdit_valueMissingQtyIO");
    m_sureToCancel          ->setObjectName("IntRepportPage_SureToCancel");

    pal.setColor(QPalette::Background, MENU_BACKGROUND_COLOR);
    m_rectangle->setAutoFillBackground(true);
    setPalette(pal);

    pal = m_titleLabel->palette();
    pal.setColor(m_titleLabel->foregroundRole(), MENU_FONT_COLOR);
    m_titleLabel            ->setPalette(pal);
    m_palletIdLabel         ->setPalette(pal);
    m_boxQtyLabel           ->setPalette(pal);
    m_boxQtyLabel           ->setPalette(pal);
    m_boxScannedQtyLabel    ->setPalette(pal);
    m_boxMissingQtyLabel    ->setPalette(pal);
    m_valueQtyLabel         ->setPalette(pal);
    m_valueScannedQtyLabel  ->setPalette(pal);
    m_valueMissingQtyLabel  ->setPalette(pal);

    font = m_titleLabel->font();
    font.setPointSize(26);
    m_titleLabel            ->setFont(font);

    font = m_palletIdLabel->font();
    font.setPointSize(16);
    m_palletIdLabel         ->setFont(font);
    m_palletIdLabel         ->setFont(font);
    m_boxQtyLabel           ->setFont(font);
    m_boxQtyLabel           ->setFont(font);
    m_boxScannedQtyLabel    ->setFont(font);
    m_boxMissingQtyLabel    ->setFont(font);
    m_valueQtyLabel         ->setFont(font);
    m_valueScannedQtyLabel  ->setFont(font);
    m_valueMissingQtyLabel  ->setFont(font);

    font = m_palletIdIO->font();
    font.setPointSize(16);
    m_palletIdIO            ->setFont(font);
    m_boxQtyIO              ->setFont(font);
    m_boxScannedQtyIO       ->setFont(font);
    m_boxMissingQtyIO       ->setFont(font);
    m_valueQtyIO            ->setFont(font);
    m_valueScannedQtyIO     ->setFont(font);
    m_valueMissingQtyIO     ->setFont(font);

    m_titleLabel            ->setMinimumHeight(60);
    m_palletIdLabel         ->setMinimumHeight(40);
    m_palletIdIO            ->setMinimumHeight(40);
    m_boxQtyLabel           ->setMinimumHeight(40);
    m_boxQtyIO              ->setMinimumHeight(40);
    m_boxScannedQtyLabel    ->setMinimumHeight(40);
    m_boxScannedQtyIO       ->setMinimumHeight(40);
    m_boxMissingQtyLabel    ->setMinimumHeight(40);
    m_boxMissingQtyIO       ->setMinimumHeight(40);
    m_valueQtyLabel         ->setMinimumHeight(40);
    m_valueQtyIO            ->setMinimumHeight(40);
    m_valueScannedQtyLabel  ->setMinimumHeight(40);
    m_valueScannedQtyIO     ->setMinimumHeight(40);
    m_valueMissingQtyLabel  ->setMinimumHeight(40);
    m_valueMissingQtyIO     ->setMinimumHeight(40);

    m_titleLabel            ->setAlignment(Qt::AlignCenter);
    m_palletIdLabel         ->setAlignment(Qt::AlignCenter);
    m_palletIdIO            ->setAlignment(Qt::AlignCenter);
    m_boxQtyLabel           ->setAlignment(Qt::AlignCenter);
    m_boxQtyIO              ->setAlignment(Qt::AlignCenter);
    m_boxScannedQtyLabel    ->setAlignment(Qt::AlignCenter);
    m_boxScannedQtyIO       ->setAlignment(Qt::AlignCenter);
    m_boxMissingQtyLabel    ->setAlignment(Qt::AlignCenter);
    m_boxMissingQtyIO       ->setAlignment(Qt::AlignCenter);
    m_valueQtyLabel         ->setAlignment(Qt::AlignCenter);
    m_valueQtyIO            ->setAlignment(Qt::AlignCenter);
    m_valueScannedQtyLabel  ->setAlignment(Qt::AlignCenter);
    m_valueScannedQtyIO     ->setAlignment(Qt::AlignCenter);
    m_valueMissingQtyLabel  ->setAlignment(Qt::AlignCenter);
    m_valueMissingQtyIO     ->setAlignment(Qt::AlignCenter);

    m_titleLabel            ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_palletIdLabel         ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_palletIdIO            ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_boxQtyLabel           ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_boxQtyIO              ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_boxScannedQtyLabel    ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_boxScannedQtyIO       ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_boxMissingQtyLabel    ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_boxMissingQtyIO       ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_valueQtyLabel         ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_valueQtyIO            ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_valueScannedQtyLabel  ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_valueScannedQtyIO     ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_valueMissingQtyLabel  ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_valueMissingQtyIO     ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    m_palletIdIO            ->setReadOnly(true);
    m_boxQtyIO              ->setReadOnly(true);
    m_boxScannedQtyIO       ->setReadOnly(true);
    m_boxMissingQtyIO       ->setReadOnly(true);
    m_valueQtyIO            ->setReadOnly(true);
    m_valueScannedQtyIO     ->setReadOnly(true);
    m_valueMissingQtyIO     ->setReadOnly(true);

    m_layoutInfo            ->addWidget(m_titleLabel            , 0, 0, 1, 5);
    m_layoutInfo            ->addWidget(m_palletIdLabel         , 1, 2, 1, 1);
    m_layoutInfo            ->addWidget(m_palletIdIO            , 2, 2, 1, 1);
    m_layoutInfo            ->addWidget(m_boxQtyLabel           , 3, 0, 1, 1);
    m_layoutInfo            ->addWidget(m_boxQtyIO              , 4, 0, 1, 1);
    m_layoutInfo            ->addWidget(m_boxScannedQtyLabel    , 3, 2, 1, 1);
    m_layoutInfo            ->addWidget(m_boxScannedQtyIO       , 4, 2, 1, 1);
    m_layoutInfo            ->addWidget(m_boxMissingQtyLabel    , 3, 4, 1, 1);
    m_layoutInfo            ->addWidget(m_boxMissingQtyIO       , 4, 4, 1, 1);
    m_layoutInfo            ->addWidget(m_valueQtyLabel         , 5, 0, 1, 1);
    m_layoutInfo            ->addWidget(m_valueQtyIO            , 6, 0, 1, 1);
    m_layoutInfo            ->addWidget(m_valueScannedQtyLabel  , 5, 2, 1, 1);
    m_layoutInfo            ->addWidget(m_valueScannedQtyIO     , 6, 2, 1, 1);
    m_layoutInfo            ->addWidget(m_valueMissingQtyLabel  , 5, 4, 1, 1);
    m_layoutInfo            ->addWidget(m_valueMissingQtyIO     , 6, 4, 1, 1);

    m_layoutInfo            ->setColumnStretch(0,28);
    m_layoutInfo            ->setColumnStretch(1,8);
    m_layoutInfo            ->setColumnStretch(2,28);
    m_layoutInfo            ->setColumnStretch(3,8);
    m_layoutInfo            ->setColumnStretch(4,28);

    m_rectangle             ->setLayout(m_layoutInfo);

    pal.setColor(m_cancelLabel->foregroundRole(), MENU_BACKGROUND_COLOR);
    m_cancelLabel           ->setPalette(pal);
    m_rescanLabel           ->setPalette(pal);
    m_continueLabel         ->setPalette(pal);

    font = m_cancelLabel->font();
    font.setPointSize(16);
    m_cancelLabel           ->setFont(font);
    m_rescanLabel           ->setFont(font);
    m_continueLabel         ->setFont(font);

    m_cancelLabel           ->setMinimumHeight(40);
    m_rescanLabel           ->setMinimumHeight(40);
    m_continueLabel         ->setMinimumHeight(40);

    m_cancelLabel           ->setAlignment(Qt::AlignCenter);
    m_rescanLabel           ->setAlignment(Qt::AlignCenter);
    m_continueLabel         ->setAlignment(Qt::AlignCenter);

    m_layoutButton          ->addWidget(m_cancelButton,     0, 0, 2, 1, Qt::AlignCenter);
    m_layoutButton          ->addWidget(m_cancelLabel,      2, 0, 1, 1, Qt::AlignCenter);
    m_layoutButton          ->addWidget(m_rescanButton,     0, 2, 2, 1, Qt::AlignCenter);
    m_layoutButton          ->addWidget(m_rescanLabel,      2, 2, 1, 1, Qt::AlignCenter);
    m_layoutButton          ->addWidget(m_continueButton,   0, 4, 2, 1, Qt::AlignCenter);
    m_layoutButton          ->addWidget(m_continueLabel,    2, 4, 1, 1, Qt::AlignCenter);

    m_layoutButton          ->setColumnStretch(0,28);
    m_layoutButton          ->setColumnStretch(1,8);
    m_layoutButton          ->setColumnStretch(2,28);
    m_layoutButton          ->setColumnStretch(3,8);
    m_layoutButton          ->setColumnStretch(4,28);

    m_layout                ->addStretch();
    m_layout                ->addWidget(m_rectangle);
    m_layout                ->addStretch();
    m_layout                ->addLayout(m_layoutButton);

    setLayout(m_layout);

    // Signal & slot connection
    QList<MenuButton *> menuButtons = this->parent()->findChildren<MenuButton *>();
    MenuButton *identifyButton;
    MenuButton *FinReportButton;
    for(int i = 0; i < menuButtons.size() ; ++i)
    {
        if (menuButtons.at(i)->objectName()=="menuButton_Identify")
        {
            identifyButton = menuButtons.at(i);
            QObject::connect(m_rescanButton,  SIGNAL(clicked()),    identifyButton,   SLOT(enable()));
            QObject::connect(m_rescanButton,  SIGNAL(clicked()),    this->parent(),   SLOT(setIdentifyPage()));
        }
        if (menuButtons.at(i)->objectName()=="menuButton_FinRepport")
        {
            FinReportButton = menuButtons.at(i);
            QObject::connect(m_continueButton,  SIGNAL(clicked()),      FinReportButton,  SLOT(enable()));
            QObject::connect(m_continueButton,  SIGNAL(clicked()),      this->parent(),   SLOT(setFinRepportPage()));
        }
    }

}

void IntRepportPage::settempvalue()
{;
}
