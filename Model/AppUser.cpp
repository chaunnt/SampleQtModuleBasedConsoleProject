#include "AppUser.h"

AppUser::AppUser(QObject *parent)
    : QObject(parent)
    , m_Email("")
    , m_Password("")
{

}

AppUser::AppUser(QString strEmail, QString strPassword)
{
    m_Email = strEmail;
    m_Password = strPassword;
}

QString AppUser::getEmail()
{
    return m_Email;
}

QString AppUser::getPassword()
{
    return m_Password;
}

void AppUser::setEmail(QString newVal)
{
    m_Email = newVal;
}

void AppUser::setPassword(QString newVal)
{
    m_Password = newVal;
}
