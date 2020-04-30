#include "globals.h"

// Debug //
bool    CONSOLE_DEBUG           = true;
bool    GRAPHICAL_DEBUG         = false;
bool    CLICK_SIDEMENU_ALLOWED  = false;

// Colors //
QColor  MAIN_BACKGROUND_COLOR   (0,130,200);

QColor  MENU_BACKGROUND_COLOR   (0,130,200);
QColor  MENU_BACKGROUND_ACTIVE  (250,180,50);
QColor  MENU_FONT_COLOR         (255,255,255);

QColor  INFO_BACKGROUND_COLOR   (0,130,200);
QColor  INFO_FONT_COLOR         (255,255,255);

//LOG//
QString LOG_PATH                                = QDir::homePath()+"/"+QStandardPaths::displayName(QStandardPaths::DesktopLocation)+"/";
                                                  //QDir::tempPath()/VELEC SYSTEMS/DeliveryChecker/Logfile
// CSV //
const QString CSV_DELIMITER                     = ";";
const QString CSV_ITEMS_NAME                    = "ITEMS";
bool CSV_ITEMS_HAS_SYS_FIELDS                   = true;

const QString CSV_JOBORDER_NAME                 = "JOBORDER";
bool CSV_JOBORDER_HAS_SYS_FIELDS                = true;

const QString CSV_TRACEABILITY_BATCH_NAME       = "TRACEABILITY_BATCH";
bool CSV_TRACEABILITY_BATCH_HAS_SYS_FIELDS      = true;

const QString CSV_TRACEABILITY_BOX_NAME         = "TRACEABILITY_BOX";
bool CSV_TRACEABILITY_BOX_HAS_SYS_FIELDS        = true;

const QString CSV_TRACEABILITY_PALLET_NAME      = "TRACEABILITY_PALLET";
bool CSV_TRACEABILITY_PALLET_HAS_SYS_FIELDS     = true;

const QString CSV_DELIVERY_NAME                 = "DELIVERY";
bool CSV_DELIVERY_HAS_SYS_FIELDS                = true;

const QString CSV_DELIVERY_LIST_NAME            = "DELIVERY_LIST";
bool CSV_DELIVERY_LIST_HAS_SYS_FIELDS           = true;
