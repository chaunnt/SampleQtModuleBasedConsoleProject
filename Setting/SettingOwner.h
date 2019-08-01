#pragma once

#include <QObject>
#include <memory>

#include "Framework/Utils/QtSingleton.h"

/**
 * @brief Class contain all functions related to Settings of system
 */
class SettingOwner : public QObject, private QtSingleton<SettingOwner>
{
    Q_OBJECT

public:
    friend class QtSingleton<SettingOwner>;

    /// Static getter for System function owner class
    static SettingOwner* getInstance();

    //Initialise the Setting
    void createObjects();

private:
    SettingOwner();
    virtual ~SettingOwner();

    Q_SLOT void _onAboutToQuit();
};
