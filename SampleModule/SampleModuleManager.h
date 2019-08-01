#pragma once

#include "Framework/Model/ImageData.h"
#include "SampleModuleServer.h"
#include "SampleModuleFileManager.h"
#include "Framework/FrameworkOwner.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QTimer>
#include <memory>

class SampleModuleManager : public QObject
{
    Q_OBJECT
    std::unique_ptr<SampleModuleServer> m_pSampleModuleServer;
    std::unique_ptr<CommonFunctions> m_pCommonFunctions;
    std::unique_ptr<SampleModuleFileManager> m_pSampleModuleFileManager;

public:
    SampleModuleManager();

    bool LoginUser(QString strEmail, QString strPwd);
    bool AutoLogin();
    bool Initialize();
    bool Logout();

    void sampleMethod(QByteArray& data);
    void sampleMethod(QJsonObject jsObj);
    void sampleMethod(QJsonArray jsArr);

    QByteArray sampleReturningMethod();

    Q_SLOT void onServerError(QString error);

    Q_SIGNAL void serverError(QString error);
};
