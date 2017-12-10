#include "Component/vehiclecomponent.h"

VehicleComponent::VehicleComponent(GameObject * gameObject,Scene * _scene):
    Component(gameObject)
{
    scene = _scene;
    turnFactor = 45;
    accelerateFactor = 100;
    decelerateFactor = 70;

    elapsedTimer.start();

}

VehicleComponent::~VehicleComponent()
{

}

void VehicleComponent::accelerate()
{
    qDebug() << "accelerate" ;

    Rigidbody *body = gameObject->getComponent<Rigidbody>();
    QMatrix4x4 model = gameObject->getModelMatrix();
    Transform * trans = gameObject->getComponent<Transform>();
    QVector3D upVector = Utils::getUpVectorFromQuat(trans->getRotation());
    btVector3 btUpVector = btVector3(upVector.x(),upVector.y(),upVector.z());
    QVector3D center = model*gameObject->getCenter();
    btVector3 btCenter = btVector3(center.x(),center.y(),center.z());
    btVector3 begin = btCenter - btUpVector*3;

    btVector3 end = begin-btUpVector*4;


    btDynamicsWorld::ClosestRayResultCallback RayCallback(begin, end);
    btDynamicsWorld * world = scene->getWorld();
    world->rayTest(begin, end, RayCallback);
    if(onGround) {


        gameObject->getComponent<Rigidbody>()->activate(true);
        Transform *transform = gameObject->getComponent<Transform>();

        QQuaternion q = transform->getRotation();
        QVector3D forwardDirection = Utils::getForwardVectorFromQuat(q);
        forwardDirection *= accelerateFactor * 30;

        btVector3 force = btVector3(btScalar(forwardDirection.x()),btScalar(forwardDirection.y()),btScalar(forwardDirection.z()));
        gameObject->getComponent<Rigidbody>()->applyCentralForce(force);
    }
}

void VehicleComponent::decelerate()
{
    qDebug() << "decelerate" ;
    gameObject->getComponent<Rigidbody>()->activate(true);
    Transform *transform = gameObject->getComponent<Transform>();

    QQuaternion q = transform->getRotation();
    QVector3D backwardDirection = -Utils::getForwardVectorFromQuat(q);

    backwardDirection *= decelerateFactor;

    btVector3 force = btVector3(btScalar(backwardDirection.x()),btScalar(backwardDirection.y()),btScalar(backwardDirection.z()));
    gameObject->getComponent<Rigidbody>()->applyCentralImpulse(force);

}

void VehicleComponent::turnLeft()
{
    qDebug() << "turnLeft" ;
    gameObject->getComponent<Rigidbody>()->activate(true);
    Transform *transform = gameObject->getComponent<Transform>();

    QQuaternion q = transform->getRotation();
    QVector3D upVector = Utils::getUpVectorFromQuat(q);

    upVector*=turnFactor;

    gameObject->getComponent<Rigidbody>()->applyTorqueImpulse(btVector3(upVector.x(),upVector.y(),upVector.z()));
}

void VehicleComponent::turnRight()
{
    qDebug() << "turnRight" ;
    gameObject->getComponent<Rigidbody>()->activate(true);
    Transform *transform = gameObject->getComponent<Transform>();

    QQuaternion q = transform->getRotation();
    QVector3D upVector = Utils::getUpVectorFromQuat(q);

    upVector*=-turnFactor;


    // gameObject->getComponent<Rigidbody>()->applyTorque(btVector3(upVector.x(),upVector.y(),upVector.z()));
    gameObject->getComponent<Rigidbody>()->applyTorqueImpulse(btVector3(upVector.x(),upVector.y(),upVector.z()));
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
    float delta_time = elapsedTimer.elapsed()/1000.0f;
    qDebug() << delta_time;
    Rigidbody *body = gameObject->getComponent<Rigidbody>();
    body->activate(true);


    // Vecteurs de rays
    QVector3D QBegin[4];
    QBegin[0] = QVector3D(-1.f,-1.0f,1.f);
    QBegin[1] = QVector3D(1.f,-1.0f,1.f);
    QBegin[2] = QVector3D(-1.f,-1.0f,-1.f);
    QBegin[3] = QVector3D(1.f,-1.0f,-1.f);


    float dist = 0;
    float maxDist = 4;
    btVector3 begin;
    btVector3 end;
    QMatrix4x4 model = gameObject->getModelMatrix();
    Transform * trans = gameObject->getComponent<Transform>();
    QVector3D upVector = Utils::getUpVectorFromQuat(trans->getRotation());
    btVector3 btUpVector = btVector3(upVector.x(),upVector.y(),upVector.z());
    btVector3 force;
    onGround = false;
    for (int i=0;i<4;i++)
    {
        QVector3D QBeginD = model*QBegin[i];

        QVector3D QEnd = QBeginD-upVector*maxDist;
        begin = btVector3(QBeginD.x(),QBeginD.y(),QBeginD.z());
        end = btVector3(QEnd.x(),QEnd.y(),QEnd.z());

        btDynamicsWorld::ClosestRayResultCallback RayCallback(begin, end);
        btDynamicsWorld * world = scene->getWorld();
        world->rayTest(begin, end, RayCallback);
        if(RayCallback.hasHit()) {
            onGround = true;

            btVector3 hitPoint = RayCallback.m_hitPointWorld;

            btVector3 vel= body->getVelocityInLocalPoint(begin);
            btVector3 currentForce = btUpVector*btUpVector.dot(vel) ;


            dist = ((hitPoint.distance(begin)/(maxDist)));
            force = btUpVector * (-body->getGravity()/4/0.75)*(1-dist)/body->getInvMass(); // compression force
            //force = btUpVector * (1-dist) * 50; // compression force
            force -= currentForce;

            body->applyForce(force,begin);
            qDebug() << "Ray "<<i<<" Hit: " << currentForce.x()<< " " << currentForce.y() << " "  << currentForce.z() << " "<< dist ;
        }


    }



    elapsedTimer.restart();
}
