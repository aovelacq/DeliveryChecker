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
<<<<<<< HEAD

=======
    qDebug() << "Nb of rows test : " << this->model()->rowCount();
>>>>>>> 209b8882ecd1c327fb83154dc0d8c2213183a0de
}
