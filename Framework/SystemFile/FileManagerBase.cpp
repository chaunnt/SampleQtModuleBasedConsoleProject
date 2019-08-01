#include "FileManagerBase.h"
#include "Framework/GlobalDefine.h"
#include "Framework/FrameworkOwner.h"

#include <QFile>

static QString c_Key_LoginInfo = "LoginInfo";
static QString c_Key_Email = "Email";
static QString c_Key_Password = "Password";

FileManagerBase::FileManagerBase(QObject *parent) : QObject(parent)
{

}
void FileManagerBase::saveLoginWithEmail(QString strEmail, QString strPassword)
{
    QFile file(c_LoginInfo_FilePath);

    if (!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement(c_Key_LoginInfo);
    xmlWriter.writeTextElement(c_Key_Email, strEmail);
    xmlWriter.writeTextElement(c_Key_Password, strPassword);
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();
}

void FileManagerBase::getLoginByEmail(QString &strEmail, QString &strPassword)
{
    QFile file(c_LoginInfo_FilePath);

    if ( !file.open( QFile::ReadOnly | QFile::Text ) )
    {
        return;
    }
    QXmlStreamReader xmlStream(&file);
    while(!xmlStream.atEnd())
    {
        xmlStream.readNext();
        if (xmlStream.isStartElement() && xmlStream.name() == c_Key_LoginInfo)
        {

            while(!xmlStream.atEnd())
            {
                xmlStream.readNext();
                QString keyValue = xmlStream.name().toString();
                if (xmlStream.isStartElement() == true)
                {
                    if (keyValue == c_Key_Email)
                    {
                        strEmail = xmlStream.readElementText();
                    }
                    else if (keyValue == c_Key_Password)
                    {
                        strPassword = xmlStream.readElementText();
                    }
                }
            }
        }
    }

    file.close();
}

void FileManagerBase::saveLoginWithPhone(QString strPhoneNumber, QString strPassword)
{
    QFile file(c_LoginInfo_FilePath);

    if (!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("LoginInfo");
    xmlWriter.writeTextElement("PhoneNumber", strPhoneNumber);
    xmlWriter.writeTextElement("Password", strPassword);
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();
}

void FileManagerBase::getLoginByPhone(QString &strPhoneNumber, QString &strPassword)
{
    QFile file(c_LoginInfo_FilePath);

    if ( !file.open( QFile::ReadOnly | QFile::Text ) )
    {
        return;
    }
    QXmlStreamReader xmlStream(&file);
    while(!xmlStream.atEnd())
    {
        xmlStream.readNext();
        if (xmlStream.isStartElement() && xmlStream.name() == "LoginInfo")
        {

            while(!xmlStream.atEnd())
            {
                xmlStream.readNext();
                QString keyValue = xmlStream.name().toString();
                if (xmlStream.isStartElement() == true)
                {
                    if (keyValue == "PhoneNumber")
                    {
                        strPhoneNumber = xmlStream.readElementText();
                    }
                    else if (keyValue == "Password")
                    {
                        strPassword = xmlStream.readElementText();
                    }
                }
            }
        }
    }

    file.close();
}

///
/// \brief add log to log file
/// \param strLog: log detail
///
void FileManagerBase::addEventLog(QString strLog)
{
    TRACE_LOG(strLog);
    QFile file(c_Log_FilePath);

    if (!file.open(QIODevice::Append))
    {
        return;
    }

    file.write(strLog.toUtf8());

    file.close();
}
