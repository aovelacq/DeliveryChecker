#include "SureToContinue.h"

SureToContinue::SureToContinue(QWidget *parent)
    : QDialog(parent)
{
    setMinimumWidth(600);
    setMinimumHeight(450);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QFont font;
    QPalette pal;
    QString styleSheet;

    this->setWindowModality ( Qt::WindowModal );
    //this->setWindowFlags ( windowFlags() | Qt::FramelessWindowHint  );


    m_mainLayout        = new QVBoxLayout(this);
    QVBoxLayout *m_elementLayout = new QVBoxLayout(this);

    m_warningImage      = new RoundPushButton(":/img/img/PlusOff.png",":/img/img/PlusOn.png",this);

    QVBoxLayout *m_labelLayout = new QVBoxLayout(this);
    m_warningScan       = new QLabel("All Packs have not been scanned !",this);
    m_sureToContinue    = new QLabel("Are you sure to continue ?",this);
    m_warningOperation  = new QLabel("(This operation can not been canceled)",this);

    QGridLayout *m_choiceLayout = new QGridLayout(this);
    m_continueNoButton  = new RoundPushButton(":/img/img/PlusOff.png",":/img/img/PlusOn.png",this);
    m_continueYesButton = new RoundPushButton(":/img/img/PlusOff.png",":/img/img/PlusOn.png",this);
    m_continueNoLabel   = new QLabel("No",this);
    m_continueYesLabel  = new QLabel("Yes",this);

    QWidget * m_border  = new QWidget();

    m_continueNoButton    ->setObjectName("SureToContinue_RoundPushButton_m_continueNoButton");
    m_continueYesButton   ->setObjectName("SureToContinue_RoundPushButton_m_continueYesButton");
    m_border              ->setObjectName("SureToContinue_BackGroundRect");



    //Label Design
    pal = m_warningScan->palette();
    pal.setColor(m_warningScan->foregroundRole(), MENU_BACKGROUND_COLOR);
    m_warningScan       ->setPalette(pal);
    m_sureToContinue    ->setPalette(pal);
    m_warningOperation  ->setPalette(pal);
    m_continueNoLabel   ->setPalette(pal);
    m_continueYesLabel  ->setPalette(pal);


    m_warningScan       ->setMinimumHeight(25);
    m_sureToContinue    ->setMinimumHeight(25);
    m_warningOperation  ->setMinimumHeight(25);
    m_continueNoLabel   ->setMinimumHeight(40);
    m_continueYesLabel  ->setMinimumHeight(40);

    font = m_warningScan->font();
    font.setPointSize(16);
    font.setBold(true);
    m_warningScan       ->setFont(font);
    m_sureToContinue    ->setFont(font);
    m_continueNoLabel   ->setFont(font);
    m_continueYesLabel  ->setFont(font);

    //font = m_warningScan->font();
    font.setPointSize(12);
    m_warningOperation  ->setFont(font);

    styleSheet = QString("#SureToContinue_BackGroundRect{ ")
                + "border-style: solid;"
                + "border-width: 10px;"
                + "border-color: %1;"
                + "}";
    setStyleSheet( styleSheet.arg(MENU_BACKGROUND_COLOR.name()));


    //Layout management

    m_labelLayout   ->addWidget(m_warningScan,      1, Qt::AlignCenter);
    m_labelLayout   ->addWidget(m_sureToContinue,   1, Qt::AlignCenter);
    m_labelLayout   ->addWidget(m_warningOperation, 1, Qt::AlignCenter);

    m_choiceLayout  ->addWidget(m_continueNoButton, 1, 1, Qt::AlignCenter);
    m_choiceLayout  ->addWidget(m_continueYesButton,1, 2, Qt::AlignCenter);
    m_choiceLayout  ->addWidget(m_continueNoLabel,  2, 1, Qt::AlignCenter);
    m_choiceLayout  ->addWidget(m_continueYesLabel, 2, 2, Qt::AlignCenter);

    m_elementLayout ->addStretch(1);
    m_elementLayout ->addWidget(m_warningImage,     1, Qt::AlignCenter);
    m_elementLayout ->addStretch(1);
    m_elementLayout ->addLayout(m_labelLayout);
    m_elementLayout ->addStretch(2);
    m_elementLayout ->addLayout(m_choiceLayout);
    m_elementLayout ->addStretch(1);

    m_border          ->setLayout(m_elementLayout);

    m_mainLayout      ->addWidget(m_border);
    m_mainLayout->setMargin(0);
}
