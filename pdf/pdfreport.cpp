#include "pdfreport.h"
#include <QDebug>
#include <QApplication>
#include <QFile>
#include <QDateTime>
#include <QHeaderView>
#include "barcode128.h"
#include <QDesktopServices>
#include <QUrl>

unsigned int mmToPixel(double mm)
{
    return static_cast<unsigned int>(mm*3.7795275591);
}

PdfReport::PdfReport(QWidget *parent) : QWidget(parent)
{
    m_Resumetable = new PDFTableView(this);
    //m_PalletTable = new QVector<PDFTableView>;

    m_Resumetable->setObjectName("tabletemp");
    m_Resumetable->hide();
}

void PdfReport::createDocument()
{
    QFile::remove("C:\\Users\\axelo\\VELEC\\PROJETS\\Peruri\\DataBase\\Data\\test.pdf");
    pdfWriter = new QPdfWriter(QString("C:\\Users\\axelo\\VELEC\\PROJETS\\Peruri\\DataBase\\Data\\test.pdf"));
    pdfWriter->setPageSize(QPageSize(QPageSize::A4));
    pdfWriter->setResolution(300);
    QMarginsF docMargins(margin,margin,margin,margin);
    pdfWriter->setPageMargins(docMargins,QPageLayout::Millimeter);
    pdfWriter->setPageOrientation(QPageLayout::Portrait);
    QPainter painter(pdfWriter);
    painter.setBackgroundMode(Qt::TransparentMode);

    pageNumber = 1;
    createResume(&painter);
    createDetails(&painter);
    palletInfo.clear();
    QDesktopServices::openUrl(QUrl::fromLocalFile("C:\\Users\\axelo\\VELEC\\PROJETS\\Peruri\\DataBase\\Data\\test.pdf"));
}

