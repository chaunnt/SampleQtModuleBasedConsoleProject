#include "GlobalDefine.h"
#include <QStandardPaths>
#include <QString>

QString STORAGE_PATH = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
QString c_LoginInfo_FilePath = STORAGE_PATH + "Storage.xml";
QString c_Log_FilePath = STORAGE_PATH + "App.log";

QString DEFAULT_TEXT = "";
int DEFAULT_SELECTED_ID = -1;
int DEFAULT_INT_VALUE = -1;
int DEFAULT_KEY = -1;
double MIN_DOUBLE_VALUE = 0.1;
