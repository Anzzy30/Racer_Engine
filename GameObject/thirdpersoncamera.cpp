#include "thirdpersoncamera.h"

# define M_PI 3.14159265358979323846  /* pi */


ThirdPersonCamera::ThirdPersonCamera(GameObject *target):
    target(target)
{
    offset = 100;

}

void ThirdPersonCamera::update()
{

}



QMatrix4x4 ThirdPersonCamera::getViewMatrix()
{
    Transform *transformTarget = target->getComponent<Transform>();
    Transform *transform = getComponent<Transform>();
    QMatrix4x4 model = target->getModelMatrix();

    QVector3D axis;
    float angle;
    QQuaternion q = transformTarget->getRotation();
    QVector3D forwardQ( 2 * (q.x() * q.z() + q.scalar() * q.y()),
                        2 * (q.y() * q.x() - q.scalar() * q.x()),
                        1 - 2 * (q.x() * q.x() + q.y() * q.y()));

    QVector3D upQ( 2 * (q.x() * q.y() - q.scalar() * q.z()),
                        1 - 2 * (q.x() * q.x() + q.z() * q.z()),
                        2 * (q.y() * q.z() + q.scalar() * q.x()));

    QVector3D rightQ( 1 - 2 * (q.y() * q.y() + q.z() * q.z()),
                        2 * (q.x() * q.y() + q.scalar() * q.z()),
                        2 * (q.x() * q.z() - q.scalar() * q.y()));

    forwardQ.normalize();
    upQ.normalize();
    rightQ.normalize();
    QVector3D forward(model(0,2), model(1,2),model(2,2));
    forward.normalize();
    QVector3D right(model(0,0), model(0,1),model(0,2));
    right.normalize();
    QVector3D up(-model(1,0), -model(1,1),-model(1,2));
    up.normalize();
    qDebug() << rightQ << upQ <<forwardQ;
    transform->setPosition(transformTarget->getPosition()+(-offset)*forwardQ + 30*upQ);
    transform->setRotation(transformTarget->getRotation());

    QVector3D position = transform->getPosition();

    viewMatrix.setToIdentity();
    viewMatrix.lookAt(position,(transformTarget->getPosition()),upQ);

    return viewMatrix;
}
