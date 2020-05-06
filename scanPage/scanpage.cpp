#include "scanpage.h"

ScanPage::ScanPage(QWidget *parent)
    : QWidget(parent)
{
    QFont font;
    QPalette pal;
    QString styleSheet;
    QPixmap pix;

    // Set element name
    setObjectName("ScanPage");
    // Set elements size policy
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_layout                = new QGridLayout(this);
    m_layoutTextQR          = new QHBoxLayout (this);
    m_TextQR                = new QLabel("Scan the QR code on each box",this);
    m_ImageQR               = new QLabel(this);
    m_layoutTextIO          = new QHBoxLayout(this);
    m_TextIO                = new QLabel("or enter the reference manually", this);
    m_BoxRef                = new QLineEdit(this);
    m_Table                 = new SQLView(this);
    m_CancelButtonLayout    = new QVBoxLayout(this);
    m_CancelButton          = new RoundPushButton(":/img/img/BackOff.png",":/img/img/BackOn.png",this);
    m_CancelButtonText      = new QLabel("Cancel", this);
    m_ContinueButtonLayout  = new QVBoxLayout(this);
    m_ContinueButton        = new RoundPushButton(":/img/img/ArrowOff.png",":/img/img/ArrowOn.png",this);
    m_ContinueButtonText    = new QLabel("Continue", this);
    m_sureToCancel          = new SureToCancel(this);
    m_sureToContinue        = new SureToContinue(this);
    m_productNotFound       = new ProductNotFound(this);


    m_layout                ->setObjectName("ScanPage_GridLayout_mainLayout");
    m_layoutTextQR          ->setObjectName("ScanPage_HBoxLayout_TextQR");
    m_TextQR                ->setObjectName("ScanPage_Label_TextQR");
    m_ImageQR               ->setObjectName("ScanPage_Label_ImageQR");
    m_layoutTextIO          ->setObjectName("ScanPage_HBoxLayout_IOLayout");
    m_TextIO                ->setObjectName("ScanPage_Label_TextIO");
    m_BoxRef                ->setObjectName("ScanPage_LineEdit_BoxRef");
    m_Table                 ->setObjectName("ScanPage_SQLView_Table");
    m_CancelButtonLayout    ->setObjectName("ScanPage_VBoxLayout_CancelLayout");
    m_CancelButton          ->setObjectName("ScanPage_RoundPushButton_Cancel");
    m_CancelButtonText      ->setObjectName("ScanPage_Label_Cancel");
    m_ContinueButtonLayout  ->setObjectName("ScanPage_VBoxLayout_ContinueLayout");
    m_ContinueButton        ->setObjectName("ScanPage_RoundPushButton_Continue");
    m_ContinueButtonText    ->setObjectName("ScanPage_Label_Continue");
    m_sureToCancel          ->setObjectName("ScanPage_SureToCancel");
    m_sureToContinue        ->setObjectName("ScanPage_SureToContinue");
    m_productNotFound       ->setObjectName("ScanPage_ProductNotFound");

    pal                 = m_TextQR->palette();
    pal.setColor(m_TextQR->foregroundRole(), MENU_BACKGROUND_COLOR);
    m_TextQR            ->setPalette(pal);
    m_TextIO            ->setPalette(pal);
    m_CancelButtonText  ->setPalette(pal);
    m_ContinueButtonText->setPalette(pal);

    font                = m_TextQR->font();
    font.setPointSize(16);
    m_TextQR            ->setFont(font);
    m_TextIO            ->setFont(font);
    m_CancelButtonText  ->setFont(font);
    m_ContinueButtonText->setFont(font);

    font = m_BoxRef     ->font();
    font.setPointSize(16);
    m_BoxRef            ->setFont(font);

    m_TextQR            ->setMaximumHeight(40);
    m_TextIO            ->setMaximumHeight(40);
    m_BoxRef            ->setMaximumHeight(40);
    m_CancelButtonText  ->setMaximumHeight(40);
    m_ContinueButtonText->setMaximumHeight(40);

    m_ImageQR->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    m_ImageQR -> setAlignment(Qt::AlignCenter);
    m_ImageQR->setContentsMargins(0,0,0,0);

    m_CancelButtonLayout->addWidget(m_CancelButton);
    m_CancelButtonLayout->addWidget(m_CancelButtonText);

    m_ContinueButtonLayout->addWidget(m_ContinueButton);
    m_ContinueButtonLayout->addWidget(m_ContinueButtonText);

    m_CancelButtonLayout    ->setAlignment(Qt::AlignHCenter);
    m_ContinueButtonLayout  ->setAlignment(Qt::AlignHCenter);
    m_CancelButtonText->setAlignment(Qt::AlignHCenter);
    m_ContinueButtonText->setAlignment(Qt::AlignHCenter);

    m_Table -> setSelectionMode(QAbstractItemView::NoSelection);

    m_layout              ->addWidget(m_TextQR,                 0, 1, 1, 1);
    m_layout              ->addWidget(m_ImageQR,                0, 2, 2, 1);
    m_layout              ->addWidget(m_TextIO,                 1, 0, 1, 1);
    m_layout              ->addWidget(m_BoxRef,                 1, 1, 1, 1);
    m_layout              ->addWidget(m_Table,                  2, 0, 1, 3);
    m_layout              ->addLayout(m_CancelButtonLayout,     3, 0, 1, 1);
    m_layout              ->addLayout(m_ContinueButtonLayout,   3, 2, 1, 1);

    m_layout              ->setColumnStretch(0,1);
    m_layout              ->setColumnStretch(1,1);
    m_layout              ->setColumnStretch(2,1);

    m_layout              ->setRowStretch(0,2);
    m_layout              ->setRowStretch(1,1);
    m_layout              ->setRowStretch(2,6);
    m_layout              ->setRowStretch(3,1);

    setLayout(m_layout);
    m_CancelButtonLayout    ->setAlignment(Qt::AlignHCenter);
    m_ContinueButtonLayout  ->setAlignment(Qt::AlignHCenter);
    m_TextIO->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_TextQR->setAlignment(Qt::AlignHCenter);
    if (pix.load(":/img/img/label.png"))
    {
        //pix = pix.scaled(m_ImageQR->size(), Qt::KeepAspectRatio);
        m_ImageQR->setPixmap(pix);
    }

}
