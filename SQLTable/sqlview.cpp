#include "sqlview.h"
#include <QHeaderView>
#include "globals/globals.h"


SQLView::SQLView(QWidget *parent)
    : QTableView(parent)
{
    QFont ft;
    QString styleSheet;
    //setAttribute(Qt::WA_TransparentForMouseEvents);
    ft = font();
    ft.setPointSize(12);
    setFont(ft);
    setAlternatingRowColors(true);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->setFixedHeight(40);
    styleSheet = QString("QHeaderView::section { ")
                 + "background-color:%1;"
                 + "border: 2px solid white;"
                 + "}";
    horizontalHeader()->setStyleSheet(styleSheet.arg(MENU_BACKGROUND_ACTIVE.name()));
    ft = horizontalHeader()->font();
    ft.setPointSize(14);
    horizontalHeader()->setFont(ft);

    this->verticalHeader()->setVisible(false);

}

void SQLView::setResults(QSqlQueryModel *Results)
{
    this->setModel(Results);
    qDebug() << "Nb of rows :" << this->model()->rowCount();
}
