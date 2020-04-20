#ifndef FILEMGMT_H
#define FILEMGMT_H

#include "filemgmt_global.h"

#include <sys/stat.h>
#include <unistd.h>

class FILEMGMT_EXPORT Filemgmt
{
public:
    Filemgmt();

    bool fileExists(const QString &fileName);
};

#endif // FILEMGMT_H
