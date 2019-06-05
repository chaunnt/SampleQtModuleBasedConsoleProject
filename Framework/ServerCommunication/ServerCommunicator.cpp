#include "ServerCommunicator.h"

static QString SAMPLE_POST_API = "/api/samplepost";
static QString SAMPLE_GET_API = "/api/sampleget";

ServerCommunicator::ServerCommunicator(QObject *parent) : QObject(parent)
{
    m_serverAccessManager = new QNetworkAccessManager;
    connect(m_serverAccessManager, &QNetworkAccessManager::finished, this, &ServerCommunicator::serverResponse);
}

void ServerCommunicator::sampleGetAPI()
{
    qDebug() << Q_FUNC_INFO;
    QUrl url = QUrl(CLOUD_HOST_SAMPLE + SAMPLE_GET_API + PARAM_MARK + PARAM_TOKENKEY + TokenKey);
    QNetworkRequest request;

    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    executeGETrequest(request);
}

QByteArray ServerCommunicator::samplePostAPI(QByteArray bodyData)
{
    qDebug() << Q_FUNC_INFO;
    QUrl url = QUrl(CLOUD_HOST_SAMPLE + SAMPLE_POST_API + PARAM_MARK + PARAM_TOKENKEY + TokenKey);
    QNetworkRequest request;

    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray responseData = executePOSTrequest(request, bodyData, true);
    return responseData;
}

QByteArray ServerCommunicator::executeGETrequest(QNetworkRequest newRequest, bool isHaveToWait)
{
    QByteArray responseData;
    if(isHaveToWait){
        QNetworkAccessManager tempNamLogin;
        QNetworkReply* newResponse = tempNamLogin.get(newRequest);
        QEventLoop tempLoop;
        connect(&tempNamLogin, SIGNAL(finished(QNetworkReply*)), &tempLoop, SLOT(quit()));
        tempLoop.exec();
        responseData = newResponse->readAll();

        delete newResponse;
        newResponse = nullptr;
    }else{
        m_serverAccessManager->get(newRequest);
    }
    return responseData;
}

QByteArray ServerCommunicator::executePOSTrequest(QNetworkRequest newRequest, QByteArray newBodyData, bool isHaveToWait)
{
    QByteArray responseData;
    if(isHaveToWait){
        QNetworkAccessManager tempNamLogin;
        QNetworkReply* newResponse = tempNamLogin.post(newRequest, newBodyData);
        QEventLoop tempLoop;
        connect(&tempNamLogin, SIGNAL(finished(QNetworkReply*)), &tempLoop, SLOT(quit()));
        tempLoop.exec();
        responseData = newResponse->readAll();

        delete newResponse;
        newResponse = nullptr;
    }else{
        m_serverAccessManager->post(newRequest, newBodyData);
    }
    return responseData;
}

QByteArray ServerCommunicator::executePUTrequest(QNetworkRequest newRequest, QByteArray newBodyData, bool isHaveToWait)
{
    QByteArray responseData;
    if(isHaveToWait){
        QNetworkAccessManager tempNamLogin;
        QNetworkReply* newResponse = tempNamLogin.put(newRequest, newBodyData);
        QEventLoop tempLoop;
        connect(&tempNamLogin, SIGNAL(finished(QNetworkReply*)), &tempLoop, SLOT(quit()));
        tempLoop.exec();
        responseData = newResponse->readAll();

        delete newResponse;
        newResponse = nullptr;
    }else{
        m_serverAccessManager->put(newRequest, newBodyData);
    }

    return responseData;
}
void ServerCommunicator::serverResponse(QNetworkReply *newResponse)
{
    if(newResponse->error() == QNetworkReply::NoError){
        QString responseUrl = newResponse->request().url().toString();
        if(responseUrl.contains(SAMPLE_POST_API)){
            emit samplePostAPIResponsed(newResponse);
        }else if(responseUrl.contains(SAMPLE_GET_API)){
            emit sampleGetAPIResponsed(newResponse);
        }else{
            emit requestFinished(newResponse);
            delete newResponse;
            newResponse = nullptr;
        }
    }else{
        emit requestError(newResponse);
        delete newResponse;
        newResponse = nullptr;
    }
}
