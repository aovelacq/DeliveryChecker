#ifndef IMPORTPAGE_H
#define IMPORTPAGE_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QMessageBox>

#include "globals/globals.h"
#include "sideMenu/MenuButton.h"
#include "roundpushbutton.h"
#include "pillspushbutton.h"
#include "deliveryinfo.h"

class DataBase;

class ImportPage : public QWidget
{
    Q_OBJECT
    public:
        ImportPage(QWidget *parent);
        void getPath();
        bool checkFilesExists();
        bool fillDatabase();


    public slots:
        bool getData();

    private:
        QVBoxLayout         *m_layout;
        RoundPushButton     *m_plusButton;
        PillsPushButton     *m_addButton;
        DeliveryInfo        *m_deliveryInfo;
        PillsPushButton     *m_checkBox;
};

#endif // IMPORTPAGE_H
