#pragma once

#include "Framework/GlobalDefine.h"
#include "SampleModule/SampleModuleDefines.h"

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class SimpleData : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(int dataId READ dataId WRITE setDataId NOTIFY dataChanged)
    Q_PROPERTY(int dataParentId READ dataParentId WRITE setDataParentId NOTIFY dataChanged)
    Q_PROPERTY(QString dataDisplayName READ dataDisplayName WRITE setDataDisplayName NOTIFY dataChanged)
    Q_PROPERTY(QString dataName READ dataName WRITE setDataName NOTIFY dataChanged)

public:
    explicit SimpleData(QObject *parent = nullptr);
    SimpleData(int nDataID, QString strDataName, QString strDisplayName, int nParentID);
    int dataId();
    int dataParentId();
    QString dataName();
    QString dataDisplayName();

    void setDataId(int newValue);
    void setDataName(QString newValue);
    void setDataParentId(int newValue);
    void setDataDisplayName(QString newValue);
    QString convertToJSON();
    QJsonObject convertToJSONObject();
    void importFromJSON(QString strData);
    void importFromJSON(QJsonObject jsObj);

    virtual int  getDataPoint();
signals:
    void dataChanged();
public slots:

protected:
    int m_dataId = DEFAULT_INT_VALUE;
    int m_dataParentId = DEFAULT_INT_VALUE;
    QString m_dataName = DEFAULT_TEXT;
    QString m_dataDisplayName = DEFAULT_TEXT;
};


