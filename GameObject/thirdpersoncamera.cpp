#include "thirdpersoncamera.h"

# define M_PI 3.14159265358979323846  /* pi */


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
    pitch = 40;
    float  hD  = 30 * cos(( pitch * M_PI ) / 180);
    float  vD  = 30 * sin(( pitch * M_PI ) / 180);



    float offsetX =  hD * sin(( pitch * M_PI ) / 180);
    float offsetZ =  hD * cos(( pitch * M_PI ) / 180);


    transform->setPosition(transformTarget->getPosition()+QVector3D(-offsetX,vD,-offsetZ));
    transform->setRotation(transformTarget->getRotation());

    QVector3D position = transform->getPosition();
    QQuaternion rotation = transform->getRotation();
    viewMatrix.setToIdentity();
    //rotation*up;
    viewMatrix.lookAt(position,(transformTarget->getPosition()),rotation*QVector3D(0,1,0));

    return viewMatrix;
}
