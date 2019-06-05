#pragma once

#include <QString>
#include <QDebug>
#define DEBUGLOG(format, ...)   do { RAYLOG_CHECK_FORMAT(format, ##__VA_ARGS__); ELADebugEx(RAYLOG_LEVEL_DEBUG,   __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__); } while (false)
class CommonFunctions
{
public:
    static void AddLog(QString strLog);
};
