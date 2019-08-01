#include "DBLocalBase.h"
#include "Framework/SystemFile/FileManagerBase.h"
#include "Framework/FrameworkOwner.h"

static const QString DBTYPE = "QSQLITE";
static const QString DBNAME_DATA_MANAGEMENT = "LocalDB";
static const QString DBFILENAME_EXTENSION = ".db";
static const QString DBFILENAME_DATA_MANAGEMENT = DBNAME_DATA_MANAGEMENT + DBFILENAME_EXTENSION;
static const QString DBCON_DATA_MANAGEMENT = DBNAME_DATA_MANAGEMENT;
static const QString DBTBL_DATA = "tblData";

DBLocalBase::DBLocalBase(QObject *parent) : QObject(parent)
{   

}

DBLocalBase::~DBLocalBase()
{
    if (m_dbLocal.isOpen())
    {
        m_dbLocal.close();
    }
}

bool DBLocalBase::createDB(QString dbName, QString tableName)
{
    if (dbName != "" && tableName != "")
    {
        //Initialize target page database
        QSqlDatabase::database(dbName, false).close();
        QSqlDatabase::removeDatabase(dbName);

        m_dbLocal = QSqlDatabase::addDatabase(DBTYPE, DBCON_DATA_MANAGEMENT);
        m_dbLocal.setDatabaseName(dbName);

        if (m_dbLocal.isOpen() || m_dbLocal.open())
        {
            if (!m_dbLocal.tables().contains(tableName))
            {
                QSqlQuery query("", m_dbLocal);
                query.exec("create table " + tableName + " (data varchar)");
            }
            m_dbLocal.close();
        }

    }
    else
    {
        //Initialize target page database
        QSqlDatabase::database(DBCON_DATA_MANAGEMENT, false).close();
        QSqlDatabase::removeDatabase(DBCON_DATA_MANAGEMENT);

        m_dbLocal = QSqlDatabase::addDatabase(DBTYPE, DBCON_DATA_MANAGEMENT);
        m_dbLocal.setDatabaseName(DBFILENAME_DATA_MANAGEMENT);

        if (m_dbLocal.isOpen() || m_dbLocal.open())
        {
            if (!m_dbLocal.tables().contains(DBTBL_DATA))
            {
                QSqlQuery query("", m_dbLocal);
                query.exec("create table " + DBTBL_DATA + " (data varchar)");
            }
            m_dbLocal.close();
        }
    }

    return true;
}

bool DBLocalBase::addData(QString strData)
{
    if (m_dbLocal.isOpen() || m_dbLocal.open())
    {
        if (!m_dbLocal.tables().contains(DBTBL_DATA))
        {
            QSqlQuery query("", m_dbLocal);
            query.exec("create table " + DBTBL_DATA + " (data varchar)");
        }
        QSqlQuery query ("",m_dbLocal);
        query.prepare("INSERT INTO " + DBTBL_DATA + "(data) VALUES(:data)");
        query.bindValue(":data", strData);
        if (!query.exec())
        {
            FileManagerBase::addEventLog("add Crawled Url to database failed");
            FileManagerBase::addEventLog("result: " + query.lastError().text());
            return false;
        }
        m_dbLocal.close();
    }
    else
    {
        FileManagerBase::addEventLog(DBTBL_DATA + " can not open");
        FileManagerBase::addEventLog("result: " + m_dbLocal.lastError().text());
        return false;
    }
    return true;
}

bool DBLocalBase::hasData(QString strData)
{
    bool crawled = false;
    if (m_dbLocal.isOpen() || m_dbLocal.open())
    {
        if (m_dbLocal.tables().contains(DBTBL_DATA))
        {
            m_dbLocal.transaction();
            QString selectQuery = "SELECT * FROM " + DBTBL_DATA + " WHERE data = '" + strData + "'";

            QSqlQuery query(selectQuery, m_dbLocal);
            if (query.exec())
            {
                QJsonDocument jsDoc;
                QSqlRecord record = query.record();
                int nColData = record.indexOf("data");
                while(query.next())
                {
                    QString strTempData = query.value(nColData).toString();
                    if(strTempData != "")
                    {
                        crawled = true;
                        break;
                    }
                }
            }
            else
            {
                FileManagerBase::addEventLog("Load data from database failed for checking hasCrawledUrl");
                FileManagerBase::addEventLog("result: " + query.lastError().text());
            }
            m_dbLocal.commit();
        }
        else
        {
            FileManagerBase::addEventLog(DBTBL_DATA + " do not exist");
            FileManagerBase::addEventLog("result: " + m_dbLocal.lastError().text());
        }
    }

    return crawled;
}

QStringList DBLocalBase::loadData(int numberOfRecord)
{
    QStringList lstBDS;
    if (m_dbLocal.isOpen() || m_dbLocal.open())
    {
        if (m_dbLocal.tables().contains(DBTBL_DATA))
        {
            m_dbLocal.transaction();
            QString selectQuery = "SELECT * FROM " + DBTBL_DATA + " LIMIT " + QString::number(numberOfRecord);
            QSqlQuery query(selectQuery, m_dbLocal);
            if (query.exec())
            {
                QJsonDocument jsDoc;
                QSqlRecord record = query.record();
                int nColData = record.indexOf("data");
                while(query.next())
                {
                    QJsonDocument jsTempDoc;
                    QString strTempData = query.value(nColData).toString();
                    QByteArray arrayResponse = strTempData.toUtf8();
                    lstBDS.append(arrayResponse);
                }
            }
            else
            {
                FileManagerBase::addEventLog("loadAllCrawledUrl from database failed");
                FileManagerBase::addEventLog("result: " + query.lastError().text());
            }
            m_dbLocal.commit();
        }
        else
        {
            FileManagerBase::addEventLog(DBTBL_DATA + " do not exist");
            FileManagerBase::addEventLog("result: " + m_dbLocal.lastError().text());
        }
    }

    TRACE_LOG(lstBDS.count());
    return lstBDS;
}
