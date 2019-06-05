#include "SystemFileManager.h"
#include "Framework/GlobalDefine.h"

#include <QFile>

SystemFileManager::SystemFileManager(QObject *parent) : QObject(parent)
{

}

/**
 * @brief Save login info as JSON format
 * @param info: QMap<key, value>
 */
void SystemFileManager::saveLoginInfo(QMap<QString, QString> info)
{
    QFile file(LOGIN_INFO);

    if(!file.open(QIODevice::WriteOnly)){
        return;
    }

    QJsonObject jsObj;
    for (int i = 0; i < info.count(); ++i) {
        jsObj[info.keys()[i]] = info.value(info.keys()[i]);
    }

    file.write(QJsonDocument(jsObj).toJson());

    file.close();
}

/**
 * @brief get login info as JSON format
 * @return login info as JSON format
 */
QByteArray SystemFileManager::getLoginInfo()
{
    QByteArray result;
    QFile file(LOGIN_INFO);

    if (file.open(QFile::ReadOnly | QFile::Text )){
        result = file.readAll();
    }

    file.close();

    return result;
}

void SystemFileManager::removeLoginInfo()
{
    QFile file(LOGIN_INFO);
    if(file.exists()){
        file.remove();
    }
}

void SystemFileManager::addEventLog(QString strLog)
{
    QFile file(LOG_INFO);

    if(!file.open(QIODevice::Append)){
        return;
    }

    file.write(strLog.toUtf8());

    file.close();
}
