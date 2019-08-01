#include "SampleModuleServer.h"
#include "SampleModuleDefines.h"
#include <QFileInfo>

static QString c_Cloud_Host = "http://CLOUD_HOST.vn:443/api";
static QString c_Ftp_Host = "ftp://FTP_HOST.com/dataresources/";

static QString c_API_GET_SAMPLE = "/Sample/SampleAPI";
static QString c_Params_UserId = "id=";

SampleModuleServer::SampleModuleServer(QObject *parent)
    : ServerBase(parent)
{

}

QByteArray SampleModuleServer::loginUser(QString& strUserName, QString& strPwd)
{
    QUrl url = QUrl(c_Cloud_Host + "/Users/UserLogin");
    QNetworkRequest request;
    QJsonObject jsObj;
    jsObj["UserName"] = strUserName;
    jsObj["Password"] = strPwd;

    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    return _executePOSTrequest(request, QJsonDocument(jsObj).toJson(), true);
}

void exportJson(QString strFileName, QJsonDocument jsDoc)
{
    QFile file(strFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << jsDoc.toJson();
    file.close();
}

QByteArray SampleModuleServer::uploadImage(QString newFileName)
{
    QFile newFile(newFileName);
    QUrl url = QUrl(c_Ftp_Host + QFileInfo(newFile).fileName());
    url.setUserName("admin_testftp");    // Set login
    url.setPassword("6o7A0T8HLT"); // Set пароль
    url.setPort(21);             // Protocol port, which we will work on

    QByteArray responseData;
    if (!newFile.open(QFile::ReadOnly))
    {
    }
    else
    {
        responseData = _executePUTrequest(QNetworkRequest(url), newFile.readAll());
        newFile.close();
    }

    return responseData;
}

void SampleModuleServer::serverResponse(QNetworkReply *newResponse)
{
    if (newResponse->error() == QNetworkReply::NoError)
    {
        QString responseUrl = newResponse->request().url().toString();

        if (responseUrl.contains(c_API_GET_SAMPLE))
        {
            emit sampleServerResponsed(newResponse);

        }
        else
        {
            emit requestFinished(newResponse);
            delete newResponse;
            newResponse = nullptr;
        }
    }
    else
    {
        emit requestError(newResponse);
        delete newResponse;
        newResponse = nullptr;
    }
}
