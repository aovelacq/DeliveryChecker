#include "ProductNotFound.h"

ProductNotFound::ProductNotFound(QWidget *parent)
    : QDialog(parent)
{
    setMinimumWidth(500);
    setMinimumHeight(300);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QFont font;
    QPalette pal;
    QString styleSheet;

    this->setWindowModality ( Qt::WindowModal );
    this->setWindowFlags ( windowFlags() | Qt::FramelessWindowHint  );


    m_mainLayout         = new QVBoxLayout(this);
    QVBoxLayout *m_elementLayout = new QVBoxLayout(this);
    m_errorProductButton = new RoundPushButton(":/img/img/BackOff.png",":/img/img/BackOn.png",this);
    m_errorProductLabel  = new QLabel("Product not found !",this);
    QWidget * m_border = new QWidget();

    m_errorProductButton    ->setObjectName("ProductNotFound_RoundPushButton_errorProductButton");
    m_errorProductLabel     ->setObjectName("ProductNotFound_Label_errorProductLabel");
    m_border                ->setObjectName("BackGroundRect");

    //Label Design
    pal = m_errorProductLabel->palette();
    pal.setColor(m_errorProductLabel->foregroundRole(), MENU_BACKGROUND_COLOR);
    m_errorProductLabel        ->setPalette(pal);

    m_errorProductLabel       ->setMinimumHeight(40);

    font = m_errorProductLabel->font();
    font.setPointSize(16);
    font.setBold(true);
    m_errorProductLabel->setFont(font);

    styleSheet = QString("#BackGroundRect{ ")
                + "border-style: solid;"
                + "border-width: 10px;"
                + "border-color: %1;"
                + "}";
    setStyleSheet( styleSheet.arg(MENU_BACKGROUND_COLOR.name()));


    //Layout management

    m_elementLayout   ->addStretch(1);
    m_elementLayout   ->addWidget(m_errorProductButton);
    m_elementLayout   ->addWidget(m_errorProductLabel);
    m_elementLayout   ->addStretch(1);

    m_elementLayout   ->setAlignment(m_errorProductLabel,Qt::AlignCenter);
    m_elementLayout   ->setAlignment(m_errorProductButton,Qt::AlignCenter);

    m_border          ->setLayout(m_elementLayout);

    m_mainLayout      ->addWidget(m_border);
    m_mainLayout->setMargin(0);

    QObject::connect(m_errorProductButton, SIGNAL(clicked()), this, SLOT(close()));
}
