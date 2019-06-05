#pragma once

#include <QObject>
#include <QTextStream>
#include <QMap>
#include <QJsonObject>
#include <QJsonDocument>

class SystemFileManager : public QObject
{
    Q_OBJECT
public:
    explicit SystemFileManager(QObject *parent = nullptr);

    void saveLoginInfo(QMap<QString, QString> info);
    QByteArray getLoginInfo();
    void removeLoginInfo();

    static void addEventLog(QString strLog);

};

