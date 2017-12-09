#ifndef UTILS_H
#define UTILS_H
#include <QVector3D>
#include <QQuaternion>
class Utils
{
public:
    Utils();

    static QVector3D getUpVectorFromQuat(const QQuaternion &q);
    static QVector3D getForwardVectorFromQuat(const QQuaternion &q);
};

#endif // UTILS_H
