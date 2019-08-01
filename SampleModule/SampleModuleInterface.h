#pragma once

#include "Framework/Utils/QtSingleton.h"

#include <QObject>
#include <memory>

class SampleModuleManager;
class SampleModuleInterface : public QObject, private QtSingleton<SampleModuleInterface>
{
    Q_OBJECT
public:
    /// Static getter for System function owner class
    static SampleModuleInterface* getInstance();

    void createObjects();
    virtual ~SampleModuleInterface();

    void sampleMethod(QByteArray &data);
    QByteArray sampleReturningMethod();
private:
    friend class QtSingleton<SampleModuleInterface>;

    SampleModuleManager* m_pSampleModuleManager; ///Owner of this class

    SampleModuleInterface();

    Q_SLOT void _onAboutToQuit();
};
