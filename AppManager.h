#pragma once

#include "Framework/GlobalDefine.h"
#include "Framework/ServerCommunication/ServerCommunicator.h"
#include "Framework/DBCommunication/DBCommunicator.h"
#include "Framework/SystemFile/SystemFileManager.h"
#include "Framework/CommonFunctions/CommonFunctions.h"
#include "Model/AppUser.h"

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QStandardPaths>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <memory>

class AppManager : public QObject
{
    Q_OBJECT
    std::unique_ptr<ServerCommunicator> m_pServerCommunicator;
    std::unique_ptr<DBCommunicator> m_pDBCommunicator;
    std::unique_ptr<SystemFileManager> m_pSystemFileManager;
    std::unique_ptr<AppUser> m_pCurrentUser;
public:
    explicit AppManager(QObject *parent = nullptr);
    ~AppManager();

    Q_INVOKABLE bool changePassword(QString strOldPwd, QString strNewPwd, QString strConfirmPwd);
    Q_INVOKABLE bool forgotPassword(QString strEmail);
    Q_INVOKABLE bool loginWithEmail(QString strEmail, QString strPwd);
    Q_INVOKABLE bool loginWithPhoneNumber(QString strNumber, QString strPwd);
    Q_INVOKABLE bool autoLogin();
    Q_INVOKABLE bool startupApplication();
    Q_INVOKABLE bool logout();

    void saveLoginInfo(QString strEmail, QString strPassword);
    void getLoginInfo(QString &strEmail, QString &strPassword);
    void sampleCallAPI();


signals:

    void serverError(QString errorMessage);
public slots:
};
