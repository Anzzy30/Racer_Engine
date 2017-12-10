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

    QQuaternion q = transform->getRotation();
    QVector3D forwardDirection = Utils::getForwardVectorFromQuat(q);
    forwardDirection *= accelerateFactor;
    btVector3 force = btVector3(btScalar(forwardDirection.x()),btScalar(forwardDirection.y()),btScalar(forwardDirection.z()));
    gameObject->getComponent<Rigidbody>()->applyCentralImpulse(force);

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

    Rigidbody *body = gameObject->getComponent<Rigidbody>();
    body->activate(true);
    // Vecteurs de rays
    QVector3D QBegin[4];
    QBegin[0] = QVector3D(-1.f,-1.0f,1.f);
    QBegin[1] = QVector3D(1.f,-1.0f,1.f);
    QBegin[2] = QVector3D(-1.f,-1.0f,-1.f);
    QBegin[3] = QVector3D(1.f,-1.0f,-1.f);


    float dist = 0;
    float maxDist = 8;
    btVector3 begin;
    btVector3 End;
    QMatrix4x4 model = gameObject->getModelMatrix();
    Transform * trans = gameObject->getComponent<Transform>();
    QVector3D upVector = Utils::getUpVectorFromQuat(trans->getRotation());
    btVector3 btUpVector = btVector3(upVector.x(),upVector.y(),upVector.z());
    btVector3 force;

    for (int i=0;i<4;i++)
    {
        QVector3D QBeginD = model*QBegin[i];

        QVector3D QEnd = QBeginD-upVector*maxDist;
        begin = btVector3(QBeginD.x(),QBeginD.y(),QBeginD.z());
        End = btVector3(QEnd.x(),QEnd.y(),QEnd.z());

        btVector3 vel= body->getVelocityInLocalPoint(begin);

        btDynamicsWorld::ClosestRayResultCallback RayCallback(begin, End);
        btDynamicsWorld * world = scene->getWorld();
        world->rayTest(begin, End, RayCallback);
        if(RayCallback.hasHit()) {
            btVector3 hitPoint = RayCallback.m_hitPointWorld;
            dist = hitPoint.distance(begin)/maxDist;
            force = btUpVector * (-body->getGravity()/4/0.75)*(1-dist);
            body->applyDamping(0.5);
            body->applyForce(force,btVector3(QBegin[i].x(),QBegin[i].y(),QBegin[i].z()));

            qDebug() << "Ray "<<i<<" Hit: " << force.x() << force.y() << force.z() << 1-dist;

        }


    }

}
