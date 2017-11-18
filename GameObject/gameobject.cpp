#include "gameobject.h"

GameObject::GameObject():
    center(QVector3D(0,0,0)),parent(this)
{
    components.push_back( new Transform(this));
}

GameObject::GameObject(QVector3D position, QQuaternion rotation, QVector3D scale):
    center(QVector3D(0,0,0)),parent(this)
{
    components.push_back( new Transform(this,position,rotation,scale));
}

GameObject::GameObject(Transform *transform):
    center(QVector3D(0,0,0)),parent(this)
{
    components.push_back( new Transform(transform));

}

GameObject::~GameObject()
{
    for(auto &c : components)
        delete c;

}



void GameObject::update()
{
    for(auto &c : components)
        c->update();
}

void GameObject::addComponent(Component *c)
{
    components.push_back(c);
}

void GameObject::addChild(GameObject *child)
{
    child->parent = this;
    childs.push_back(child);
}


QMatrix4x4 GameObject::getModelMatrix()
{
    Transform *transform = this->getComponent<Transform>();

    model.setToIdentity();
    model.translate(-center);
    model.scale(transform->getScale());

    model.rotate(transform->getRotation());
    if(parent != this){
        Transform *parentTransform = parent->getComponent<Transform>();

        model.translate(parentTransform->getRotation().rotatedVector(parentTransform->getPosition()/transform->getScale()));
    }
    model.translate(transform->getRotation().rotatedVector(transform->getPosition())/transform->getScale());


    return model;
}