void PdfReport::createResume(QPainter *painter)
{
    const uint interline = 20;
    int textWidth;
    QRect footerRect;
    QRect space;

    createPage(painter);
    insertTitle(painter);
    QPoint pos = insertTable(painter, deliveryInfo.table, QPoint(0,0),true);
    painter->translate(pos);

    QFont font;
    font.setPointSize(10);
    painter->setFont(font);

    const int textHeight=painter->fontMetrics().height();

    // Pallet Informations
    footerRect = QRect(FooterRect.x()-painter->worldMatrix().dx(),FooterRect.y()-painter->worldMatrix().dy(),FooterRect.width(), FooterRect.height());
    QRect palletInfo(0,0,pdfWriter->width(),3*(textHeight+interline));
    if (palletInfo.intersects(footerRect))
    {
        pdfWriter->newPage();
        createPage(painter);
    }

    const QString palletTotal = QString("Quantity of pallet on delivery :");
    textWidth=painter->fontMetrics().horizontalAdvance(palletTotal);
    const QRect palletTotalRect(0,0, textWidth,textHeight);
    painter->drawText(palletTotalRect,Qt::AlignVCenter | Qt::AlignLeft, palletTotal);

    const QString valPalletTotal = deliveryInfo.palletTotal;
    textWidth=painter->fontMetrics().horizontalAdvance(valPalletTotal);
    const QRect valPalletTotalRect(palletTotalRect.right()+20,palletTotalRect.top(), textWidth,textHeight);
    painter->drawText(valPalletTotalRect,Qt::AlignVCenter | Qt::AlignLeft, valPalletTotal);

    const QString palletScanned = QString("Quantity of pallet scanned :");
    textWidth=painter->fontMetrics().horizontalAdvance(palletScanned);
    const QRect palletScannedlRect(0,palletTotalRect.bottom()+interline, textWidth,textHeight);
    painter->drawText(palletScannedlRect,Qt::AlignVCenter | Qt::AlignLeft, palletScanned);

    const QString valPalletScanned = deliveryInfo.palletScanned;
    textWidth=painter->fontMetrics().horizontalAdvance(valPalletScanned);
    const QRect valPalletScannedlRect(valPalletTotalRect.x(),palletScannedlRect.y(), textWidth,textHeight);
    painter->drawText(valPalletScannedlRect,Qt::AlignVCenter | Qt::AlignLeft, valPalletScanned);

    const QString palletMissing = QString("Quantity of pallet missing :");
    textWidth=painter->fontMetrics().horizontalAdvance(palletMissing);
    const QRect palletMissingRect(0,palletScannedlRect.bottom()+interline, textWidth,textHeight);
    painter->drawText(palletMissingRect,Qt::AlignVCenter | Qt::AlignLeft, palletMissing);

    const QString valPalletMissing = deliveryInfo.palletMissing;
    textWidth=painter->fontMetrics().horizontalAdvance(valPalletMissing);
    const QRect valPalletMissingRect(valPalletTotalRect.x(),palletMissingRect.y(), textWidth,textHeight);
    painter->drawText(valPalletMissingRect,Qt::AlignVCenter | Qt::AlignLeft, valPalletMissing);

    painter->translate(QPoint(0,palletMissingRect.bottom()+interline));

    // Box informations
    footerRect = QRect(FooterRect.x()-painter->worldMatrix().dx(),FooterRect.y()-painter->worldMatrix().dy(),FooterRect.width(), FooterRect.height());
    space = QRect(0,0,pdfWriter->width(),30);
    if (!space.intersects(footerRect))
    {
        painter->translate(QPoint(0,space.height()));
    }
    QRect boxInfo(0,0,pdfWriter->width(),3*(textHeight+interline));
    if (boxInfo.intersects(footerRect))
    {
        pdfWriter->newPage();
        createPage(painter);
    }

    const QString boxTotal = QString("Quantity of box on delivery :");
    textWidth=painter->fontMetrics().horizontalAdvance(boxTotal);
    const QRect boxTotalRect(0,0, textWidth,textHeight);
    painter->drawText(boxTotalRect,Qt::AlignVCenter | Qt::AlignLeft, boxTotal);

    const QString valBoxTotal = deliveryInfo.boxTotal;
    textWidth=painter->fontMetrics().horizontalAdvance(valBoxTotal);
    const QRect valBoxTotalRect(valPalletTotalRect.x(),boxTotalRect.y(), textWidth,textHeight);
    painter->drawText(valBoxTotalRect,Qt::AlignVCenter | Qt::AlignLeft, valBoxTotal);

    const QString boxScanned = QString("Quantity of box scanned :");
    textWidth=painter->fontMetrics().horizontalAdvance(boxScanned);
    const QRect boxScannedlRect(0,boxTotalRect.bottom()+interline, textWidth,textHeight);
    painter->drawText(boxScannedlRect,Qt::AlignVCenter | Qt::AlignLeft, boxScanned);

    const QString valBoxScanned = deliveryInfo.boxScanned;
    textWidth=painter->fontMetrics().horizontalAdvance(valBoxScanned);
    const QRect valBoxScannedRect(valPalletTotalRect.x(),boxScannedlRect.y(), textWidth,textHeight);
    painter->drawText(valBoxScannedRect,Qt::AlignVCenter | Qt::AlignLeft, valBoxScanned);

    const QString boxMissing = QString("Quantity of box missing :");
    textWidth=painter->fontMetrics().horizontalAdvance(boxMissing);
    const QRect boxMissingRect(0,boxScannedlRect.bottom()+interline, textWidth,textHeight);
    painter->drawText(boxMissingRect,Qt::AlignVCenter | Qt::AlignLeft, boxMissing);

    const QString valBoxMissing = deliveryInfo.boxMissing;
    textWidth=painter->fontMetrics().horizontalAdvance(valBoxMissing);
    const QRect valBoxMissingRect(valPalletTotalRect.x(),boxMissingRect.y(), textWidth,textHeight);
    painter->drawText(valBoxMissingRect,Qt::AlignVCenter | Qt::AlignLeft, valBoxMissing);

    painter->translate(QPoint(0,boxMissingRect.bottom()+interline));

    // Value informations
    footerRect = QRect(FooterRect.x()-painter->worldMatrix().dx(),FooterRect.y()-painter->worldMatrix().dy(),FooterRect.width(), FooterRect.height());
    space = QRect(0,0,pdfWriter->width(),30);
    if (!space.intersects(footerRect))
    {
        painter->translate(QPoint(0,space.height()));
    }
    QRect valueInfo(0,0,pdfWriter->width(),3*(textHeight+interline));
    if (valueInfo.intersects(footerRect))
    {
        pdfWriter->newPage();
        createPage(painter);
    }

    const QString valueTotal = QString("Total value on delivery :");
    textWidth=painter->fontMetrics().horizontalAdvance(valueTotal);
    const QRect valueTotalRect(0,0, textWidth,textHeight);
    painter->drawText(valueTotalRect,Qt::AlignVCenter | Qt::AlignLeft, valueTotal);

    const QString valValueTotal = deliveryInfo.valueTotal;
    textWidth=painter->fontMetrics().horizontalAdvance(valValueTotal);
    const QRect valValueTotalRect(valPalletTotalRect.x(),valueTotalRect.y(), textWidth,textHeight);
    painter->drawText(valValueTotalRect,Qt::AlignVCenter | Qt::AlignLeft, valValueTotal);

    const QString valueScanned = QString("Total value scanned :");
    textWidth=painter->fontMetrics().horizontalAdvance(valueScanned);
    const QRect valueScannedRect(0,valueTotalRect.bottom()+interline, textWidth,textHeight);
    painter->drawText(valueScannedRect,Qt::AlignVCenter | Qt::AlignLeft, valueScanned);

    const QString valValueScanned = deliveryInfo.valueScanned;
    textWidth=painter->fontMetrics().horizontalAdvance(valValueScanned);
    const QRect valValueScannedRect(valPalletTotalRect.x(),valueScannedRect.y(), textWidth,textHeight);
    painter->drawText(valValueScannedRect,Qt::AlignVCenter | Qt::AlignLeft, valValueScanned);

    const QString valueMissing = QString("Total value missing :");
    textWidth=painter->fontMetrics().horizontalAdvance(valueMissing);
    const QRect valueMissingRect(0,valueScannedRect.bottom()+interline, textWidth,textHeight);
    painter->drawText(valueMissingRect,Qt::AlignVCenter | Qt::AlignLeft, valueMissing);

    const QString valValueMissing = deliveryInfo.valueMissing;
    textWidth=painter->fontMetrics().horizontalAdvance(valValueMissing);
    const QRect valValueMissingRect(valPalletTotalRect.x(),valueMissingRect.y(), textWidth,textHeight);
    painter->drawText(valValueMissingRect,Qt::AlignVCenter | Qt::AlignLeft, valValueMissing);

    painter->translate(QPoint(0,valueMissingRect.bottom()+interline));

    QPen pen;
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawLine(0, 0, pdfWriter->width(), 0);

}

