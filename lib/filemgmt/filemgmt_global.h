#ifndef FILEMGMT_GLOBAL_H
#define FILEMGMT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FILEMGMT_LIBRARY)
#  define FILEMGMT_EXPORT Q_DECL_EXPORT
#else
#  define FILEMGMT_EXPORT Q_DECL_IMPORT
#endif

#endif // FILEMGMT_GLOBAL_H
