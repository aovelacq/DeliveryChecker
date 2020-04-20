#include "infobar.h"

InfoBar::InfoBar(QWidget *parent) : QWidget(parent)
{
    QFont font;

    // Set minimum size
    setFixedHeight(40);

    // Set name
    setObjectName("infoBar");

    // Set background
    QPalette pal = palette();
    pal.setColor(QPalette::Background, MENU_BACKGROUND_COLOR);
    setAutoFillBackground(true);
    setPalette(pal);

    // Create element
    m_Copyright = new QLabel(this);

    // Give a name to element
    m_Copyright->setObjectName("copyright");

    // Set labels text
    m_Copyright->setText("© 2020 VELEC SYSTEMS | All right reserved");

    // Resize labels font
    font = m_Copyright->font();
    font.setPointSize(12);
    m_Copyright->setFont(font);

    // Set text alignement
    m_Copyright->setAlignment(Qt::AlignCenter);

    // Set size policy
    m_Copyright -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    // Change text color
    QPalette palette = m_Copyright->palette();
    palette.setColor(m_Copyright->foregroundRole(), INFO_FONT_COLOR);
    m_Copyright->setPalette(palette);

    // Set border to debug
    if (GRAPHICAL_DEBUG)
    {
        m_Copyright->setStyleSheet("border: 1px solid black");
    }

    // Create layout and place elements
    m_Layout = new QHBoxLayout;
    m_Layout->addWidget(m_Copyright, 50);
    setLayout(m_Layout);
}

InfoBar::~InfoBar()
{
    delete m_Copyright;
    delete m_Layout;
}
