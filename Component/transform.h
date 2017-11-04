#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QVector3D>
#include <QQuaternion>

#include "Component/component.h"

class Component;

class Transform : public Component
{
public:
    Transform(GameObject * gameObject);

    Transform(GameObject * gameObject,QVector3D position,QQuaternion rotation,QVector3D scale);
    Transform(const Transform*);

    ~Transform();
    QVector3D getPosition() const;
    QQuaternion getRotation() const;
    QVector3D getScale() const;

    void setPosition(const QVector3D &value);
    void setRotation(const QQuaternion &value);
    void setScale(const QVector3D &value);

    virtual void update();
private:

    QVector3D position;
    QQuaternion rotation;
    QVector3D scale;


};

#endif // TRANSFORM_H
