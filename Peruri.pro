QT       += core
QT       += gui
QT       += sql
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4):   QT += widgets

CONFIG += c++11

TARGET = VelecSystems.DeliveryChecker
QMAKE_TARGET_DESCRIPTION = VELEC SYSTEMS - Delivery Checker
VERSION = 1.0.1.0
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SQLTable/pdftableview.cpp \
    SQLTable/sqlview.cpp \
    dataBaseWindow/ImprovedLineEdit.cpp \
    dataBaseWindow/databasewindow.cpp \
    finRepport/finrepportpage.cpp \
    identifyPage/identifypage.cpp \
    importPage/deliveryinfo.cpp \
    importPage/importpage.cpp \
    importPage/pillspushbutton.cpp \
    importPage/roundpushbutton.cpp \
    info/infobar.cpp \
    intRepport/intrepportpage.cpp \
    loadAnim/loadanim.cpp \
    main.cpp \
    MainWindow.cpp \
    globals/globals.cpp \
    pdf/barcode128.cpp \
    pdf/pdfreport.cpp \
    popUpWindows/ProductNotFound.cpp \
    popUpWindows/SureToCancel.cpp \
    popUpWindows/SureToContinue.cpp \
    scanPage/scanpage.cpp \
    sideMenu/MenuButton.cpp \
    sideMenu/SideMenu.cpp \
    DB/database.cpp

HEADERS += \
    MainWindow.h \
    SQLTable/pdftableview.h \
    SQLTable/sqlview.h \
    dataBaseWindow/ImprovedLineEdit.h \
    dataBaseWindow/databasewindow.h \
    finRepport/finrepportpage.h \
    globals/globals.h \
    identifyPage/identifypage.h \
    importPage/deliveryinfo.h \
    importPage/importpage.h \
    importPage/pillspushbutton.h \
    importPage/roundpushbutton.h \
    info/infobar.h \
    intRepport/intrepportpage.h \
    loadAnim/loadanim.h \
    pdf/barcode128.h \
    pdf/pdfreport.h \
    popUpWindows/ProductNotFound.h \
    popUpWindows/SureToCancel.h \
    popUpWindows/SureToContinue.h \
    scanPage/scanpage.h \
    sideMenu/MenuButton.h \
    sideMenu/SideMenu.h \
    DB/database.h

TRANSLATIONS += \
    Peruri_id_ID.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = logo.ico

RESOURCES += \
    Res.qrc
