#include "gameobject.h"

GameObject::GameObject():
    position(QVector3D(0,0,0)),
    rotation(QVector3D(0,0,0)),
    scale(QVector3D(0,0,0))
{

}

GameObject::GameObject(QVector3D position, QVector3D rotation, QVector3D scale):
    position(position),
    rotation(rotation),
    scale(scale)
{

}

void GameObject::draw()
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

QMatrix4x4 GameObject::getModelMatrix()
{
    model.setToIdentity();

    model.scale(scale);

    model.rotate(rotation.x(),1,0,0);
    model.rotate(rotation.y(),0,1,0);
    model.rotate(rotation.z(),0,0,1);

    model.translate(position);

    return model;
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
