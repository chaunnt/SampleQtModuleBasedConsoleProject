#include "AppManager.h"
#include "Framework/FrameworkOwner.h"

#include <QDebug>

AppManager::AppManager(QObject *parent)
    : QObject(parent)
{
    Initialize();
}

void AppManager::Initialize()
{

}

void AppManager::startService()
{
    TRACE_LOG("startupApplication");
}

void AppManager::_onDataCollected(QByteArray data)
{
    Q_UNUSED(data);
}
