#include "barcode128.h"
#include <QImage>
#include <QDebug>
BarCode128::BarCode128()
{
    //Definition
    {
    CharList.append('0');
    CharList.append('1');
    CharList.append('2');
    CharList.append('3');
    CharList.append('4');
    CharList.append('5');
    CharList.append('6');
    CharList.append('7');
    CharList.append('8');
    CharList.append('9');
    CharList.append('-');
    CharList.append('S');

    Value.append("00001");
    Value.append("10001");
    Value.append("01001");
    Value.append("11000");
    Value.append("00101");
    Value.append("10100");
    Value.append("01100");
    Value.append("00011");
    Value.append("10010");
    Value.append("10000");
    Value.append("00100");
    Value.append("00110");

    ValueEncoded.append("101011");
    ValueEncoded.append("1101011");
    ValueEncoded.append("1001011");
    ValueEncoded.append("1100101");
    ValueEncoded.append("1011011");
    ValueEncoded.append("1101101");
    ValueEncoded.append("1001101");
    ValueEncoded.append("1010011");
    ValueEncoded.append("1101001");
    ValueEncoded.append("110101");
    ValueEncoded.append("101101");
    ValueEncoded.append("1011001");}


}

QString BarCode128::getSequence(const QString &data)
{
    QString Result;
    QString KString(data);
    int pos;

    int C=0;
    for (int i=0;i<data.size();++i)
    {
        if (data.at(i).isDigit())
            C+=data.at(i).digitValue()*(data.size()-i);
        else
            C+=10*(data.size()-i);
    }
    C%=11;

    if (C==10) KString.append('-');
    else KString.append(QString("%1").arg(C));

    int K=0;
    for (int i=0;i<KString.size();++i)
    {
        if (KString.at(i).isDigit())
            K+=KString.at(i).digitValue()*(KString.size()-i);
        else
            K+=10*(KString.size()-i);
    }
    K%=11;

    Result += ValueEncoded.last();
    Result += "0";
    for (int i=0;i<data.size();++i)
    {
        pos = CharList.indexOf(data.at(i));
        if (pos==-1) return "";
        Result += ValueEncoded.at(pos);
        Result += "0";
    }
//    Result += ValueEncoded.at(C);
//    Result += "0";
//    Result += ValueEncoded.at(K);
//    Result += "0";
    Result += ValueEncoded.last();


    return Result;
}

QImage BarCode128::getImage(int w, int h, const QString &Data)
{
    const QString sequence = getSequence(Data);
    const int ratioWidth = w/sequence.size();
    QImage image(ratioWidth*sequence.size(), h, QImage::Format_ARGB32);
    QRgb value;

    for (int lig=1; lig<h; lig++)
    {
        for (int col=1;col<ratioWidth*sequence.size();col++)
        {

            if(sequence.at((col-1)/ratioWidth)=='1')
                value = qRgba(0,0,0,255);
            else if ((sequence.at((col-1)/ratioWidth)=='0'))
                value = qRgba(0,0,0,0);
            image.setPixel(col, lig, value);
        }
    }

    return image;
}
