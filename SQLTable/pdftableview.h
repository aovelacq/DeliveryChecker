#ifndef PDFTABLEVIEW_H
#define PDFTABLEVIEW_H
#include <QTableView>
#include <QSqlQueryModel>
#include <QDebug>
#include <QHeaderView>
#include <QScrollBar>


class PDFTableView : public QTableView
{
        Q_OBJECT
    public:
        PDFTableView(QWidget *parent = nullptr);

    public slots:
        void setResults(QSqlQueryModel *Results);
};

#endif // PDFTABLEVIEW_H
