#ifndef LOGGER_H
#define LOGGER_H

#include <QCoreApplication>
#include <QDebug>
#include <QString>

namespace Logger
{
    void Debug(QString str,int t);
    void Info(QString str, int t);
    void Warning(QString str, int t);
    void Critical(QString str, int t);
    void SetVerbose(int vbs);

    static int verboseTreshold=0;


};

#endif // LOGGER_H
