#include "GlobalDefine.h"
#include <QStandardPaths>
#include <QString>

#ifdef Q_OS_WIN
QString STORAGE_PATH = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
#else
QString STORAGE_PATH = QStandardPaths::AppDataLocation + "\\resource\\xml\\";
#endif
QString c_LoginInfo_FilePath = STORAGE_PATH + "Storage.xml";
QString c_Log_FilePath = STORAGE_PATH + "App.log";

QString AND = "&";

uint32_t MILLION = 1000000;
QString DEFAULT_TEXT = "";
int DEFAULT_SELECTED_ID = -999;
int DEFAULT_INT_VALUE = -999;
int DEFAULT_KEY = -999;
double MIN_DOUBLE_VALUE = 0.1;


