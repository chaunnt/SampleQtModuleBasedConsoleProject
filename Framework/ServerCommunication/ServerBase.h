#pragma once

#include "Framework/GlobalDefine.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QFile>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

class ServerBase : public QObject
{
    Q_OBJECT
public:
    explicit ServerBase(QObject *parent = nullptr);
    Q_SIGNAL void requestFinished(QNetworkReply* newResponse);
    Q_SIGNAL void requestError(QNetworkReply* newResponse);

protected:
    QByteArray _executeGETrequest(QNetworkRequest newRequest, bool isHaveToWait = false);
    QByteArray _executePOSTrequest(QNetworkRequest newRequest, QByteArray newBodyData, bool isHaveToWait = false);
    QByteArray _executePUTrequest(QNetworkRequest newRequest, QByteArray newBodyData, bool isHaveToWait = false);
    virtual void serverResponse(QNetworkReply* newResponse);

    QNetworkAccessManager* m_serverAccessManager;
};
