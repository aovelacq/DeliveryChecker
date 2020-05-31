#ifndef PDFREPORT_H
#define PDFREPORT_H

#include <QObject>
#include <QPdfWriter>
#include <QPainter>
#include <globals/globals.h>
#include "SQLTable/pdftableview.h"

struct DeliveryInformations{
        PDFTableView *table;
        QAbstractItemModel *model;
        QString deliveryID;
        QString palletTotal;
        QString palletScanned;
        QString palletMissing;
        QString boxTotal;
        QString boxScanned;
        QString boxMissing;
        QString valueTotal;
        QString valueScanned;
        QString valueMissing;
};

struct PalletInformations{
        PDFTableView *table;
        QAbstractItemModel *model;
        QString palletID;
        QString boxTotal;
        QString boxScanned;
        QString boxMissing;
        QString valueTotal;
        QString valueScanned;
        QString valueMissing;
};

class PdfReport : public QWidget
{
        Q_OBJECT
    public:
        explicit PdfReport(QWidget *parent = nullptr);

        void createPage(QPainter *painter);
        QRect createHeader(QPainter *painter);
        QRect createFooter(QPainter *painter);
        void createResume(QPainter *painter);
        void createDetails(QPainter *painter);
        void insertTitle(QPainter *painter);
        QPoint insertTable(QPainter *painter, PDFTableView* table, QPoint pos = QPoint(0,0), bool coloredStatus = false);

    private:
        QPdfWriter *pdfWriter;
        const int margin = 20;
        int pageNumber=1;
        QRect HeaderRect;
        QRect FooterRect;
        PDFTableView *m_Resumetable;
        DeliveryInformations deliveryInfo;
        QVector<PalletInformations> palletInfo;

    public slots:
        void createDocument();
        void getDeliveryInformations(DeliveryInformations delInfo);
        void getPalletInformation(PalletInformations palInfo);
    signals:

};

#endif // PDFREPORT_H
