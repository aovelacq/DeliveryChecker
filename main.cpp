#include "MainWindow.h"
#include "DB/database.h"
#include "databasewindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow Window;
    DataBaseWindow WindowDB;
 //   Window.showMaximized();
    Window.show();
    WindowDB.exec();

    return app.exec();
}