void PdfReport::createPage(QPainter *painter)
{
    painter->resetMatrix();
    painter->save();
    HeaderRect = createHeader(painter);
    FooterRect = createFooter(painter);
    painter->restore();
    pageNumber++;
    painter->translate(QPoint(0,HeaderRect.height()+50));
}

QRect PdfReport::createHeader(QPainter *painter)
{
    const uint interline = 15;
    int textWidth;
    QPoint startLinePoint,endLinePoint;

    QFont font;
    font.setPointSize(7);
    painter->setFont(font);

    QPen pen;
    pen.setWidth(3);
    painter->setPen(pen);

    QFontMetrics fm(painter->font());
    const int textHeight=fm.height();

    const QPixmap Logo(":/img/img/logopdf.png");
    const QRect logoRect(0,0,Logo.width(),Logo.height());
    painter->drawPixmap(logoRect,Logo);

    const QString date = QString("Generated on : %1 at %2").arg(QDate::currentDate().toString("dddd dd MMMM yyyy"), QTime::currentTime().toString("hh:mm:ss AP"));
    textWidth=fm.horizontalAdvance(date);
    const QRect dateRect(pdfWriter->width()-textWidth,logoRect.bottom()-textHeight,textWidth,textHeight);
    painter->drawText(dateRect,Qt::AlignBottom | Qt::AlignRight, date);

    startLinePoint = QPoint(0,logoRect.bottom()+interline);
    endLinePoint = QPoint(pdfWriter->width(),logoRect.bottom()+interline);
    painter->drawLine(startLinePoint,endLinePoint);

    const QString idx = QString::number(static_cast<uint>(static_cast<double>(QTime::currentTime().msecsSinceStartOfDay())/864.0)).rightJustified(6,'0');
    const QString ref = QString("Report reference : %1-%2-%3").arg(QDate::currentDate().toString("yyyyMMdd"),deliveryInfo.deliveryID,idx);
    textWidth=fm.horizontalAdvance(ref);
    const QRect refRect(0,startLinePoint.y()+pen.width()+interline,textWidth,textHeight);
    painter->drawText(refRect,Qt::AlignVCenter | Qt::AlignLeft,ref);

    const QString user = QString("Edited by : %1/%2").arg(QSysInfo::machineHostName(),getenv("USERNAME"));
    textWidth=fm.horizontalAdvance(ref);
    const QRect userRect(0,refRect.bottom()+interline,textWidth,textHeight);
    painter->drawText(userRect,Qt::AlignVCenter | Qt::AlignLeft,user);

    const QString soft = QString("Generated by : %1 %2").arg(QCoreApplication::applicationName(), QCoreApplication::applicationVersion());
    textWidth=fm.horizontalAdvance(soft);
    const QRect softRect(0,userRect.bottom()+interline,textWidth,textHeight);
    painter->drawText(softRect,Qt::AlignVCenter | Qt::AlignLeft,soft);

    startLinePoint = QPoint(0,softRect.bottom()+interline);
    endLinePoint = QPoint(pdfWriter->width(),softRect.bottom()+interline);
    painter->drawLine(startLinePoint,endLinePoint);

    BarCode128 barcode;
    QImage image = barcode.getImage(pdfWriter->width()-logoRect.width()-200,125,QString("%1-%2-%3").arg(QDate::currentDate().toString("yyyyMMdd"),"99",idx));
    painter->drawImage(pdfWriter->width()-image.width(),logoRect.top()+50,image);

    return QRect(0,0,pdfWriter->width(),startLinePoint.y()+interline);
}

