#include "filemgmt.h"

Filemgmt::Filemgmt()
{
}

bool Filemgmt::fileExists(const QString &fileName)
{
    std::filesystem::exists(fileName);
}
