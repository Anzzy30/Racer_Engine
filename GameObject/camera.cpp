#include "camera.h"

Camera::Camera():
    GameObject("Camera",new Transform(this,QVector3D(30,30,30),QQuaternion(),QVector3D()))
{
    lookAt = QVector3D(0,0,0);
}

Camera::~Camera()
{

}

float Camera::getFOV() const
{
    return FOV;
}

void Camera::setFOV(float value)
{
    FOV = value;
}

float Camera::getNEAR_PLANE() const
{
    return NEAR_PLANE;
}

void Camera::setNEAR_PLANE(float value)
{
    NEAR_PLANE = value;
}

float Camera::getFAR_PLANE() const
{
    return FAR_PLANE;
}

void Camera::setFAR_PLANE(float value)
{
    FAR_PLANE = value;
}

QMatrix4x4 Camera::getProjectionMatrix() const
{
    return projectionMatrix;
}

void Camera::setProjectionMatrix(const QMatrix4x4 &value)
{
    projectionMatrix = value;
}


void Camera::setViewMatrix(const QMatrix4x4 &value)
{
    viewMatrix = value;
}

float Camera::getPitch() const
{
    return pitch;
}

void Camera::setPitch(float value)
{
    pitch = value;
}

float Camera::getRoll() const
{
    return roll;
}

void Camera::setRoll(float value)
{
    roll = value;
}

float Camera::getYaw() const
{
    return yaw;
}

void Camera::setYaw(float value)
{
    yaw = value;
}


QVector3D Camera::getLookAt() const
{
    return lookAt;
}

void Camera::setLookAt(const QVector3D &value)
{
    lookAt = value;
}

