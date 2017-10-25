#include "gameobject.h"

GameObject::GameObject()
{

}

QVector3D GameObject::getPosition() const
{
    return position;
}

QVector3D GameObject::getRotation() const
{
    return rotation;
}

QVector3D GameObject::getScale() const
{
    return scale;
}

void GameObject::setPosition(const QVector3D &value)
{
    position = value;
}

void GameObject::setRotation(const QVector3D &value)
{
    rotation = value;
}

void GameObject::setScale(const QVector3D &value)
{
    scale = value;
}
