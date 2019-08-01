#pragma once

#include "Framework/ServerCommunication/ServerBase.h"

#include <QObject>

class SampleModuleServer : public ServerBase
{
    Q_OBJECT
public:
    QString TokenKey = "";

    explicit SampleModuleServer(QObject *parent = nullptr);

    QByteArray loginUser(QString &strUserName, QString &strPwd);

    QByteArray uploadImage(QString newFileName);

    Q_SIGNAL void sampleServerResponsed(QNetworkReply* newResponse);

protected:
    virtual void serverResponse(QNetworkReply* newResponse) override;
};
