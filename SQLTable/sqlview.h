#ifndef SQLVIEW_H
#define SQLVIEW_H
#include <QTableView>
#include <QSqlQueryModel>
#include <QDebug>


class SQLView : public QTableView
{
        Q_OBJECT
    public:
        SQLView(QWidget *parent = nullptr);

    public slots:
        void setResults(QSqlQueryModel *Results);
};

#endif // SQLVIEW_H
