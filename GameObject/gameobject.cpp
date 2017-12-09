#include "gameobject.h"

GameObject::GameObject():
    center(QVector3D(0,0,0))
{
    parent = NULL;
    components.push_back( new Transform(this));
}

GameObject::GameObject(QString name, QVector3D position, QQuaternion rotation, QVector3D scale):
    center(QVector3D(0,0,0)),parent(this),name(name)
{
    parent = NULL;
    components.push_back( new Transform(this,position,rotation,scale));
}

GameObject::GameObject(QString name,Transform *transform):
    center(QVector3D(0,0,0)),name(name)
{
    parent = NULL;
    components.push_back( transform);//new Transform(transform));

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

QString GameObject::getName() const
{
    return name;
}

void GameObject::setName(const QString &value)
{
    name = value;
}

GameObject *GameObject::getParent() const
{
    return parent;
}

QVector3D GameObject::getCenter() const
{
    return center;
}


QMatrix4x4 GameObject::getModelMatrix()
{
    Transform *transform = this->getComponent<Transform>();

    model.setToIdentity();
    model.translate(-center);

    if(parent != NULL){
        Transform *parentTransform = parent->getComponent<Transform>();

        model.translate((parentTransform->getPosition()));
    }
    model.translate((transform->getPosition()));

    if(parent != NULL){
        Transform *parentTransform = parent->getComponent<Transform>();

        model.rotate((parentTransform->getRotation()));
    }

    model.rotate(transform->getRotation());


    model.scale(transform->getScale());

    return model;
}




