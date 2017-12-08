#include "Component/rigidbody.h"


Rigidbody::Rigidbody(GameObject *gameObject, btRigidBody::btRigidBodyConstructionInfo rbInfo):
    Component(gameObject), btRigidBody(rbInfo)
{
}

Rigidbody::~Rigidbody()
{

}

void Rigidbody::update()
{

}
