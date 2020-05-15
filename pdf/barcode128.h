#ifndef BARCODE128_H
#define BARCODE128_H

#include <QObject>
#include <QVector>

class BarCode128
{
    public:
        BarCode128();
        QString getSequence(const QString &data);
        QImage getImage(int w, int h, const QString &Data);

    private:
        QVector<QChar> CharList;
        QVector<QString>Value;
        QVector<QString>ValueEncoded;
};

#endif // BARCODE128_H
