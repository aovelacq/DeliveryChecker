#ifndef DELIVERYINFO_H
#define DELIVERYINFO_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

#include "globals/globals.h"
#include "SQLTable/sqlview.h"

class DeliveryInfo : public QWidget
{
    Q_OBJECT
public:
    explicit DeliveryInfo(QWidget *parent = nullptr);

private:
    QGridLayout     *m_layout;
    QLabel          *m_deliveryNameLabel;
    QLineEdit       *m_deliveryNameIO;
    QLabel          *m_palletIdLabel;
    QLineEdit       *m_palletIdIO;
    QLabel          *m_boxQtyLabel;
    QLineEdit       *m_boxQtyIO;
    QLabel          *m_packQtyLabel;
    QLineEdit       *m_packQtyIO;
    QLabel          *m_deliveryDetailsLabel;
    SQLView         *m_Table;

signals:

};

#endif // DELIVERYINFO_H
