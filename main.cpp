
#include "ApplicationInitializer.h"
#include "AppManager.h"

#include <QCoreApplication>
#include <QProcess>
#include <QStandardPaths>
#include <QFile>
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    ApplicationInitializer initializer;
    initializer.startStartupSequence();

    AppManager *appManager = new AppManager();
    appManager->startService();

//Currently, auto run .bat file is stopped
//#ifdef Q_OS_WIN
//    QProcess process;
//    QStringList tempParams;
//    tempParams.append(QDir::currentPath() + "\\release\\VDR_CollectorScript.bat");
//    bool bResult = process.startDetached("C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Node.js\\Node.js command prompt", tempParams);
//#endif

    return app.exec();
}
