QT += network sql
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += SampleModule/SampleModuleFileManager.cpp
HEADERS += SampleModule/SampleModuleFileManager.h

SOURCES += SampleModule/SampleModuleInterface.cpp
HEADERS += SampleModule/SampleModuleInterface.h

SOURCES += SampleModule/SampleModuleManager.cpp
HEADERS += SampleModule/SampleModuleManager.h

SOURCES += SampleModule/SampleModuleServer.cpp
HEADERS += SampleModule/SampleModuleServer.h

SOURCES += SampleModule/SampleModuleDefines.cpp
HEADERS += SampleModule/SampleModuleDefines.h

INCLUDEPATH *= ../Framework
