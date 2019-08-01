#include "SampleModuleManager.h"
#include "SampleModuleDefines.h"
#include "Framework/GlobalDefine.h"

static const QString c_VERSION = "1.00002";

SampleModuleManager::SampleModuleManager()
    : m_pSampleModuleServer (new SampleModuleServer)
    , m_pCommonFunctions (new CommonFunctions)
    , m_pSampleModuleFileManager (new SampleModuleFileManager)
{
    TRACE_LOG("Version: " + c_VERSION);

    QObject::connect(this, &SampleModuleManager::serverError, this, &SampleModuleManager::onServerError);
}

bool SampleModuleManager::LoginUser(QString strUserName, QString strPwd)
{

    bool bResult = false;
    QByteArray arrayResponse = m_pSampleModuleServer->loginUser(strUserName, strPwd);
    if (arrayResponse.length() > 0)
    {
        QJsonDocument jsDoc = QJsonDocument::fromJson(arrayResponse);
        bResult = jsDoc.object().value("IsSuccessed").toBool();
        if (bResult == true)
        {
            m_pSampleModuleServer->TokenKey = jsDoc.object().value("Data").toObject().value("TokenKey").toString();
            m_pSampleModuleFileManager->saveLoginWithEmail(strUserName, strPwd);
        }
        else
        {
            emit serverError(jsDoc.object().value("Message").toString());
        }
    }
    else
    {
        emit serverError("Login failed: " + arrayResponse);
        bResult = false;
    }

    return bResult;
}

bool SampleModuleManager::AutoLogin()
{
    QString tempEmail = "";
    QString tempPwd = "";
    m_pSampleModuleFileManager->getLoginByEmail(tempEmail, tempPwd);

    if (tempEmail != "" && tempPwd != "")
    {
        return LoginUser(tempEmail, tempPwd);
    }
    return false;
}

bool SampleModuleManager::Initialize()
{
    TRACE_LOG(Q_FUNC_INFO);

    return true;
}

bool SampleModuleManager::Logout()
{
    QFile file(c_LoginInfo_FilePath);
    if (file.exists())
    {
        file.remove();
    }
    return true;
}

void SampleModuleManager::sampleMethod(QByteArray &data)
{
    Q_UNUSED(data);
}

void SampleModuleManager::sampleMethod(QJsonObject jsObj)
{
    Q_UNUSED(jsObj);
}

void SampleModuleManager::sampleMethod(QJsonArray jsArr)
{
    Q_UNUSED(jsArr);
}

void SampleModuleManager::onServerError(QString error)
{
    SampleModuleFileManager::addEventLog("SampleModuleManager::onServerError: " + error);
}

QByteArray SampleModuleManager::sampleReturningMethod()
{
    TRACE_LOG(Q_FUNC_INFO);
    return QByteArray("");
}
