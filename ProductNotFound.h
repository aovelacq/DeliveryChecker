#ifndef PRODUCTNOTFOUND_H
#define PRODUCTNOTFOUND_H

#endif // PRODUCTNOTFOUND_H
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

#include "importPage/roundpushbutton.h"

class ProductNotFound : public QDialog
{
public:
    ProductNotFound(QWidget *parent = nullptr);

private:
    QVBoxLayout         *m_mainLayout;
    RoundPushButton     *m_errorProductButton;
    QLabel              *m_errorProductLabel;
};
