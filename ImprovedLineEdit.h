#ifndef IMPROVEDLINEEDIT_H
#define IMPROVEDLINEEDIT_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>

class ImprovedLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    ImprovedLineEdit(QWidget *parent = 0);

signals:
    void focussed (bool hasFocus);

protected:
    virtual void focusInEvent(QFocusEvent *e);
    virtual void focusOutEvent(QFocusEvent *e);

};

#endif // IMPROVEDLINEEDIT_H
