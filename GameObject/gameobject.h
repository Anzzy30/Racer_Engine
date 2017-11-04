#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QVector>


#include "Component/transform.h"


class GameObject
{
public:
    GameObject();
    GameObject(QVector3D position, QQuaternion rotation, QVector3D scale);
    GameObject(Transform *transform);
    virtual ~GameObject();

    QMatrix4x4 getModelMatrix();


    virtual void update();


    template <typename T>
    T * getComponent() {
        return dynamic_cast<T*>
                (*std::find_if(components.begin(), components.end(), [&](Component * c) {
                     if(dynamic_cast<T*>(c))
                     return true;
                     return false;
                 }));
    }

    void addComponent(Component *c);


protected:



    QVector3D center;

    QMatrix4x4 model;

    QVector<Component *> components;


};


#endif // GAMEOBJECT_H
