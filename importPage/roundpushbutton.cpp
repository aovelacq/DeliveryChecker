#include "roundpushbutton.h"

RoundPushButton::RoundPushButton(const QString &text, QWidget *parent = nullptr)
    : QPushButton(parent)
{
    QFont font;
    QPalette palette;
    QString styleSheet;

    // Set element text
    setText(text);
    // Set element size policy
    setContentsMargins(0,0,0,0);
    setFixedSize(100,100);
    setSizePolicy(QSizePolicy ::Fixed, QSizePolicy ::Fixed);
    // Set element name
    setObjectName("roundButton");
    // Set style of the button
    styleSheet = QString("#roundButton{ ")
                + "background-color: %1 ;"
                + "color : white;"
                + "border: none;"
                + "border-radius : 50px;"
                + "text-align: center center;"
                + "padding : -15 0 0 0;"
                + "margin-top -15 px"
                + "}"
                + "#roundButton:hover {"
                + "background-color: %2 ;"
                + "}"
                + "#roundButton:pressed {"
                + "background-color: %2 ;"
                + "color : %1;"
                + "}";
    setStyleSheet( styleSheet.arg(MENU_BACKGROUND_COLOR.name(), MENU_BACKGROUND_ACTIVE.name()) );
    // Set element font
    font = this->font();
    font.setPointSize(80);
    setFont(font);
}
