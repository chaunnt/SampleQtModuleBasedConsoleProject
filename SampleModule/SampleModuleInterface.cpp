#include "SampleModuleInterface.h"
#include "SampleModuleManager.h"

SampleModuleInterface::SampleModuleInterface() = default;

/**
 * Don't put this in the header.  Non-inlined version of multiple
 * data sources owner destructor.
 */
SampleModuleInterface::~SampleModuleInterface() = default;

SampleModuleInterface* SampleModuleInterface::getInstance()
{
    return QtSingleton<SampleModuleInterface>::getInstance();
}

void SampleModuleInterface::createObjects()
{
    m_pSampleModuleManager = new SampleModuleManager;
}

void SampleModuleInterface::sampleMethod(QByteArray& data)
{
    m_pSampleModuleManager->sampleMethod(data);

}

QByteArray SampleModuleInterface::sampleReturningMethod()
{
    return m_pSampleModuleManager->sampleReturningMethod();
}

void SampleModuleInterface::_onAboutToQuit()
{
    if(m_pSampleModuleManager)
    {
        delete m_pSampleModuleManager;
        m_pSampleModuleManager = nullptr;
    }

    QtSingleton<SampleModuleInterface>::onAboutToQuit();
}
