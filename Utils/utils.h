#ifndef UTILS_H
#define UTILS_H
#include <QVector3D>
#include <QQuaternion>
#include <algorithm>
class Utils
{
public:
    Utils();

    static QVector3D getUpVectorFromQuat(const QQuaternion &q);
    static QVector3D getForwardVectorFromQuat(const QQuaternion &q);
    static QVector3D lerp( const QVector3D& begin, const QVector3D& end, float t );
};

#endif // UTILS_H