QRect PdfReport::createFooter(QPainter *painter)
{
    const uint interline = 15;
    QPoint startLinePoint,endLinePoint;

    QPen pen;
    pen.setWidth(3);
    painter->setPen(pen);

    QFont font;
    font.setPointSize(7);
    painter->setFont(font);

    QFontMetrics fm(painter->font());
    const int textHeight=fm.height();

    startLinePoint = QPoint(0,pdfWriter->height()-textHeight/2);
    endLinePoint = QPoint(pdfWriter->width()/2-100,pdfWriter->height()-textHeight/2);
    painter->drawLine(startLinePoint,endLinePoint);

    const QRect pageRect(pdfWriter->width()/2-100,pdfWriter->height()-textHeight,200,textHeight);
    painter->drawText(pageRect,Qt::AlignCenter,QString("%1").arg(pageNumber));

    startLinePoint = QPoint(pdfWriter->width()/2+100,pdfWriter->height()-textHeight/2);
    endLinePoint = QPoint(pdfWriter->width(),pdfWriter->height()-textHeight/2);
    painter->drawLine(startLinePoint,endLinePoint);

    return QRect(0,pdfWriter->height()-textHeight-interline,pdfWriter->width(),textHeight+interline);

}

void PdfReport::insertTitle(QPainter *painter)
{
    QFont font;
    font.setPointSize(20);
    font.setCapitalization(QFont::SmallCaps);
    painter->setFont(font);

    QFontMetrics fm(painter->font());
    const int textHeight=fm.height();

    const QString title = "DELIVERY REPORT";
    const QRect titleRect(0,0,pdfWriter->width(),textHeight);
    painter->drawText(titleRect,Qt::AlignCenter, title);
    painter->translate(0,titleRect.height()+50);
}

