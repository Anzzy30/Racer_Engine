#include "transform.h"


Transform::Transform(GameObject *gameObject):
    Component(gameObject),
    position(QVector3D(0,0,0)),
    rotation(QQuaternion()),
    scale(QVector3D(0,0,0))
{

}

Transform::Transform(GameObject *gameObject, QVector3D position = QVector3D(0,0,0), QQuaternion rotation = QQuaternion(), QVector3D scale = QVector3D(1.0f,1.0f,1.0f)):
    Component(gameObject),
    position(position),
    rotation(rotation),
    scale(scale)
{

}


Transform::Transform(const Transform * t):
    Component(t->gameObject),
    position(t->position),
    rotation(t->rotation),
    scale(t->scale)
{

}

Transform::~Transform()
{

}

QVector3D Transform::getPosition() const
{
    return position;
}

QQuaternion Transform::getRotation() const
{
    return rotation;
}

QVector3D Transform::getScale() const
{
    return scale;
}

void Transform::setPosition(const QVector3D &value)
{
    position = value;
}

void Transform::setRotation(const QQuaternion &value)
{
    rotation = value;
}

void Transform::setScale(const QVector3D &value)
{
    scale = value;
}
