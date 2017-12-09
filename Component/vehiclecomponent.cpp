#include "Component/vehiclecomponent.h"

VehicleComponent::VehicleComponent(GameObject * gameObject,Scene * _scene):
    Component(gameObject)
{
    scene = _scene;
    turnFactor = 45;
    accelerateFactor = 100;
    decelerateFactor = 70;
}

VehicleComponent::~VehicleComponent()
{

}

void VehicleComponent::accelerate()
{
    qDebug() << "accelerate" ;


    gameObject->getComponent<Rigidbody>()->activate(true);
    Transform *transform = gameObject->getComponent<Transform>();
<<<<<<< HEAD
    QVector3D forwardDirection= transform->getRotation()*forwardVector;
    forwardDirection.normalize();
    btVector3 force = btVector3(btScalar(forwardDirection.x()*400),btScalar(forwardDirection.y()*400),btScalar(forwardDirection.z()*400));
    gameObject->getComponent<Rigidbody>()->applyCentralForce(force);
=======

    QQuaternion q = transform->getRotation();
    QVector3D forwardDirection = Utils::getForwardVectorFromQuat(q);
    forwardDirection *= accelerateFactor;
    btVector3 force = btVector3(btScalar(forwardDirection.x()),btScalar(forwardDirection.y()),btScalar(forwardDirection.z()));
    gameObject->getComponent<Rigidbody>()->applyCentralImpulse(force);
>>>>>>> d3290940084878898fd9db9eb4ea73c5e0568677
}

void VehicleComponent::decelerate()
{
    qDebug() << "decelerate" ;
    gameObject->getComponent<Rigidbody>()->activate(true);
    Transform *transform = gameObject->getComponent<Transform>();
<<<<<<< HEAD
    QVector3D forwardDirection= transform->getRotation()*forwardVector;
    forwardDirection.normalize();
    btVector3 force = btVector3(btScalar(forwardDirection.x()*400),btScalar(forwardDirection.y()*400),btScalar(forwardDirection.z()*400));
    gameObject->getComponent<Rigidbody>()->applyCentralForce(force);
=======

    QQuaternion q = transform->getRotation();
    QVector3D backwardDirection = -Utils::getForwardVectorFromQuat(q);

    backwardDirection *= decelerateFactor;

    btVector3 force = btVector3(btScalar(backwardDirection.x()),btScalar(backwardDirection.y()),btScalar(backwardDirection.z()));
    gameObject->getComponent<Rigidbody>()->applyCentralImpulse(force);
>>>>>>> d3290940084878898fd9db9eb4ea73c5e0568677

}

void VehicleComponent::turnLeft()
{
    qDebug() << "turnLeft" ;
    gameObject->getComponent<Rigidbody>()->activate(true);
<<<<<<< HEAD
    gameObject->getComponent<Rigidbody>()->applyTorque(btVector3(0,100,0));
=======
    Transform *transform = gameObject->getComponent<Transform>();

    QQuaternion q = transform->getRotation();
    QVector3D upVector = Utils::getUpVectorFromQuat(q);

    upVector*=turnFactor;

    gameObject->getComponent<Rigidbody>()->applyTorqueImpulse(btVector3(upVector.x(),upVector.y(),upVector.z()));
>>>>>>> d3290940084878898fd9db9eb4ea73c5e0568677
}

