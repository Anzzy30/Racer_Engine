#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include <QVector3D>
#include "Component/component.h"
#include "Component/transform.h"
#include "GameObject/gameobject.h"
class Component;
class Rigidbody : public Component
{
public:
    Rigidbody(GameObject * gameObject);
    ~Rigidbody();
    void applyForce(QVector3D);
    virtual void update();
private:
    Transform* transform;

};

#endif // RIGIDBODY_H
