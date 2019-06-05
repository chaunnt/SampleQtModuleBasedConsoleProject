#include "AppManager.h"

static const QString c_LoginKey_Email = "Email";
static const QString c_LoginKey_Password = "Password";

AppManager::AppManager(QObject *parent)
    : QObject(parent)
    , m_pServerCommunicator(new ServerCommunicator)
    , m_pDBCommunicator(new DBCommunicator)
    , m_pSystemFileManager(new SystemFileManager)
    , m_pCurrentUser(new AppUser)
{

}

AppManager::~AppManager()
{

}

bool AppManager::changePassword(QString strOldPwd, QString strNewPwd, QString strConfirmPwd)
{
    if (strNewPwd == strConfirmPwd){
        if (strOldPwd != "" && strNewPwd != ""){
            m_pCurrentUser->setPassword(strNewPwd);
        }
    }
    return true;
}

bool AppManager::forgotPassword(QString strEmail)
{
    return true;
}

bool AppManager::loginWithEmail(QString strEmail, QString strPwd)
{
    return true;
}

bool AppManager::loginWithPhoneNumber(QString strNumber, QString strPwd)
{
    return true;
}

bool AppManager::autoLogin()
{
    QString strEmail = "";
    QString strPwd = "";
    bool bResult = false;

    getLoginInfo(strEmail, strPwd);

    if(strEmail.isEmpty() || strPwd.isEmpty()){
        emit serverError("Login Failed");
    }else {
        bResult = loginWithEmail(strEmail, strPwd);
    }

    return bResult;
}

bool AppManager::startupApplication(){
    return true;
}

bool AppManager::logout()
{
    m_pSystemFileManager->removeLoginInfo();
    return true;
}


void AppManager::saveLoginInfo(QString strEmail, QString strPassword)
{
    QMap<QString, QString> tempMap;
    tempMap.insert(c_LoginKey_Email, strEmail);
    tempMap.insert(c_LoginKey_Password, strPassword);
    m_pSystemFileManager->saveLoginInfo(tempMap);
}

void AppManager::getLoginInfo(QString &strEmail, QString &strPassword)
{
    QJsonDocument jsDoc;
    jsDoc = QJsonDocument::fromJson(m_pSystemFileManager->getLoginInfo());
    strEmail = jsDoc.object().value(c_LoginKey_Email).toString();
    strPassword = jsDoc.object().value(c_LoginKey_Password).toString();
}

void AppManager::sampleCallAPI()
{
    qDebug() << Q_FUNC_INFO;
    m_pServerCommunicator->sampleGetAPI();
    QObject::connect(m_pServerCommunicator.get(), &ServerCommunicator::sampleGetAPIResponsed, [=] (QNetworkReply *newResponse) {
        QObject::disconnect(m_pServerCommunicator.get(), &ServerCommunicator::sampleGetAPIResponsed, nullptr, nullptr);
        qDebug() << "getAllAssignedProvinceResponsed";
        QString tempNetworkResponse;
        if(newResponse->error() == QNetworkReply::NoError)
        {
            QByteArray arrayResponse = newResponse->readAll();
            qDebug() << "arrayResponse: " << arrayResponse;
            QJsonDocument jsDoc = QJsonDocument::fromJson(arrayResponse);
            QJsonArray jsArr = jsDoc.object().value("Data").toArray();
            if(jsArr.count() > 0){
                //TODO
            }
        }
        else
        {
            tempNetworkResponse = newResponse->errorString() + " | " + newResponse->readAll();
            qDebug() << tempNetworkResponse;
            emit serverError(newResponse->errorString());
        }
        qDebug() << "tempNetworkResponse: " << tempNetworkResponse;
    });
}