void VehicleComponent::turnRight()
{
    qDebug() << "turnRight" ;
    gameObject->getComponent<Rigidbody>()->activate(true);
<<<<<<< HEAD
    gameObject->getComponent<Rigidbody>()->applyTorque(btVector3(0,-100,0));
=======
    Transform *transform = gameObject->getComponent<Transform>();

    QQuaternion q = transform->getRotation();
    QVector3D upVector = Utils::getUpVectorFromQuat(q);

    upVector*=-turnFactor;


   // gameObject->getComponent<Rigidbody>()->applyTorque(btVector3(upVector.x(),upVector.y(),upVector.z()));
    gameObject->getComponent<Rigidbody>()->applyTorqueImpulse(btVector3(upVector.x(),upVector.y(),upVector.z()));
>>>>>>> d3290940084878898fd9db9eb4ea73c5e0568677
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
    gameObject->getComponent<Rigidbody>()->activate(true);
    // Vecteurs de rays
    QVector3D QBegin1(-1.f,-.9f,1.f);
    QVector3D QBegin2(1.f,-.9f,1.f);
    QVector3D QBegin3(-1.f,-.9f,-1.f);
    QVector3D QBegin4(1.f,-.9f,-1.f);
    float dist = 0;

    btVector3 Begin;
    btVector3 End;
    QMatrix4x4 model = gameObject->getModelMatrix();

    /// PREMIER VECTEUR

    QVector3D QBeginD = model*QBegin1;
    Begin = btVector3(QBeginD.x(),QBeginD.y(),QBeginD.z());
    End = btVector3(QBeginD.x(),QBeginD.y()-5.f,QBeginD.z());


    btDynamicsWorld::ClosestRayResultCallback RayCallback(Begin, End);
    btDynamicsWorld * world = scene->getWorld();


    world->rayTest(Begin, End, RayCallback);
    if(RayCallback.hasHit()) {
        btVector3 End2 = RayCallback.m_hitPointWorld;
        dist = End2.distance(Begin);
        dist = 1.1-(dist / End.distance(Begin));
        gameObject->getComponent<Rigidbody>()->applyForce(btVector3(0,80*dist,0),btVector3(QBegin1.x(),QBegin1.y(),QBegin1.z()));

        btVector3 Normal = RayCallback.m_hitNormalWorld;
        qDebug() << "Ray 1 salut"<<QBeginD<< dist;

        // Do some clever stuff here
    }

    /// SECOND VECTEUR

    QBeginD = model*QBegin2;
    Begin = btVector3(QBeginD.x(),QBeginD.y(),QBeginD.z());
    End = btVector3(QBeginD.x(),QBeginD.y()-5.f,QBeginD.z());
    RayCallback = btDynamicsWorld::ClosestRayResultCallback(Begin, End);


    world->rayTest(Begin, End, RayCallback);
    if(RayCallback.hasHit()) {
        btVector3 End2 = RayCallback.m_hitPointWorld;
        dist = End2.distance(Begin);
        dist = 1.1-(dist / End.distance(Begin));
        gameObject->getComponent<Rigidbody>()->applyForce(btVector3(0,80*dist,0),btVector3(QBegin2.x(),QBegin2.y(),QBegin2.z()));

        btVector3 Normal = RayCallback.m_hitNormalWorld;
        qDebug() << "Ray 2 salut"<<QBeginD<< dist;
        // Do some clever stuff here
    }

    /// TROISIEME VECTEUR
    QBeginD = model*QBegin3;
    Begin = btVector3(QBeginD.x(),QBeginD.y(),QBeginD.z());
    End = btVector3(QBeginD.x(),QBeginD.y()-5.f,QBeginD.z());
    RayCallback = btDynamicsWorld::ClosestRayResultCallback(Begin, End);


    world->rayTest(Begin, End, RayCallback);
    if(RayCallback.hasHit()) {
        btVector3 End2 = RayCallback.m_hitPointWorld;
        dist = End2.distance(Begin);
        dist = 1.1-(dist / End.distance(Begin));
        gameObject->getComponent<Rigidbody>()->applyForce(btVector3(0,80*dist,0),btVector3(QBegin3.x(),QBegin3.y(),QBegin3.z()));

        btVector3 Normal = RayCallback.m_hitNormalWorld;
        qDebug() << "Ray 3 salut"<<QBeginD<< dist;

        // Do some clever stuff here
    }

    /// QUATRIEME VECTEUR
    QBeginD = model*QBegin4;
    Begin = btVector3(QBeginD.x(),QBeginD.y(),QBeginD.z());
    End = btVector3(QBeginD.x(),QBeginD.y()-5.f,QBeginD.z());
    RayCallback = btDynamicsWorld::ClosestRayResultCallback(Begin, End);


    world->rayTest(Begin, End, RayCallback);
    if(RayCallback.hasHit()) {
        btVector3 End2 = RayCallback.m_hitPointWorld;
        dist = End2.distance(Begin);
        dist = 1.1-(dist / End.distance(Begin));
        gameObject->getComponent<Rigidbody>()->applyForce(btVector3(0,80*dist,0),btVector3(QBegin4.x(),QBegin4.y(),QBegin4.z()));

        btVector3 Normal = RayCallback.m_hitNormalWorld;
        qDebug() << "Ray 4 salut"<<QBeginD<< dist;

        // Do some clever stuff here
    }

}
