#pragma once

#include <QObject>
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlResult>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "Framework/GlobalDefine.h"

class DBCommunicator : public QObject
{
    Q_OBJECT
    QSqlDatabase m_dbBDSData;
public:
    explicit DBCommunicator(QObject *parent = nullptr);

    bool addRecord(QString strData);
    bool updateRecord(QString strData);
signals:

public slots:
};
