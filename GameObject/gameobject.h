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

    virtual void draw();

    QMatrix4x4 getModelMatrix();

    Transform *getTransform();

protected:

    QVector3D center;

    QMatrix4x4 model;

    QVector<Component *> components;


};


#endif // GAMEOBJECT_H