QPoint PdfReport::insertTable(QPainter *painter, PDFTableView* table, QPoint pos, bool coloredStatus)
{
    QPen pen;
    pen.setWidth(1);
    painter->setPen(pen);

    painter->translate(pos);
    QPoint ActPos(0,0);
    int nbLine = table->model()->rowCount();
    int nbColumn = table->model()->columnCount();
    int cellwidth = pdfWriter->width()/nbColumn;
    int headerHeight = table->horizontalHeader()->height();
    int rowHeight = table->rowHeight(1);
    QRect cell;
    QFont font;
    QRect footerRect;
    QBrush brush(painter->brush());
    int idxLine =0,idxCol=0;

    // Draw Header
    {
    // Set header font
    font.setPointSize(10);
    font.setCapitalization(QFont::MixedCase);
    painter->setFont(font);
    brush.setColor(Qt::white);
    painter->setBrush(brush);
    // Check if it intersects the footer and create a new page if necessary (must display 1 row min)
    footerRect = QRect(FooterRect.x()-painter->worldMatrix().dx(),FooterRect.y()-painter->worldMatrix().dy(),FooterRect.width(), FooterRect.height());
    if (QRect(0,0,cellwidth,headerHeight+rowHeight).intersects(footerRect))
    {
        pdfWriter->newPage();
        ActPos=QPoint(0,0);
        createPage(painter);
    }
    //Draw each cell and fill it with header data
    for(int col=0;col<nbColumn;col++)
    {
        cell = QRect(col*cellwidth+ActPos.x(),ActPos.y(),cellwidth,headerHeight);
        painter->drawRect(cell);
        painter->drawText(cell, Qt::AlignCenter, table->model()->headerData(col,Qt::Horizontal).toString());
    }
    //Set the new vertical position
    ActPos.setY(ActPos.y()+headerHeight);
    }

    //Draw table
    {
    // Set table font
    font.setPointSize(6);
    font.setCapitalization(QFont::MixedCase);
    painter->setFont(font);
    painter->setBrush(QBrush(Qt::transparent));
    // Loop for each model data
    for(int line=0;line<nbLine;line++)
    {
        idxCol=0;
        for(int col=0;col<nbColumn;col++)
        {

            //Check if the row interseacts the footer and create a new page if necessary
            footerRect = QRect(FooterRect.x()-painter->worldMatrix().dx(),FooterRect.y()-painter->worldMatrix().dy(),FooterRect.width(), FooterRect.height());
            cell = QRect(idxCol*cellwidth+ActPos.x(),idxLine*rowHeight+ActPos.y(),cellwidth,rowHeight);
            if (cell.intersects(footerRect))
            {
                pdfWriter->newPage();
                ActPos=QPoint(0,0);
                createPage(painter);
                // Set header again
                font.setPointSize(10);
                font.setCapitalization(QFont::MixedCase);
                painter->setFont(font);
                for(int col=0;col<nbColumn;col++)
                {
                    cell = QRect(col*cellwidth+ActPos.x(),ActPos.y(),cellwidth,headerHeight);
                    painter->drawRect(cell);
                    painter->drawText(cell, Qt::AlignCenter, table->model()->headerData(col,Qt::Horizontal).toString());
                }
                idxLine = 0;
                ActPos.setY(ActPos.y()+headerHeight);
                // Actual cell calculation
                cell = QRect(idxCol*cellwidth+ActPos.x(),idxLine*rowHeight+ActPos.y(),cellwidth,rowHeight);
                // Set table font
                font.setPointSize(6);
                font.setCapitalization(QFont::MixedCase);
                painter->setFont(font);
            }
            //Draw cell and fill it with header data
            if (idxCol==0 && coloredStatus)
            {
                painter->drawRect(cell);
                if (table->model()->index(line,col).data().toString() == "OK")
                    painter->setBrush(QBrush(Qt::green));
                else if (table->model()->index(line,col).data().toString() == "")
                    painter->setBrush(QBrush(Qt::red));
                painter->fillRect(QRect(cell.x()+4,cell.y()+4,cell.height()-8,cell.height()-8),painter->brush());
                painter->drawRect(QRect(cell.x()+4,cell.y()+4,cell.height()-8,cell.height()-8));
                painter->drawText(QRect(cell.x()+cell.height()+10,cell.y()+4,cell.width()-(cell.x()+cell.height()+4),cell.height()-8), Qt::AlignLeft | Qt::AlignVCenter, table->model()->index(line,col).data().toString()=="OK"?"Scanned":"Not Scanned");
            }
            else
            {
                painter->setBrush(QBrush(Qt::transparent));
                painter->drawRect(cell);
                painter->drawText(cell, Qt::AlignCenter, table->model()->index(line,col).data().toString());
            }
            idxCol++;
        }
        idxLine++;
    }
    }
    ActPos.setY(ActPos.y()+idxLine*rowHeight+50);
    return ActPos;

}

