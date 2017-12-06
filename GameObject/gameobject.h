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
    GameObject(QString name,QVector3D position, QQuaternion rotation, QVector3D scale);
    GameObject(QString name,Transform *transform);
    virtual ~GameObject();

    QMatrix4x4 getModelMatrix();


    virtual void update();


    template <typename T>
    T * getComponent() {
        QVector<Component*>::iterator iterator(std::find_if(components.begin(), components.end(), [&](Component * c) {
                                     if(dynamic_cast<T*>(c))
                                     {
                                         return true;
                                     }
                                     return false;
                                 }));
        if(iterator != components.end()){
            return dynamic_cast<T*>(*iterator);

        }
        else return NULL;

    }

    void addComponent(Component *c);
    void addChild(GameObject *child);


    QString getName() const;
    void setName(const QString &value);

    GameObject *getParent() const;

    QVector3D getCenter() const;

protected:

    QString name;

    GameObject * parent;

    QVector3D center;

    QMatrix4x4 model;

    QVector<Component *> components;

    QVector<GameObject *> childs;

};


#endif // GAMEOBJECT_H
