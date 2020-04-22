#include "deliveryinfo.h"

DeliveryInfo::DeliveryInfo(QWidget *parent)
    : QWidget(parent)
{
    QPalette pal;
    QFont font;

    // Set element name
    setObjectName("deliveryInfo");
    // Set element size policy
    setMinimumWidth(1100);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    // Set element background
    pal = palette();
    pal.setColor(QPalette::Background, MENU_BACKGROUND_COLOR);
    setAutoFillBackground(true);
    setPalette(pal);

    // Creates all children
    m_layout                = new QGridLayout(this);

    m_deliveryNameLabel     = new QLabel("Delivery Name", this);

    m_deliveryNameIO        = new QLineEdit(this);
    m_deliveryNameIO        ->setObjectName("LineEdit_deliveryName");

    m_palletIdLabel         = new QLabel("Pallet quantity", this);

    m_palletIdIO            = new QLineEdit(this);
    m_palletIdIO            ->setObjectName("LineEdit_palletQty");

    m_boxQtyLabel           = new QLabel("Box quantity", this);

    m_boxQtyIO              = new QLineEdit(this);
    m_boxQtyIO              ->setObjectName("LineEdit_boxQty");

    m_packQtyLabel          = new QLabel("Pack quantity", this);

    m_packQtyIO             = new QLineEdit(this);
    m_packQtyIO             ->setObjectName("LineEdit_packQty");

    m_deliveryDetailsLabel  = new QLabel("Delivery details", this);

    m_Table                  = new SQLView(this);
    m_Table                  ->setObjectName("TableView_Table");


    pal = m_deliveryNameLabel->palette();
    pal.setColor(m_deliveryNameLabel->foregroundRole(), MENU_FONT_COLOR);
    m_deliveryNameLabel     ->setPalette(pal);
    m_palletIdLabel         ->setPalette(pal);
    m_boxQtyLabel           ->setPalette(pal);
    m_packQtyLabel          ->setPalette(pal);
    m_deliveryDetailsLabel  ->setPalette(pal);

    font = m_deliveryNameLabel->font();
    font.setPointSize(16);
    m_deliveryNameLabel     ->setFont(font);
    m_palletIdLabel         ->setFont(font);
    m_boxQtyLabel           ->setFont(font);
    m_packQtyLabel          ->setFont(font);
    m_deliveryDetailsLabel  ->setFont(font);

    font = m_deliveryNameIO->font();
    font.setPointSize(16);
    m_deliveryNameIO        ->setFont(font);
    m_palletIdIO            ->setFont(font);
    m_boxQtyIO              ->setFont(font);
    m_packQtyIO             ->setFont(font);

    m_deliveryNameLabel     ->setFixedHeight(40);
    m_deliveryNameIO        ->setFixedHeight(40);
    m_palletIdLabel         ->setFixedHeight(40);
    m_palletIdIO            ->setFixedHeight(40);
    m_boxQtyLabel           ->setFixedHeight(40);
    m_boxQtyIO              ->setFixedHeight(40);
    m_packQtyLabel          ->setFixedHeight(40);
    m_packQtyIO             ->setFixedHeight(40);
    m_deliveryDetailsLabel  ->setFixedHeight(40);

    m_deliveryNameLabel     ->setAlignment(Qt::AlignCenter);
    m_deliveryNameIO        ->setAlignment(Qt::AlignCenter);
    m_palletIdLabel         ->setAlignment(Qt::AlignCenter);
    m_palletIdIO            ->setAlignment(Qt::AlignCenter);
    m_boxQtyLabel           ->setAlignment(Qt::AlignCenter);
    m_boxQtyIO              ->setAlignment(Qt::AlignCenter);
    m_packQtyLabel          ->setAlignment(Qt::AlignCenter);
    m_packQtyIO             ->setAlignment(Qt::AlignCenter);
    m_deliveryDetailsLabel  ->setAlignment(Qt::AlignCenter);

    m_deliveryNameLabel     ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_deliveryNameIO        ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_palletIdLabel         ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_palletIdIO            ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_boxQtyLabel           ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_boxQtyIO              ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_packQtyLabel          ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_packQtyIO             ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_deliveryDetailsLabel  ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_Table                  ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    m_deliveryNameIO        ->setReadOnly(true);
    m_palletIdIO            ->setReadOnly(true);
    m_boxQtyIO              ->setReadOnly(true);
    m_packQtyIO             ->setReadOnly(true);

    m_layout->addWidget(m_deliveryNameLabel,    0, 1, 1, 3);
    m_layout->addWidget(m_deliveryNameIO,       1, 1, 1, 3);
    m_layout->addWidget(m_palletIdLabel,        2, 0, 1, 1);
    m_layout->addWidget(m_palletIdIO,           3, 0, 1, 1);
    m_layout->addWidget(m_boxQtyLabel,          2, 2, 1, 1);
    m_layout->addWidget(m_boxQtyIO,             3, 2, 1, 1);
    m_layout->addWidget(m_packQtyLabel,         2, 4, 1, 1);
    m_layout->addWidget(m_packQtyIO,            3, 4, 1, 1);
    m_layout->addWidget(m_deliveryDetailsLabel, 5, 1, 1, 3);
    m_layout->addWidget(m_Table,                6, 0, 1, 5);

    m_layout->setColumnStretch(0,28);
    m_layout->setColumnStretch(1,8);
    m_layout->setColumnStretch(2,28);
    m_layout->setColumnStretch(3,8);
    m_layout->setColumnStretch(4,28);

    setLayout(m_layout);
}
