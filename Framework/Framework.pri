QT += network sql
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += $$PWD/CommonFunctions/CommonFunctions.cpp
HEADERS += $$PWD/CommonFunctions/CommonFunctions.h

HEADERS += $$PWD/Utils/QtSingleton.h

SOURCES += $$PWD/FrameworkOwner.cpp
HEADERS += $$PWD/FrameworkOwner.h

SOURCES += $$PWD/ServerCommunication/ServerBase.cpp
HEADERS += $$PWD/ServerCommunication/ServerBase.h

SOURCES += $$PWD/SystemFile/FileManagerBase.cpp
HEADERS += $$PWD/SystemFile/FileManagerBase.h

SOURCES += $$PWD/DBCommunication/DBLocalBase.cpp
HEADERS += $$PWD/DBCommunication/DBLocalBase.h

SOURCES += $$PWD/GlobalDefine.cpp
HEADERS += $$PWD/GlobalDefine.h

SOURCES +=
HEADERS +=

SOURCES += $$PWD/Model/ImageData.cpp
HEADERS += $$PWD/Model/ImageData.h

SOURCES += $$PWD/Model/SimpleData.cpp
HEADERS += $$PWD/Model/SimpleData.h

