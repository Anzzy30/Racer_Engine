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
    btTransform trans = this->getWorldTransform();

    if (this->getMotionState())
    {
        this->getMotionState()->getWorldTransform(trans);
    }
    else
    {
        trans = this->getWorldTransform();
    }
    Transform *transform = gameObject->getComponent<Transform>();
    transform->setPosition(QVector3D(trans.getOrigin().getX(),trans.getOrigin().getY(),trans.getOrigin().getZ()));
    transform->setRotation(QQuaternion(trans.getRotation().getW(),QVector3D(trans.getRotation().getX(),trans.getRotation().getY(),trans.getRotation().getZ())));
}
