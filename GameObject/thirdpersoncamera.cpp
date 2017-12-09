#include "thirdpersoncamera.h"

ThirdPersonCamera::ThirdPersonCamera(GameObject *target):
    target(target)
{
    offset = 30;
}

void ThirdPersonCamera::update()
{

}

QMatrix4x4 ThirdPersonCamera::getViewMatrix()
{
    Transform *transformTarget = target->getComponent<Transform>();
    Transform *transform = getComponent<Transform>();
    transform->setPosition(transformTarget->getPosition()-QVector3D(offset,offset,offset));
    transform->setRotation(transformTarget->getRotation());

    QVector3D position = transform->getPosition();
    QQuaternion rotation = transform->getRotation();

    viewMatrix.setToIdentity();
    viewMatrix.lookAt(position,transformTarget->getPosition()-position,rotation*QVector3D(0,1,0));

    return viewMatrix;
}
