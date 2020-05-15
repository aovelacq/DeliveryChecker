#ifndef PDFREPORT_H
#define PDFREPORT_H

#include <QObject>
#include <QPdfWriter>
#include <QPainter>
#include <globals/globals.h>
#include "SQLTable/pdftableview.h"

class PdfReport : public QWidget
{
        Q_OBJECT
    public:
        explicit PdfReport(QWidget *parent = nullptr);

        void createPage(QPainter *painter);
        QRect createHeader(QPainter *painter);
        QRect createFooter(QPainter *painter);
        void createResume(QPainter *painter);
        void insertTitle(QPainter *painter);
        QPoint insertTable(QPainter *painter, PDFTableView* table, QPoint pos = QPoint(0,0), bool coloredStatus = false);

    private:
        QPdfWriter *pdfWriter;
        const int margin = 20;
        int pageNumber=0;
        QRect HeaderRect;
        QRect FooterRect;
        PDFTableView *table;

    public slots:
        void createDocument();
    signals:

};

#endif // PDFREPORT_H
