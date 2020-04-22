#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "dynamicfontsizelabel.h"

class MenuButton : public QPushButton
{
    Q_OBJECT

    public:
        MenuButton(const QString &index = "", const QString &text = "", QWidget *parent = nullptr, const QString &objName = "");
        ~MenuButton();

    public slots:
        void enable();

    protected:

    private:
        QLabel      *m_LabelIndex;          // Number of the button
        QLabel      *m_LabelText;           // Text of the button
        QVBoxLayout *m_Layout;              // Layout inside the button

    signals:

};

#endif // MENUBUTTON_H
