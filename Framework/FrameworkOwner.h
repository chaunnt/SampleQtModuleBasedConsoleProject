#pragma once

#include <QObject>
#include <memory>

#include "Framework/Utils/QtSingleton.h"
#include "Framework/CommonFunctions/CommonFunctions.h"
#include "Framework/DBCommunication/DBLocalBase.h"

///Use this to output stderr
//#define TRACE_LOG(log) qDebug() << Q_FUNC_INFO << "(" << __LINE__ << ")" << log
//#define TRACE_NAKED(log) qDebug() << log

///Use this to output to stdout
#define TRACE_LOG(log) QTextStream(stdout) << Q_FUNC_INFO << " (" << __LINE__ << ") " << log << "\r\n"
#define TRACE_NAKED(log) QTextStream(stdout) << log << " \r\n"

/**
 * @brief Class contain all functions related to Utils
 * or framework level functionality
 */
class FrameworkOwner: public QObject, private QtSingleton<FrameworkOwner>
{
public:

    friend class QtSingleton<FrameworkOwner>;

    /// Static getter for System function owner class
    static FrameworkOwner* getInstance();

    //Initialise the framework
    void createObjects();

    /// We use simple pointer instead of smart pointer
    /// It will help us build on Less-Support-C++11 and higher system (like centos)
    DBLocalBase* getDBLocalBase();
    CommonFunctions* getCommonFunctions();
private:

    volatile bool m_deleting = false;

    CommonFunctions* m_pCommonFunctions; //Owner of this object
    DBLocalBase* m_pDBLocalBase; //Owner of this object

    FrameworkOwner();
    virtual ~FrameworkOwner();

    Q_SLOT void _onAboutToQuit();
};
