#include "gameobject.h"

GameObject::GameObject():
    center(QVector3D(0,0,0))
{
    components.push_back( new Transform(this));
}

GameObject::GameObject(QVector3D position, QQuaternion rotation, QVector3D scale):
    center(QVector3D(0,0,0))
{
    components.push_back( new Transform(this,position,rotation,scale));
}

GameObject::GameObject(Transform *transform):
    center(QVector3D(0,0,0))
{
    components.push_back( new Transform(transform));

}

void GameObject::draw()
{

}


QMatrix4x4 GameObject::getModelMatrix()
{
    Transform *transform = getTransform();

    model.setToIdentity();
    model.translate(-center);

    model.scale(transform->getScale());

    model.rotate(transform->getRotation());


    model.translate(transform->getPosition()/transform->getScale());

    return model;
}



Transform *GameObject::getTransform()
{
    return dynamic_cast<Transform*>(*std::find_if(components.begin(), components.end(), [&](Component * c) {
        if(dynamic_cast<Transform*>(c))
            return true;
        return false;
    }));

}
