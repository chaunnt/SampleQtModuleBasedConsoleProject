QT += quick network sql
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    $$PWD/CommonFunctions/CommonFunctions.cpp \
    $$PWD/SystemFile/SystemFileManager.cpp \
    $$PWD/DBCommunication/DBCommunicator.cpp \
    $$PWD/ServerCommunication/ServerCommunicator.cpp \
    $$PWD/GlobalDefine.cpp

HEADERS += \
    $$PWD/CommonFunctions/CommonFunctions.h \
    $$PWD/SystemFile/SystemFileManager.h \
    $$PWD/DBCommunication/DBCommunicator.h \
    $$PWD/ServerCommunication/ServerCommunicator.h \
    $$PWD/GlobalDefine.h
