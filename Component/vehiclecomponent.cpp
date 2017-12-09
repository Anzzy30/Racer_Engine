#include "Component/vehiclecomponent.h"

VehicleComponent::VehicleComponent(GameObject * gameObject,Scene * _scene):
    Component(gameObject)
{
scene = _scene;
}

VehicleComponent::~VehicleComponent()
{

}

void VehicleComponent::accelerate()
{
    qDebug() << "accelerate" ;
    gameObject->getComponent<Rigidbody>()->activate(true);
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
    gameObject->getComponent<Rigidbody>()->activate(true);
    QVector3D forwardVector = QVector3D(0,0,-1);
    Transform *transform = gameObject->getComponent<Transform>();
    QVector3D forwardDirection= transform->getRotation()*forwardVector;
    forwardDirection.normalize();
    btVector3 force = btVector3(btScalar(forwardDirection.x()*100),btScalar(forwardDirection.y()*100),btScalar(forwardDirection.z()*100));
    gameObject->getComponent<Rigidbody>()->applyCentralForce(force);

}

void VehicleComponent::turnLeft()
{
    qDebug() << "turnLeft" ;
    gameObject->getComponent<Rigidbody>()->activate(true);
    gameObject->getComponent<Rigidbody>()->applyTorque(btVector3(0,20,0));
}

void VehicleComponent::turnRight()
{
    qDebug() << "turnRight" ;
    gameObject->getComponent<Rigidbody>()->activate(true);
    gameObject->getComponent<Rigidbody>()->applyTorque(btVector3(0,-20,0));
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

    btVector3 Begin(0.f,0.f,0.f);
    QVector3D QBegin(0,0,0);
    QMatrix4x4 model = gameObject->getModelMatrix();
    QBegin = model*QBegin;
    Begin = btVector3(QBegin.x(),QBegin.y(),QBegin.z());
    btVector3 End(QBegin.x(),QBegin.y()-5,QBegin.z());

    btDiscreteDynamicsWorld::ClosestRayResultCallback RayCallback(Begin, End);
    btDiscreteDynamicsWorld * world = scene->getWorld();


    world->rayTest(Begin, End, RayCallback);
    if(RayCallback.hasHit()) {
        btVector3 End2 = RayCallback.m_hitPointWorld;
        gameObject->getComponent<Rigidbody>()->applyCentralForce(btVector3(0,80,0));

        btVector3 Normal = RayCallback.m_hitNormalWorld;
        qDebug() << "N A N I ?!";

        // Do some clever stuff here
    }

}
