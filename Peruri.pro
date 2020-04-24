QT       += core
QT       += gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4):   QT += widgets

CONFIG += c++11

TARGET = VelecSystems.DeliveryChecker
QMAKE_TARGET_DESCRIPTION = VELEC SYSTEMS - Delivery Checker

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ImprovedLineEdit.cpp \
    ProductNotFound.cpp \
    SQLTable/sqlview.cpp \
    finRepport/finrepportpage.cpp \
    databasewindow.cpp \
    identifyPage/identifypage.cpp \
    importPage/deliveryinfo.cpp \
    importPage/importpage.cpp \
    importPage/pillspushbutton.cpp \
    importPage/roundpushbutton.cpp \
    info/infobar.cpp \
    intRepport/intrepportpage.cpp \
    main.cpp \
    MainWindow.cpp \
    globals/globals.cpp \
    scanPage/scanpage.cpp \
    sideMenu/MenuButton.cpp \
    sideMenu/SideMenu.cpp \
    DB/database.cpp

HEADERS += \
    ImprovedLineEdit.h \
    MainWindow.h \
    ProductNotFound.h \
    SQLTable/sqlview.h \
    finRepport/finrepportpage.h \
    databasewindow.h \
    globals/globals.h \
    identifyPage/identifypage.h \
    importPage/deliveryinfo.h \
    importPage/importpage.h \
    importPage/pillspushbutton.h \
    importPage/roundpushbutton.h \
    info/infobar.h \
    intRepport/intrepportpage.h \
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
