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

class DBLocalBase : public QObject
{
    Q_OBJECT
protected:
    QSqlDatabase m_dbLocal;

public:
    explicit DBLocalBase(QObject *parent = nullptr);
    ~DBLocalBase();

    bool createDB(QString dbName = "", QString tableName = "");
    bool addData(QString strData);
    bool hasData(QString strData);
    QStringList loadData(int numberOfRecord);

};
