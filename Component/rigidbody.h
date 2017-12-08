#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include "external\bullet3-2.87\src\btBulletDynamicsCommon.h"
#include "GameObject/gameobject.h"

class Component;


class Rigidbody : public Component, public btRigidBody
{
public:
    Rigidbody(GameObject * gameObject, btRigidBodyConstructionInfo rbInfo);
    ~Rigidbody();

    void update();
};

#endif // RIGIDBODY_H
