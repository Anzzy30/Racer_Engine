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
    QQuaternion q = transformTarget->getRotation();

    QVector3D forwardQ = Utils::getForwardVectorFromQuat(q);

    QVector3D upQ = Utils::getUpVectorFromQuat(q);

    forwardQ.normalize();
    upQ.normalize();
    transform->setPosition(transformTarget->getPosition()+(-offset)*forwardQ + 30*upQ);
    transform->setRotation(transformTarget->getRotation());

    QVector3D position = transform->getPosition();

    viewMatrix.setToIdentity();
    viewMatrix.lookAt(position,(transformTarget->getPosition()),upQ);

    return viewMatrix;
}
