#include "FrameworkOwner.h"

FrameworkOwner::FrameworkOwner() = default;

/**
 * Don't put this in the header.  Non-inlined version of multiple
 * data sources owner destructor.
 */
FrameworkOwner::~FrameworkOwner()
{

}

void FrameworkOwner::_onAboutToQuit()
{
    if(m_pDBLocalBase)
    {
        delete m_pDBLocalBase;
        m_pDBLocalBase = nullptr;
    }

    if(m_pCommonFunctions)
    {
        delete m_pCommonFunctions;
        m_pCommonFunctions = nullptr;
    }

    QtSingleton<FrameworkOwner>::onAboutToQuit();
}

FrameworkOwner *FrameworkOwner::getInstance()
{
    return QtSingleton<FrameworkOwner>::getInstance();
}

void FrameworkOwner::createObjects()
{
    m_pDBLocalBase = new DBLocalBase;
    m_pDBLocalBase->createDB();

    m_pCommonFunctions = new CommonFunctions;
}

DBLocalBase* FrameworkOwner::getDBLocalBase()
{
    return m_pDBLocalBase;
}

CommonFunctions* FrameworkOwner::getCommonFunctions()
{
    return m_pCommonFunctions;
}
