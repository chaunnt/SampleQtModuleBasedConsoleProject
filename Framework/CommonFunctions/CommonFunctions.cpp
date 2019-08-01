#include "CommonFunctions.h"

CommonFunctions::CommonFunctions()
{

}

///
/// \brief Print log for realtime checking
/// \param strLog: log details
///
void CommonFunctions::AddTraceLog(QString strLog)
{
    qDebug() << strLog;
}

void CommonFunctions::exportJson(QString strFileName, QJsonDocument jsDoc)
{
    QFile file(strFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << jsDoc.toJson();
    file.close();
}
