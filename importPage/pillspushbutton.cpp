#include "pillspushbutton.h"

PillsPushButton::PillsPushButton(const QString &text, QWidget *parent, const QString &objectName)
    : QPushButton(parent)
{
    QFont font;
    QPalette palette;
    QString styleSheet;

    // Set element text
    setText(text);
    // Set element size policy
    setContentsMargins(0,0,0,0);
    setFixedSize(300,80);
    setSizePolicy(QSizePolicy ::Fixed, QSizePolicy ::Fixed);
    // Set element name
    setObjectName("pillsButton_"+objectName);
    // Set style of the button
    styleSheet = QString("PillsPushButton{ ")
                + "background-color: %1 ;"
                + "color : white;"
                + "border: none;"
                + "border-radius : 40px;"
                + "text-align: center center;"
                + "padding : 0 0 0 0;"
                + "margin-top -15 px"
                + "}"
                + "PillsPushButton:hover {"
                + "background-color: %2 ;"
                + "}"
                + "PillsPushButton:pressed {"
                + "background-color: %2 ;"
                + "color : %1;"
                + "}";
    setStyleSheet( styleSheet.arg(MENU_BACKGROUND_COLOR.name(), MENU_BACKGROUND_ACTIVE.name()) );
    // Set element font
    font = this->font();
    font.setPointSize(20);
    setFont(font);
}
