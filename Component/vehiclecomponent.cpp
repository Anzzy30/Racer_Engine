#include "Component/vehiclecomponent.h"

VehicleComponent::VehicleComponent(GameObject * gameObject):
    Component(gameObject)
{

}

VehicleComponent::~VehicleComponent()
{

}

void VehicleComponent::accelerate()
{
    qDebug() << "accelerate" ;
    QVector3D forwardVector = QVector3D(0,0,1);
    Transform *transform = gameObject->getComponent<Transform>();
    QVector3D forwardDirection= transform->getRotation()*forwardVector;
    forwardDirection.normalize();
    btVector3 force = btVector3(btScalar(forwardDirection.x()*100),btScalar(forwardDirection.y()*100),btScalar(forwardDirection.z()*100));
    gameObject->getComponent<Rigidbody>()->applyCentralForce(force);
}

void VehicleComponent::decelerate()
{
    qDebug() << "decelerate" ;
}

void VehicleComponent::turnLeft()
{
    qDebug() << "turnLeft" ;
}

void VehicleComponent::turnRight()
{
    qDebug() << "turnRight" ;
}

void VehicleComponent::actionKey()
{
    qDebug() << "actionKey" ;
}

void VehicleComponent::boostKey()
{
    qDebug() << "boostKey" ;
}
void VehicleComponent::update()
{
}
