#include "finrepportpage.h"

FinRepportPage::FinRepportPage(QWidget *parent)
    : QWidget(parent)
{
    QPalette pal;
    QFont font;

    m_Layout            = new QVBoxLayout(this);
    m_titleLabel        = new QLabel("FINAL REPORT", this);
    m_PalletLabel       = new QLabel("Pallets on delivery", this);
    m_PalletView        = new SQLView(this);
    m_BoxScannedLabel   = new QLabel("Box scanned", this);
    m_BoxScannedView    = new SQLView(this);
    m_BoxMissingLabel   = new QLabel("Box missing", this);
    m_BoxMissingView    = new SQLView(this);
    m_ExitLabel         = new QLabel("Exit", this);
    m_ExitButton        = new RoundPushButton(":/img/img/BackOff.png",":/img/img/BackOn.png",this);
    m_SaveLabel         = new QLabel("Save", this);
    m_SaveButton        = new RoundPushButton(":/img/img/DownloadOff.png",":/img/img/DownloadOn.png", this);
    m_Report            = new PdfReport(this);

    QVBoxLayout * m_layoutInfo      = new QVBoxLayout();
    QGridLayout * m_layoutButton    = new QGridLayout();
    QWidget     * m_rectangle       = new QWidget();

    m_Layout            ->setObjectName("FinReportPage_VBoxLayout_mainLayout");
    m_titleLabel        ->setObjectName("FinReportPage_Label_titleLabel");
    m_PalletLabel       ->setObjectName("FinReportPage_Label_palletlabel");
    m_PalletView        ->setObjectName("FinReportPage_SQLView_palletView");
    m_BoxScannedLabel   ->setObjectName("FinReportPage_Label_boxScanned");
    m_BoxScannedView    ->setObjectName("FinReportPage_SQLView_boxScanned");
    m_BoxMissingLabel   ->setObjectName("FinReportPage_Label_boxMissing");
    m_BoxMissingView    ->setObjectName("FinReportPage_SQLView_boxMissing");
    m_ExitLabel         ->setObjectName("FinReportPage_Label_exitButton");
    m_ExitButton        ->setObjectName("FinReportPage_RoundPushButton_exitButton");
    m_SaveLabel         ->setObjectName("FinReportPage_Label_saveButton");
    m_SaveButton        ->setObjectName("FinReportPage_RoundPushButton_saveButton");
    m_Report            ->setObjectName("PDFReport");

    pal.setColor(QPalette::Background, MENU_BACKGROUND_COLOR);
    m_rectangle->setAutoFillBackground(true);
    setPalette(pal);

    pal = m_titleLabel->palette();
    pal.setColor(m_titleLabel->foregroundRole(), MENU_FONT_COLOR);
    m_titleLabel        ->setPalette(pal);
    m_PalletLabel       ->setPalette(pal);
    m_BoxScannedLabel   ->setPalette(pal);
    m_BoxMissingLabel   ->setPalette(pal);

    font = m_titleLabel->font();
    font.setPointSize(26);
    m_titleLabel        ->setFont(font);

    font = m_PalletLabel->font();
    font.setPointSize(16);
    m_PalletLabel       ->setFont(font);
    m_BoxScannedLabel   ->setFont(font);
    m_BoxMissingLabel   ->setFont(font);

    m_titleLabel        ->setMinimumHeight(60);
    m_PalletLabel       ->setMinimumHeight(40);
    m_BoxScannedLabel   ->setMinimumHeight(40);
    m_BoxMissingLabel   ->setMinimumHeight(40);

    m_PalletView        ->setMinimumHeight(100);
    m_BoxScannedView    ->setMinimumHeight(100);
    m_BoxMissingView    ->setMinimumHeight(100);

    m_titleLabel        ->setAlignment(Qt::AlignCenter);
    m_PalletLabel       ->setAlignment(Qt::AlignCenter);
    m_BoxScannedLabel   ->setAlignment(Qt::AlignCenter);
    m_BoxMissingLabel   ->setAlignment(Qt::AlignCenter);

    m_titleLabel        ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_PalletLabel       ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_BoxScannedLabel   ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_BoxMissingLabel   ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_PalletView        ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    m_BoxScannedView    ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    m_BoxMissingView    ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    m_layoutInfo        ->addWidget(m_titleLabel,       Qt::AlignVCenter);
    m_layoutInfo        ->addWidget(m_PalletLabel,      Qt::AlignVCenter);
    m_layoutInfo        ->addWidget(m_PalletView,       Qt::AlignVCenter);
    m_layoutInfo        ->addWidget(m_BoxScannedLabel,  Qt::AlignVCenter);
    m_layoutInfo        ->addWidget(m_BoxScannedView,   Qt::AlignVCenter);
    m_layoutInfo        ->addWidget(m_BoxMissingLabel,  Qt::AlignVCenter);
    m_layoutInfo        ->addWidget(m_BoxMissingView,   Qt::AlignVCenter);

    m_rectangle->setLayout(m_layoutInfo);

    pal.setColor(m_ExitLabel->foregroundRole(), MENU_BACKGROUND_COLOR);
    m_ExitLabel         ->setPalette(pal);
    m_SaveLabel         ->setPalette(pal);

    font = m_ExitLabel->font();
    font.setPointSize(16);
    m_ExitLabel         ->setFont(font);
    m_SaveLabel         ->setFont(font);

    m_ExitLabel         ->setMinimumHeight(40);
    m_SaveLabel         ->setMinimumHeight(40);

    m_ExitLabel         ->setAlignment(Qt::AlignCenter);
    m_SaveLabel         ->setAlignment(Qt::AlignCenter);

    m_layoutButton      ->addWidget(m_ExitButton, 0, 0, 2, 1, Qt::AlignCenter);
    m_layoutButton      ->addWidget(m_ExitLabel,  2, 0, 1, 1, Qt::AlignCenter);
    m_layoutButton      ->addWidget(m_SaveButton,   0, 4, 2, 1, Qt::AlignCenter);
    m_layoutButton      ->addWidget(m_SaveLabel,    2, 4, 1, 1, Qt::AlignCenter);

    m_layoutButton      ->setColumnStretch(0,28);
    m_layoutButton      ->setColumnStretch(1,8);
    m_layoutButton      ->setColumnStretch(2,28);
    m_layoutButton      ->setColumnStretch(3,8);
    m_layoutButton      ->setColumnStretch(4,28);

    m_Layout            ->addStretch();
    m_Layout            ->addWidget(m_rectangle);
    m_Layout            ->addStretch();
    m_Layout            ->addLayout(m_layoutButton);

    setLayout(m_Layout);

    QObject::connect(m_ExitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
}


