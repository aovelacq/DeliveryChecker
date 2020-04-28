#include "SureToCancel.h"

SureToCancel::SureToCancel(QWidget *parent)
    : QDialog(parent)
{
    setMinimumWidth(600);
    setMinimumHeight(400);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QFont font;
    QPalette pal;
    QString styleSheet;
    QPixmap pix;

    this->setWindowModality ( Qt::WindowModal );
    this->setWindowFlags ( windowFlags() | Qt::FramelessWindowHint  );

    m_mainLayout        = new QVBoxLayout(this);
    QVBoxLayout *m_elementLayout = new QVBoxLayout(this);

    m_warningImage      = new QLabel(this);

    QVBoxLayout *m_labelLayout = new QVBoxLayout(this);
    m_sureToCancel      = new QLabel("Are you sure to cancel ?",this);
    m_warningPalletLost = new QLabel("(Data of the current pallet will be lost)",this);

    QGridLayout *m_choiceLayout = new QGridLayout(this);
    m_cancelNoButton    = new RoundPushButton(":/img/img/BackOff.png",":/img/img/BackOn.png",this);
    m_cancelYesButton   = new RoundPushButton(":/img/img/ArrowOff.png",":/img/img/ArrowOn.png",this);
    m_cancelNoLabel     = new QLabel("No",this);
    m_cancelYesLabel    = new QLabel("Yes",this);

    QWidget * m_border  = new QWidget();

    m_warningImage      ->setObjectName("SureToCancel_QLabel_WarningImage");
    m_cancelNoButton    ->setObjectName("SureToCancel_RoundPushButton_CancelNoButton");
    m_cancelYesButton   ->setObjectName("SureToCancel_RoundPushButton_CancelYesButton");
    m_border            ->setObjectName("SureToCancel_BackGroundRect");


    //Label Design
    pal = m_sureToCancel->palette();
    pal.setColor(m_sureToCancel->foregroundRole(), MENU_BACKGROUND_COLOR);
    m_sureToCancel      ->setPalette(pal);
    m_warningPalletLost ->setPalette(pal);
    m_cancelNoLabel     ->setPalette(pal);
    m_cancelYesLabel    ->setPalette(pal);

    m_sureToCancel      ->setMinimumHeight(25);
    m_warningPalletLost ->setMinimumHeight(25);
    m_cancelNoLabel     ->setMinimumHeight(40);
    m_cancelYesLabel    ->setMinimumHeight(40);

    font = m_sureToCancel->font();
    font.setPointSize(16);
    font.setBold(true);
    m_sureToCancel      ->setFont(font);
    m_cancelNoLabel     ->setFont(font);
    m_cancelYesLabel    ->setFont(font);
    font.setPointSize(12);
    m_warningPalletLost ->setFont(font);

    //Warning Image
    m_warningImage->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    m_warningImage->setContentsMargins(0,0,0,0);

    if (pix.load(":/img/img/Warning.png"))
    {
        m_warningImage->setPixmap(pix);
    }

    //Border
    styleSheet = QString("#SureToCancel_BackGroundRect{ ")
                + "border-style: solid;"
                + "border-width: 10px;"
                + "border-color: %1;"
                + "}";
    setStyleSheet( styleSheet.arg(MENU_BACKGROUND_COLOR.name()));


    //Layout management

    m_labelLayout   ->addWidget(m_sureToCancel,     1, Qt::AlignCenter);
    m_labelLayout   ->addWidget(m_warningPalletLost,1, Qt::AlignCenter);

    m_choiceLayout  ->addWidget(m_cancelNoButton,   1, 1, Qt::AlignCenter);
    m_choiceLayout  ->addWidget(m_cancelYesButton,  1, 2, Qt::AlignCenter);
    m_choiceLayout  ->addWidget(m_cancelNoLabel,    2, 1, Qt::AlignCenter);
    m_choiceLayout  ->addWidget(m_cancelYesLabel,   2, 2, Qt::AlignCenter);

    m_elementLayout ->addStretch(1);
    m_elementLayout ->addWidget(m_warningImage,     1, Qt::AlignCenter);
    m_elementLayout ->addStretch(1);
    m_elementLayout ->addLayout(m_labelLayout);
    m_elementLayout ->addStretch(2);
    m_elementLayout ->addLayout(m_choiceLayout);
    m_elementLayout ->addStretch(1);

    m_border        ->setLayout(m_elementLayout);

    m_mainLayout    ->addWidget(m_border);
    m_mainLayout    ->setMargin(0);

}
