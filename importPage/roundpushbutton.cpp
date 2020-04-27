#include "roundpushbutton.h"

RoundPushButton::RoundPushButton(const QString &imgURLOff, const QString &imgURLOn, QWidget *parent)
    : QPushButton(parent)
{
    QFont font;
    QPalette palette;
    QString styleSheet;

    // Set element size policy
    setContentsMargins(0,0,0,0);
    setFixedSize(100,100);
    setSizePolicy(QSizePolicy ::Fixed, QSizePolicy ::Fixed);
    // Set element name
    setObjectName("roundButton");
    // Set style of the button
    styleSheet = QString("RoundPushButton{ ")
                + "background-color: %1 ;"
                + "background-image: url(%3);"
                + "background-position: center;"
                + "border: none;"
                + "border-radius : 50px;"
                + "}"
                + "RoundPushButton:hover {"
                + "background-color: %2 ;"
                + "}"
                + "RoundPushButton:pressed {"
                + "background-color: %2 ;"
                + "background-image: url(%4);"
                + "background-position: center;"
                + "}";
    setStyleSheet( styleSheet.arg(MENU_BACKGROUND_COLOR.name(), MENU_BACKGROUND_ACTIVE.name(),imgURLOff,imgURLOn));

}
