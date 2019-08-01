!include(SampleModule/SampleModule.pri){
    error("Couldn't include the SampleModule.pri file")
}

!include(Framework/Framework.pri){
    error("Couldn't include the Framework.pri file")
}

!include(Setting/Setting.pri){
    error("Couldn't include the Setting.pri file")
}

QT -= gui
QT += network sql
CONFIG += c++11 console

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
android: {

    QT += androidextras
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

    OTHER_FILES += \
        android/AndroidManifest.xml
    ANDROID_EXTRA_LIBS += \
        $$PWD/resource/lib/libcrypto.so \
        $$PWD/resource/lib/libssl.so
}

SOURCES += main.cpp \
    AppManager.cpp \
    ApplicationInitializer.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    AppManager.h \
    ApplicationInitializer.h
