#include "logger.h"
namespace Logger
{
    void Debug(QString str)
    {
        qDebug().nospace() << "[" << verboseLvl << "]" << " [DEBUG]: " << qPrintable(str);
    }

    void Info(QString str)
    {
        qInfo().nospace() << "[" << verboseLvl << "]" << " [INFO]: " << qPrintable(str);
    }

    void Warning(QString str)
    {
        qWarning().nospace() << "[" << verboseLvl << "]" << " [WARNING]: " << qPrintable(str);
    }

    void Critical(QString str)
    {
        qCritical().nospace() << "[" << verboseLvl << "]" << " [CRITICAL]: " << qPrintable(str);
        abort();
    }

    void SetVerbose(int vbs)
    {
        verboseLvl = vbs;
    }
}
