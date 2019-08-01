#include "ApplicationInitializer.h"
#include "Framework/FrameworkOwner.h"
#include "Setting/SettingOwner.h"
#include "SampleModule/SampleModuleInterface.h"

ApplicationInitializer::ApplicationInitializer(QObject *parent)
    : QObject(parent)
{

}

void ApplicationInitializer::startStartupSequence()
{
    m_State = State::InitialisingSettings;

    //Init Framework singleton
    const auto &pFrameworkOwner = FrameworkOwner::getInstance();
    pFrameworkOwner->createObjects();

    //Init Setting singleton
    SettingOwner* pSettingOwner = SettingOwner::getInstance();
    pSettingOwner->createObjects();

    //Init Module singleton
    SampleModuleInterface* pSampleModuleInterface = SampleModuleInterface::getInstance();
    pSampleModuleInterface->createObjects();

}
