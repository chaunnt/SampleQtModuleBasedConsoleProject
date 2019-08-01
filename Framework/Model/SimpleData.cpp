#include "SimpleData.h"
#include "SampleModule/SampleModuleDefines.h"
#include <QDebug>

SimpleData::SimpleData(QObject *parent) : QObject(parent)
{

}

SimpleData::SimpleData(int nDataID, QString strDataName, QString strDisplayName, int nParentID)
{
    m_dataId = nDataID;
    m_dataDisplayName = strDisplayName;
    m_dataName = strDataName;
    m_dataParentId = nParentID;
}

int SimpleData::dataId()
{
    return m_dataId;
}

QString SimpleData::dataName()
{
    return m_dataName;
}

QString SimpleData::dataDisplayName()
{
    return m_dataDisplayName;
}

int SimpleData::dataParentId()
{
    return m_dataParentId;
}

void SimpleData::setDataId(int newValue)
{
    if (m_dataId != newValue)
    {
        m_dataId= newValue;
        emit dataChanged();
    }
}

void SimpleData::setDataName(QString newValue)
{
    if (m_dataName != newValue)
    {
        m_dataName= newValue;
        emit dataChanged();
    }
}

void SimpleData::setDataParentId(int newValue)
{
    if (m_dataParentId != newValue)
    {
        m_dataParentId= newValue;
        emit dataChanged();
    }
}

void SimpleData::setDataDisplayName(QString newValue)
{
    if (m_dataDisplayName != newValue)
    {
        m_dataDisplayName= newValue;
        emit dataChanged();
    }
}

QString SimpleData::convertToJSON()
{
    return QJsonDocument(convertToJSONObject()).toJson();
}

QJsonObject SimpleData::convertToJSONObject()
{
    QJsonObject jsObj;
    if (m_dataId != DEFAULT_INT_VALUE)
    {
        jsObj[c_DataId] = m_dataId;
    }

    if (m_dataParentId != DEFAULT_INT_VALUE)
    {
        jsObj[c_ParentId] = m_dataParentId;
    }

    if (m_dataName != DEFAULT_TEXT)
    {
        jsObj[c_DataName] = m_dataName;
    }

    if (m_dataDisplayName != DEFAULT_TEXT)
    {
        jsObj[c_DisplayName] = m_dataDisplayName;
    }
    return jsObj;
}

void SimpleData::importFromJSON(QString strData)
{
    QJsonDocument jsDoc = QJsonDocument::fromJson(strData.toUtf8());

    if (!jsDoc.object().value(c_DataId).isNull()
            && !jsDoc.object().value(c_DataId).isUndefined()
            && jsDoc.object().value(c_DataId).toInt() != DEFAULT_INT_VALUE)
    {
        m_dataId = jsDoc.object().value(c_DataId).toInt();
    }

    if (!jsDoc.object().value(c_ParentId).isNull()
            && !jsDoc.object().value(c_ParentId).isUndefined()
            && jsDoc.object().value(c_ParentId).toInt() != DEFAULT_INT_VALUE)
    {
        m_dataParentId = jsDoc.object().value(c_ParentId).toInt();
    }

    if (!jsDoc.object().value(c_DataName).isNull()
            && !jsDoc.object().value(c_DataName).isUndefined()
            && jsDoc.object().value(c_DataName).toString() != DEFAULT_TEXT)
    {
        m_dataName = jsDoc.object().value(c_DataName).toString();
    }

    if (!jsDoc.object().value(c_DisplayName).isNull()
            && !jsDoc.object().value(c_DisplayName).isUndefined()
            && jsDoc.object().value(c_DisplayName).toString() != DEFAULT_TEXT)
    {
        m_dataDisplayName = jsDoc.object().value(c_DisplayName).toString();
    }
}

void SimpleData::importFromJSON(QJsonObject jsObj)
{
    if (!jsObj.value(c_DataId).isNull()
            && !jsObj.value(c_DataId).isUndefined()
            && jsObj.value(c_DataId).toInt() != DEFAULT_INT_VALUE)
    {
        m_dataId = jsObj.value(c_DataId).toInt();
    }

    if (!jsObj.value(c_ParentId).isNull()
            && !jsObj.value(c_ParentId).isUndefined()
            && jsObj.value(c_ParentId).toInt() != DEFAULT_INT_VALUE)
    {
        m_dataParentId = jsObj.value(c_ParentId).toInt();
    }

    if (!jsObj.value(c_DataName).isNull()
            && !jsObj.value(c_DataName).isUndefined()
            && jsObj.value(c_DataName).toString() != DEFAULT_TEXT)
    {
        m_dataName = jsObj.value(c_DataName).toString();
    }

    if (!jsObj.value(c_DisplayName).isNull()
            && !jsObj.value(c_DisplayName).isUndefined()
            && jsObj.value(c_DisplayName).toString() != DEFAULT_TEXT)
    {
        m_dataDisplayName = jsObj.value(c_DisplayName).toString();
    }
}

int SimpleData::getDataPoint()
{
    return 0;
}
