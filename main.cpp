#include "MainWindow.h"
#include "DB/database.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName(QString("VELEC SYSTEMS - Delivery Checker"));
    QCoreApplication::setApplicationVersion(QString(APP_VERSION));

    MainWindow Window;
    Window.showMaximized();
    //Window.show();

    return app.exec();
}
