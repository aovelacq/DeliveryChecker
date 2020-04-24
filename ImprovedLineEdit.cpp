#include "ImprovedLineEdit.h"

ImprovedLineEdit::ImprovedLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
}

void ImprovedLineEdit::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    emit(focussed(true));
}

void ImprovedLineEdit::focusOutEvent(QFocusEvent *e)
{
    QLineEdit::focusOutEvent(e);
    emit(focussed(false));
}
