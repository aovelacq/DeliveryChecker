#include "pdftableview.h"
#include <QPalette>

PDFTableView::PDFTableView(QWidget *parent)
    : QTableView(parent)
{
    QFont ft;

    ft = font();
    ft.setPointSize(18);
    setFont(ft);
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader()->setDefaultSectionSize(32);
    this->verticalHeader()->setVisible(false);
    horizontalHeader()->setFixedHeight(100);
    ft = horizontalHeader()->font();
    ft.setPointSize(22);
    horizontalHeader()->setFont(ft);

}

void PDFTableView::setResults(QSqlQueryModel *Results)
{
    this->setModel(Results);
}
