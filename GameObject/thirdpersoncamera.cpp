#include "thirdpersoncamera.h"
#include "Component/vehiclecomponent.h"
# define M_PI 3.14159265358979323846  /* pi */


ThirdPersonCamera::ThirdPersonCamera(GameObject *target):
    target(target)
{
    offset = 220;
    Transform *transformTarget = target->getComponent<Transform>();
    targetPreviousPosition = transformTarget->getPosition();
}

void ThirdPersonCamera::update()
{
    Transform *transformTarget = target->getComponent<Transform>();
    Transform *transform = getComponent<Transform>();
    QQuaternion q = transformTarget->getRotation();

    QVector3D forwardQ = Utils::getForwardVectorFromQuat(q);

    QVector3D upQ = Utils::getUpVectorFromQuat(transform->getRotation());

    QVector3D pos = transform->getPosition();
    float dst = pos.distanceToPoint(transformTarget->getPosition()) - pos.distanceToPoint(targetPreviousPosition) ;
    qDebug() << dst;

    if(targetPreviousPosition != transformTarget->getPosition()){
        pos += (transformTarget->getPosition()-targetPreviousPosition).normalized() * dst;
    }

    if(target->getComponent<VehicleComponent>()->getOnGround()){
        QVector3D next_Pos = transformTarget->getPosition()+(-offset)*forwardQ + 50*upQ;
        next_Pos = Utils::lerp(pos,next_Pos,0.09);
        transform->setPosition(next_Pos);
    }else{
        QVector3D next_Pos = transformTarget->getPosition()+(-offset/1.3)*forwardQ + 150*upQ;
        next_Pos = Utils::lerp(pos,next_Pos,0.02);
        transform->setPosition(next_Pos);
    }
    QVector3D position = transform->getPosition();

    viewMatrix.setToIdentity();
    viewMatrix.lookAt(position,(transformTarget->getPosition()),upQ);

    targetPreviousPosition = transformTarget->getPosition();
}



QMatrix4x4 ThirdPersonCamera::getViewMatrix()
{
    return viewMatrix;
}
