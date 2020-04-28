#ifndef SURETOCANCEL_H
#define SURETOCANCEL_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

#include "importPage/roundpushbutton.h"

class SureToCancel : public QDialog
{
    Q_OBJECT
public:
    SureToCancel(QWidget *parent = nullptr);

private:
    QVBoxLayout         *m_mainLayout;
    QLabel              *m_warningImage;
    QLabel              *m_sureToCancel;
    QLabel              *m_warningPalletLost;
    RoundPushButton     *m_cancelNoButton;
    RoundPushButton     *m_cancelYesButton;
    QLabel              *m_cancelNoLabel;
    QLabel              *m_cancelYesLabel;
};

#endif // SURETOCANCEL_H
