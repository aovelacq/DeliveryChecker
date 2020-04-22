#include "MenuButton.h"
#include "globals/globals.h"
#include <QPainter>
#include <QFont>
#include <QDebug>
#include <QStackedWidget>

MenuButton::MenuButton(const QString &index, const QString &text, QWidget *parent, const QString &objName)
    : QPushButton(parent)
{
    QFont font;
    QPalette palette;
    QString styleSheet;
    // Set minimum size for the button
    setMinimumSize(150,150);
    setFixedHeight(this->width());
    // Set name of the button
    setObjectName("menuButton_"+objName);
    // Set style of the button
    styleSheet = "background-color: %1; border: none;";
    setStyleSheet( styleSheet.arg(MENU_BACKGROUND_COLOR.name()) );

    // Create the 2 text labels
    m_LabelIndex = new QLabel(this);
    m_LabelText = new QLabel(this);

    // Give a name for the 2 labels
    m_LabelIndex->setObjectName("menuIndex");
    m_LabelText->setObjectName("menuText");

    // Set labels text
    m_LabelIndex->setText(index);
    m_LabelText->setText(text);

    // Resize labels font
    font = m_LabelIndex->font();
    font.setPointSize(50);
    m_LabelIndex->setFont(font);
    font = m_LabelText->font();
    font.setPointSize(16);
    m_LabelText->setFont(font);

    // Set text alignement
    m_LabelIndex->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    m_LabelText->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    m_LabelIndex->setMargin(0);
    m_LabelIndex->setStyleSheet("padding: 0 0 0 0");
    m_LabelText->setMargin(0);
    m_LabelText->setStyleSheet("padding: 0 0 0 0");

    // Set size policy
    m_LabelIndex -> setSizePolicy(QSizePolicy ::Minimum, QSizePolicy ::Minimum);
    m_LabelText -> setSizePolicy(QSizePolicy ::Minimum, QSizePolicy ::Minimum);

    // Change text color
    palette = m_LabelIndex->palette();
    palette.setColor(m_LabelIndex->foregroundRole(), MENU_FONT_COLOR);
    m_LabelIndex->setPalette(palette);
    m_LabelText->setPalette(palette);

    // Set elements transparents for mouse events
    m_LabelIndex->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_LabelText->setAttribute(Qt::WA_TransparentForMouseEvents);

    // Set border to debug
    if (GRAPHICAL_DEBUG)
    {
        m_LabelIndex->setStyleSheet("border: 1px solid black");
        m_LabelText->setStyleSheet("border: 1px solid black");
    }

    // Create layout and place elements
    m_Layout = new QVBoxLayout;
    m_Layout->addWidget(m_LabelIndex, 50);
    m_Layout->addWidget(m_LabelText, 50);
    setLayout(m_Layout);

}

MenuButton::~MenuButton()
{
    delete m_LabelIndex;
    delete m_LabelText;
    delete m_Layout;
}

void MenuButton::enable()
{
    QString styleSheet = "background-color: %1; border: none;";
    QList<MenuButton *> menuButtons = this->parent()->findChildren<MenuButton *>();
    for (int i=0 ; i<menuButtons.size() ; i++)
    {
        menuButtons.at(i)->setStyleSheet( styleSheet.arg(MENU_BACKGROUND_COLOR.name()) );
    }
    setStyleSheet( styleSheet.arg(MENU_BACKGROUND_ACTIVE.name()) );
}
