#ifndef SURETOCONTINUE_H
#define SURETOCONTINUE_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

#include "importPage/roundpushbutton.h"
#include "sideMenu/MenuButton.h"

class SureToContinue : public QDialog
{
    Q_OBJECT
public:
    SureToContinue(QWidget *parent = nullptr);

signals:
    void sureToContinue_yes();

private slots:
    void changePage();

private:
    QVBoxLayout         *m_mainLayout;
    QLabel              *m_warningImage;
    QLabel              *m_warningScan;
    QLabel              *m_sureToContinue;
    QLabel              *m_warningOperation;
    RoundPushButton     *m_continueNoButton;
    RoundPushButton     *m_continueYesButton;
    QLabel              *m_continueNoLabel;
    QLabel              *m_continueYesLabel;
};

#endif // SURETOCONTINUE_H
