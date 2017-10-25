#include "logger.h"
namespace Logger
{
    void Debug(QString str, int t)
    {
        if (t<=verboseTreshold)
        {
            qDebug().nospace() << "[" << t << "]" << " [DEBUG]: " << qPrintable(str);
        }
    }

    void Info(QString str, int t)
    {
        if (t<=verboseTreshold)
        {
            qInfo().nospace() << "[" << t << "]" << " [INFO]: " << qPrintable(str);
        }
    }

    void Warning(QString str, int t)
    {
        if (t<=verboseTreshold)
        {
            qWarning().nospace() << "[" << t << "]" << " [WARNING]: " << qPrintable(str);
        }
    }

    void Critical(QString str, int t)
    {
        if (t<=verboseTreshold)
        {
            qCritical().nospace() << "[" << t << "]" << " [CRITICAL]: " << qPrintable(str);
        }
    }

    void SetVerbose(int vbs)
    {
        verboseTreshold = vbs;
    }
}
