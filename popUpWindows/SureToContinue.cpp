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
    QPixmap pix;

    this->setWindowModality ( Qt::WindowModal );
    this->setWindowFlags ( windowFlags() | Qt::FramelessWindowHint  );


    m_mainLayout        = new QVBoxLayout(this);
    QVBoxLayout *m_elementLayout = new QVBoxLayout(this);

    m_warningImage      = new QLabel(this);

    QVBoxLayout *m_labelLayout = new QVBoxLayout(this);
    m_warningScan       = new QLabel("All Packs have not been scanned !",this);
    m_sureToContinue    = new QLabel("Are you sure to continue ?",this);
    m_warningOperation  = new QLabel("(This operation can not been canceled)",this);

    QGridLayout *m_choiceLayout = new QGridLayout(this);

    m_continueNoButton  = new RoundPushButton(":/img/img/BackOff.png",":/img/img/BackOn.png",this);
    m_continueYesButton = new RoundPushButton(":/img/img/ArrowOff.png",":/img/img/ArrowOn.png",this);
    m_continueNoLabel   = new QLabel("No",this);
    m_continueYesLabel  = new QLabel("Yes",this);

    QWidget * m_border  = new QWidget();

    m_warningImage          ->setObjectName("SureToContinue_QLabel_WarningImage");
    m_continueNoButton    ->setObjectName("SureToContinue_RoundPushButton_ContinueNoButton");
    m_continueYesButton   ->setObjectName("SureToContinue_RoundPushButton_ContinueYesButton");
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
    font.setPointSize(12);
    m_warningOperation  ->setFont(font);

    //Warning Image
    m_warningImage->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    m_warningImage->setContentsMargins(0,0,0,0);

    if (pix.load(":/img/img/Warning.png"))
    {
        m_warningImage->setPixmap(pix);
    }

    //Border
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

    // Signal & slot connection;
    QList<MenuButton *> menuButtons = this->parent()->parent()->findChildren<MenuButton *>();
    MenuButton *intRepportButton;
    for(int i = 0; i < menuButtons.size() ; ++i)
    {
        if (menuButtons.at(i)->objectName()=="menuButton_IntRepport")
        {
            intRepportButton = menuButtons.at(i);

            QObject::connect(this,  SIGNAL(sureToContinue_yes()),    intRepportButton,   SLOT(enable()));
        }
    }

    QObject::connect(m_continueNoButton,    SIGNAL(clicked()),    this,   SLOT(close()));
    QObject::connect(m_continueYesButton,   SIGNAL(clicked()),    this,   SLOT(close()));
    QObject::connect(m_continueYesButton,   SIGNAL(clicked()),    this,   SLOT(changePage()));
    QObject::connect(this,  SIGNAL(sureToContinue_yes()),    this->parent()->parent(),   SLOT(setIntRepportPage()));
}

void SureToContinue::changePage()
{
    emit (sureToContinue_yes());
}
