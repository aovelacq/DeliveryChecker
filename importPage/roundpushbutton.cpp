#include "roundpushbutton.h"

RoundPushButton::RoundPushButton(const QString &text, QWidget *parent)
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
    styleSheet = QString("RoundPushButton{ ")
                + "background-color: %1 ;"
                + "color : white;"
                + "border: none;"
                + "border-radius : 50px;"
                + "text-align: center center;"
                + "padding : -15 0 0 0;"
                + "margin-top -15 px"
                + "}"
                + "RoundPushButton:hover {"
                + "background-color: %2 ;"
                + "}"
                + "RoundPushButton:pressed {"
                + "background-color: %2 ;"
                + "color : %1;"
                + "}";
    setStyleSheet( styleSheet.arg(MENU_BACKGROUND_COLOR.name(), MENU_BACKGROUND_ACTIVE.name()) );
    // Set element font
    font = this->font();
    font.setPointSize(80);
    setFont(font);
}
