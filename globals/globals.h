#ifndef GLOBALS_H
#define GLOBALS_H

#include <QtGlobal>
#include <QColor>
#include <QDir>
#include <QStandardPaths>

extern bool CONSOLE_DEBUG;
extern bool GRAPHICAL_DEBUG;
extern bool CLICK_SIDEMENU_ALLOWED;

// Colors //
extern QColor MAIN_BACKGROUND_COLOR;

extern QColor MENU_BACKGROUND_COLOR;
extern QColor MENU_BACKGROUND_ACTIVE;
extern QColor MENU_FONT_COLOR;

extern QColor INFO_BACKGROUND_COLOR;
extern QColor INFO_FONT_COLOR;

//LOG//
extern QString LOG_PATH;

// CSV //
extern QString CSV_FOLDER_PATH;
extern const QString CSV_DELIMITER;

extern const QString CSV_ITEMS_NAME;
extern bool CSV_ITEMS_HAS_SYS_FIELDS;

extern const QString CSV_JOBORDER_NAME;
extern bool CSV_JOBORDER_HAS_SYS_FIELDS;

extern const QString CSV_TRACEABILITY_BATCH_NAME;
extern bool CSV_TRACEABILITY_BATCH_HAS_SYS_FIELDS;

extern const QString CSV_TRACEABILITY_BOX_NAME;
extern bool CSV_TRACEABILITY_BOX_HAS_SYS_FIELDS;

extern const QString CSV_TRACEABILITY_PALLET_NAME;
extern bool CSV_TRACEABILITY_PALLET_HAS_SYS_FIELDS;

extern const QString CSV_DELIVERY_NAME;
extern bool CSV_DELIVERY_HAS_SYS_FIELDS;

extern const QString CSV_DELIVERY_LIST_NAME;
extern bool CSV_DELIVERY_LIST_HAS_SYS_FIELDS;

#endif // GLOBALS_H