void PdfReport::createDetails(QPainter *painter)
{
    for (int index = 0 ; index<palletInfo.count(); index++)
    {
        pdfWriter->newPage();
        createPage(painter);

        QRect footerRect;
        QRect space;
        int textWidth;
        const uint interline = 20;
        QFont font;
        font.setPointSize(16);
        font.setCapitalization(QFont::MixedCase);
        font.setWeight(QFont::DemiBold);
        painter->setFont(font);

        QPen pen;
        pen.setWidth(6);
        painter->setPen(pen);

        int textHeight=painter->fontMetrics().height();

        const QString palletRef = QString("Pallet ID : %1").arg(palletInfo.at(index).palletID);
        textWidth=painter->fontMetrics().horizontalAdvance(palletRef);
        const QRect palletRefRect(0,0,textWidth,textHeight);
        painter->drawText(palletRefRect,Qt::AlignVCenter | Qt::AlignLeft, palletRef);
        painter->drawLine(palletRefRect.bottomLeft(), palletRefRect.bottomRight());
        painter->translate(0,palletRefRect.bottom()+20);

        QPoint pos = insertTable(painter, palletInfo.at(index).table, QPoint(0,0),true);
        painter->translate(pos);

        font.setPointSize(10);
        font.setWeight(QFont::Thin);
        painter->setFont(font);
        textHeight=painter->fontMetrics().height();

        footerRect = QRect(FooterRect.x()-painter->worldMatrix().dx(),FooterRect.y()-painter->worldMatrix().dy(),FooterRect.width(), FooterRect.height());
        space = QRect(0,0,pdfWriter->width(),30);
        if (!space.intersects(footerRect))
        {
            painter->translate(QPoint(0,space.height()));
        }
        QRect boxInfo(0,0,pdfWriter->width(),3*(textHeight+interline));
        if (boxInfo.intersects(footerRect))
        {
            pdfWriter->newPage();
            createPage(painter);
        }

        const QString boxTotal = QString("Quantity of box total :");
        textWidth=painter->fontMetrics().horizontalAdvance(boxTotal);
        const QRect boxTotalRect(0,0, textWidth,textHeight);
        painter->drawText(boxTotalRect,Qt::AlignVCenter | Qt::AlignLeft, boxTotal);

        const QString valBoxTotal = palletInfo.at(index).boxTotal;
        textWidth=painter->fontMetrics().horizontalAdvance(valBoxTotal);
        const QRect valBoxTotalRect(boxTotalRect.right()+80,boxTotalRect.y(), textWidth,textHeight);
        painter->drawText(valBoxTotalRect,Qt::AlignVCenter | Qt::AlignLeft, valBoxTotal);

        const QString boxScanned = QString("Quantity of box scanned :");
        textWidth=painter->fontMetrics().horizontalAdvance(boxScanned);
        const QRect boxScannedlRect(0,boxTotalRect.bottom()+interline, textWidth,textHeight);
        painter->drawText(boxScannedlRect,Qt::AlignVCenter | Qt::AlignLeft, boxScanned);

        const QString valBoxScanned = palletInfo.at(index).boxScanned;
        textWidth=painter->fontMetrics().horizontalAdvance(valBoxScanned);
        const QRect valBoxScannedRect(valBoxTotalRect.x(),boxScannedlRect.y(), textWidth,textHeight);
        painter->drawText(valBoxScannedRect,Qt::AlignVCenter | Qt::AlignLeft, valBoxScanned);

        const QString boxMissing = QString("Quantity of box missing :");
        textWidth=painter->fontMetrics().horizontalAdvance(boxMissing);
        const QRect boxMissingRect(0,boxScannedlRect.bottom()+interline, textWidth,textHeight);
        painter->drawText(boxMissingRect,Qt::AlignVCenter | Qt::AlignLeft, boxMissing);

        const QString valBoxMissing = palletInfo.at(index).boxMissing;
        textWidth=painter->fontMetrics().horizontalAdvance(valBoxMissing);
        const QRect valBoxMissingRect(valBoxTotalRect.x(),boxMissingRect.y(), textWidth,textHeight);
        painter->drawText(valBoxMissingRect,Qt::AlignVCenter | Qt::AlignLeft, valBoxMissing);

        painter->translate(QPoint(0,boxMissingRect.bottom()+interline));

        // Value informations
        footerRect = QRect(FooterRect.x()-painter->worldMatrix().dx(),FooterRect.y()-painter->worldMatrix().dy(),FooterRect.width(), FooterRect.height());
        space = QRect(0,0,pdfWriter->width(),30);
        if (!space.intersects(footerRect))
        {
            painter->translate(QPoint(0,space.height()));
        }
        QRect valueInfo(0,0,pdfWriter->width(),3*(textHeight+interline));
        if (valueInfo.intersects(footerRect))
        {
            pdfWriter->newPage();
            createPage(painter);
        }

        const QString valueTotal = QString("Total value on pallet :");
        textWidth=painter->fontMetrics().horizontalAdvance(valueTotal);
        const QRect valueTotalRect(0,0, textWidth,textHeight);
        painter->drawText(valueTotalRect,Qt::AlignVCenter | Qt::AlignLeft, valueTotal);

        const QString valValueTotal = palletInfo.at(index).valueTotal;
        textWidth=painter->fontMetrics().horizontalAdvance(valValueTotal);
        const QRect valValueTotalRect(valBoxTotalRect.x(),valueTotalRect.y(), textWidth,textHeight);
        painter->drawText(valValueTotalRect,Qt::AlignVCenter | Qt::AlignLeft, valValueTotal);

        const QString valueScanned = QString("Total value scanned :");
        textWidth=painter->fontMetrics().horizontalAdvance(valueScanned);
        const QRect valueScannedRect(0,valueTotalRect.bottom()+interline, textWidth,textHeight);
        painter->drawText(valueScannedRect,Qt::AlignVCenter | Qt::AlignLeft, valueScanned);

        const QString valValueScanned = palletInfo.at(index).valueScanned;
        textWidth=painter->fontMetrics().horizontalAdvance(valValueScanned);
        const QRect valValueScannedRect(valBoxTotalRect.x(),valueScannedRect.y(), textWidth,textHeight);
        painter->drawText(valValueScannedRect,Qt::AlignVCenter | Qt::AlignLeft, valValueScanned);

        const QString valueMissing = QString("Total value missing :");
        textWidth=painter->fontMetrics().horizontalAdvance(valueMissing);
        const QRect valueMissingRect(0,valueScannedRect.bottom()+interline, textWidth,textHeight);
        painter->drawText(valueMissingRect,Qt::AlignVCenter | Qt::AlignLeft, valueMissing);

        const QString valValueMissing = palletInfo.at(index).valueMissing;
        textWidth=painter->fontMetrics().horizontalAdvance(valValueMissing);
        const QRect valValueMissingRect(valBoxTotalRect.x(),valueMissingRect.y(), textWidth,textHeight);
        painter->drawText(valValueMissingRect,Qt::AlignVCenter | Qt::AlignLeft, valValueMissing);

        painter->translate(QPoint(0,valueMissingRect.bottom()+interline));
    }
}

