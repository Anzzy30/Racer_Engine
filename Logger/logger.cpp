#include "logger.h"


Logger::Logger()
{
#ifdef QT_DEBUG
  qDebug() << "Logger Activated";
#endif
}

Logger::~Logger()
{

}
