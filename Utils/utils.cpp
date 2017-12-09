#include "utils.h"

Utils::Utils()
{

}

QVector3D Utils::getUpVectorFromQuat(const QQuaternion &q)
{

    return QVector3D( 2 * (q.x() * q.y() - q.scalar() * q.z()),
                      1 - 2 * (q.x() * q.x() + q.z() * q.z()),
                      2 * (q.y() * q.z() + q.scalar() * q.x()));

}



QVector3D Utils::getForwardVectorFromQuat(const QQuaternion &q)
{

    return QVector3D ( 2 * (q.x() * q.z() + q.scalar() * q.y()),
                       2 * (q.y() * q.z() - q.scalar() * q.x()),
                       1 - 2 * (q.x() * q.x() + q.y() * q.y()));
}