void PdfReport::getDeliveryInformations(DeliveryInformations delInfo)
{
    deliveryInfo.table = new PDFTableView();
    deliveryInfo.table->setModel(delInfo.model);
    deliveryInfo.deliveryID     = delInfo.deliveryID;
    deliveryInfo.palletTotal    = delInfo.palletTotal;
    deliveryInfo.palletScanned  = delInfo.palletScanned;
    deliveryInfo.palletMissing  = delInfo.palletMissing;
    deliveryInfo.boxTotal       = delInfo.boxTotal;
    deliveryInfo.boxScanned     = delInfo.boxScanned;
    deliveryInfo.boxMissing     = delInfo.boxMissing;
    deliveryInfo.valueTotal     = delInfo.valueTotal;
    deliveryInfo.valueScanned   = delInfo.valueScanned;
    deliveryInfo.valueMissing   = delInfo.valueMissing;
}

void PdfReport::getPalletInformation(PalletInformations palInfo)
{
    PalletInformations tempPalletInfo;
    tempPalletInfo.table = new PDFTableView();
    tempPalletInfo.table->setModel(palInfo.model);
    tempPalletInfo.palletID     = palInfo.palletID;
    tempPalletInfo.boxTotal     = palInfo.boxTotal;
    tempPalletInfo.boxScanned   = palInfo.boxScanned;
    tempPalletInfo.boxMissing   = palInfo.boxMissing;
    tempPalletInfo.valueTotal   = palInfo.valueTotal;
    tempPalletInfo.valueScanned = palInfo.valueScanned;
    tempPalletInfo.valueMissing = palInfo.valueMissing;
    palletInfo.append(tempPalletInfo);
}
