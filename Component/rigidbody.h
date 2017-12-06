#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include <QVector3D>
#include "Component/component.h"
class Component;
class Rigidbody:public Component
{
public:
    Rigidbody();
    ~Rigidbody();
    void applyForce(QVector3D);
    virtual void update();

};

#endif // RIGIDBODY_H
