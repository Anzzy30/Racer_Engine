#include "firstpersoncamera.h"

# define M_PI 3.14159265358979323846  /* pi */

FirstPersonCamera::FirstPersonCamera():
    Camera()
{
    v_mv = QVector2D(0,0);
    pitch=15;
    yaw=0;
    roll=0;
}


void FirstPersonCamera::update()
{
    Transform *transform = getComponent<Transform>();
    QVector3D position = transform->getPosition();

    pitch += v_mv.y() * 0.3f;
    yaw += v_mv.x() * 0.3f;

    if(pitch > 89.0)
        pitch = 89.0;
    else if(pitch < -89.0)
        pitch = -89.0;

    float phiRadian = ( pitch * M_PI ) / 180;
    float thetaRadian = ( yaw * M_PI ) / 180;

    lookAt.setX(cos(phiRadian) * -sin(thetaRadian));
    lookAt.setY(-sin(phiRadian));
    lookAt.setZ(cos(phiRadian) * cos(thetaRadian));

    QVector3D right;
    right.setX(sin(thetaRadian- 3.14f/2.0f));
    right.setY(0);
    right.setZ(-cos(thetaRadian- 3.14f/2.0f));

    if(moveForward){
        position.setX(position.x() + lookAt.x() * 1.5f);
        position.setY(position.y() + lookAt.y() * 1.5f);
        position.setZ(position.z() + lookAt.z() * 1.5f);
    }

    if(moveBackward){
        position.setX(position.x() - lookAt.x() * 1.5f);
        position.setY(position.y() - lookAt.y() * 1.5f);
        position.setZ(position.z() - lookAt.z() * 1.5f);

    }
    if(moveLeft){
        position.setX(position.x() - right.x() * 1.5f);
        position.setZ(position.z() - right.z() * 1.5f);
    }
    if(moveRight){

        position.setX(position.x() + right.x() * 1.5f);
        position.setZ(position.z() + right.z() * 1.5f);
    }
    position.setY(position.y() + 0.7f*(moveUpper-moveDown));
    transform->setPosition(position);
    v_mv = QVector2D(0,0);

    moveForward = false;
    moveBackward = false;
    moveLeft = false;
    moveRight = false;
    moveUpper = false;
    moveDown = false;
}


QMatrix4x4 FirstPersonCamera::getViewMatrix()
{
    Transform *transform = getComponent<Transform>();
    QVector3D position = transform->getPosition();

    viewMatrix.setToIdentity();
    viewMatrix.lookAt(QVector3D(position.x(),position.y(),position.z()),QVector3D(position.x()+lookAt.x(),position.y()+lookAt.y(),position.z()+lookAt.z()),QVector3D(0,1,0));

    return viewMatrix;
}

void FirstPersonCamera::setMoveLeft(bool value)
{
    moveLeft = value;
}

void FirstPersonCamera::setMoveRight(bool value)
{
    moveRight = value;
}

void FirstPersonCamera::setMoveForward(bool value)
{
    moveForward = value;
}

void FirstPersonCamera::setMoveBackward(bool value)
{
    moveBackward = value;
}

void FirstPersonCamera::setMoveUpper(bool value)
{
    moveUpper = value;
}

void FirstPersonCamera::setMoveDown(bool value)
{
    moveDown = value;
}

void FirstPersonCamera::setV_mv(const QVector2D &value)
{
    v_mv = value;
}
