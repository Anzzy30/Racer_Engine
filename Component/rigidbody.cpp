#include "Component/rigidbody.h"


Rigidbody::Rigidbody(GameObject *gameObject):
Component(gameObject)
{
    transform = gameObject->getComponent<Transform>();
}

Rigidbody::~Rigidbody()
{

}

void Rigidbody::applyForce(QVector3D)
{

}

void Rigidbody::update()
{

}
