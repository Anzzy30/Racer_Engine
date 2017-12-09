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
    // Vecteurs de rays
    QVector3D QBegin1(-6.f,-1.f,6.f);
    QVector3D QBegin2(6.f,-1.f,6.f);
    QVector3D QBegin3(-6.f,-1.f,-6.f);
    QVector3D QBegin4(6.f,-1.f,-6.f);
    float dist = 0;

    btVector3 Begin;
    btVector3 End;
    QMatrix4x4 model = gameObject->getModelMatrix();

    /// PREMIER VECTEUR

    QVector3D QBeginD = model*QBegin1;
    Begin = btVector3(QBeginD.x(),QBeginD.y(),QBeginD.z());
    End = btVector3(QBeginD.x(),QBeginD.y()-5,QBeginD.z());


    btDiscreteDynamicsWorld::ClosestRayResultCallback RayCallback(Begin, End);
    btDiscreteDynamicsWorld * world = scene->getWorld();


    world->rayTest(Begin, End, RayCallback);
    if(RayCallback.hasHit()) {
        btVector3 End2 = RayCallback.m_hitPointWorld;
        dist = End2.distance(Begin);
        dist = dist / End.distance(Begin);
        gameObject->getComponent<Rigidbody>()->applyForce(btVector3(0,200*(1/dist),0),btVector3(QBegin1.x(),QBegin1.y(),QBegin1.z()));

        btVector3 Normal = RayCallback.m_hitNormalWorld;
        qDebug() << "Ray 1 salut";

        // Do some clever stuff here
    }

    /// SECOND VECTEUR
    QBeginD = model*QBegin2;
    Begin = btVector3(QBeginD.x(),QBeginD.y(),QBeginD.z());
    End = btVector3(QBeginD.x(),QBeginD.y()-5,QBeginD.z());


    world->rayTest(Begin, End, RayCallback);
    if(RayCallback.hasHit()) {
        btVector3 End2 = RayCallback.m_hitPointWorld;
        dist = End2.distance(Begin);
        dist = dist / End.distance(Begin);
        gameObject->getComponent<Rigidbody>()->applyForce(btVector3(0,200*(1/dist),0),btVector3(QBegin2.x(),QBegin2.y(),QBegin2.z()));

        btVector3 Normal = RayCallback.m_hitNormalWorld;
        qDebug() << "Ray 2 salut";

        // Do some clever stuff here
    }

    /// TROISIEME VECTEUR
    QBeginD = model*QBegin3;
    Begin = btVector3(QBeginD.x(),QBeginD.y(),QBeginD.z());
    End = btVector3(QBeginD.x(),QBeginD.y()-5,QBeginD.z());


    world->rayTest(Begin, End, RayCallback);
    if(RayCallback.hasHit()) {
        btVector3 End2 = RayCallback.m_hitPointWorld;
        dist = End2.distance(Begin);
        dist = dist / End.distance(Begin);
        gameObject->getComponent<Rigidbody>()->applyForce(btVector3(0,200*(1/dist),0),btVector3(QBegin3.x(),QBegin3.y(),QBegin3.z()));

        btVector3 Normal = RayCallback.m_hitNormalWorld;
        qDebug() << "Ray 3 salut";

        // Do some clever stuff here
    }

    /// QUATRIEME VECTEUR
    QBeginD = model*QBegin4;
    Begin = btVector3(QBeginD.x(),QBeginD.y(),QBeginD.z());
    End = btVector3(QBeginD.x(),QBeginD.y()-5,QBeginD.z());


    world->rayTest(Begin, End, RayCallback);
    if(RayCallback.hasHit()) {
        btVector3 End2 = RayCallback.m_hitPointWorld;
        dist = End2.distance(Begin);
        dist = dist / End.distance(Begin);
        gameObject->getComponent<Rigidbody>()->applyForce(btVector3(0,200*(1/dist),0),btVector3(QBegin4.x(),QBegin4.y(),QBegin4.z()));

        btVector3 Normal = RayCallback.m_hitNormalWorld;
        qDebug() << "Ray 4 salut";

        // Do some clever stuff here
    }

}