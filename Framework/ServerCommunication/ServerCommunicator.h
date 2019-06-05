#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>

#include "Framework/GlobalDefine.h"

class ServerCommunicator : public QObject
{
    Q_OBJECT
public:
    QString TokenKey = "";
    explicit ServerCommunicator(QObject *parent = nullptr);
    QNetworkAccessManager* m_serverAccessManager;

    void sampleGetAPI();
    QByteArray samplePostAPI(QByteArray bodyData);

signals:
    void sampleGetAPIResponsed(QNetworkReply* newResponse);
    void samplePostAPIResponsed(QNetworkReply* newResponse);
    void requestFinished(QNetworkReply* newResponse);
    void requestError(QNetworkReply* newResponse);
private slots:
    void serverResponse(QNetworkReply* newResponse);
private:
    QByteArray executeGETrequest(QNetworkRequest newRequest, bool isHaveToWait = false);
    QByteArray executePOSTrequest(QNetworkRequest newRequest, QByteArray newBodyData, bool isHaveToWait = false);
    QByteArray executePUTrequest(QNetworkRequest newRequest, QByteArray newBodyData, bool isHaveToWait = false);
};
