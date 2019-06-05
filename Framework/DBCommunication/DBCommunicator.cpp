#include "DBCommunicator.h"

DBCommunicator::DBCommunicator(QObject *parent) : QObject(parent)
{   
    //Initialize target page database
    QSqlDatabase::database(DBCON_DATA_MANAGEMENT, false).close();
    QSqlDatabase::removeDatabase(DBCON_DATA_MANAGEMENT);
    m_dbBDSData = QSqlDatabase::addDatabase(DBTYPE, DBCON_DATA_MANAGEMENT);
    m_dbBDSData.setDatabaseName(DBFILENAME_DATA_MANAGEMENT);
    if(m_dbBDSData.isOpen() || m_dbBDSData.open()){
        if(!m_dbBDSData.tables().contains(DBTBL_DATA)){
            QSqlQuery query("", m_dbBDSData);
            query.exec("create table " + DBTBL_DATA + " (data varchar)");
        }
    }else{
        qDebug() << "Can not create database";
    }
}

bool DBCommunicator::addRecord(QString strData)
{
    if(m_dbBDSData.isOpen() || m_dbBDSData.open()){
        if(!m_dbBDSData.tables().contains(DBTBL_DATA)){
            qDebug() << "create new table";
            QSqlQuery query("", m_dbBDSData);
            query.exec("create table " + DBTBL_DATA + " (data varchar)");
        }

        QSqlQuery query ("",m_dbBDSData);
        query.prepare("INSERT INTO " + DBTBL_DATA + " (data) VALUES (:data)");
        query.bindValue(":data", strData);
        if(!query.exec()){
            qDebug() << "insert failed: " << query.lastError().text() ;
            return false;
        }
    }else{
        qDebug() << "Can not create database";
        return false;
    }
    return true;
}

bool DBCommunicator::updateRecord(QString strData)
{
    return true;
}


