#ifndef LOGGER_H
#define LOGGER_H

#include <QCoreApplication>
#include <QDebug>
#include <QString>

namespace Logger
{
    void Debug(QString str);
    void Info(QString str);
    void Warning(QString str);
    void Critical(QString str);
    void SetVerbose(int vbs);

    static int verboseLvl=0;

};

#endif // LOGGER_H
