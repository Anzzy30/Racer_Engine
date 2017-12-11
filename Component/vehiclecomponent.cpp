#include "Component/vehiclecomponent.h"

VehicleComponent::VehicleComponent(GameObject * gameObject,Scene * _scene):
    Component(gameObject)
{
    scene = _scene;
    turnFactor = 45;
    accelerateFactor = 500;
    decelerateFactor = 400;

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

    if(onGround) {


        gameObject->getComponent<Rigidbody>()->activate(true);
        Transform *transform = gameObject->getComponent<Transform>();

        QQuaternion q = transform->getRotation();
        QVector3D forwardDirection = Utils::getForwardVectorFromQuat(q);

        QVector3D ptsAvant = center + forwardDirection * trans->getScale()/2 - upVector*trans->getScale()/2;
        qDebug()<<ptsAvant <<center;
        btVector3 btAvant = btVector3(ptsAvant.x(),ptsAvant.y(),ptsAvant.z());
        forwardDirection *= accelerateFactor/body->getInvMass();

        body->setDamping(0,0);
        btVector3 force = btVector3(btScalar(forwardDirection.x()),btScalar(forwardDirection.y()),btScalar(forwardDirection.z()));
        btTransform transCenterMass = body->getCenterOfMassTransform();
        btTransform transCenterMassSwitch;
        btVector3 scale = btVector3(trans->getScale().x(),trans->getScale().y(),trans->getScale().z());
        transCenterMassSwitch.setOrigin(btCenter - btUpVector*scale*2);
        body->setCenterOfMassTransform(transCenterMassSwitch);
        gameObject->getComponent<Rigidbody>()->applyCentralForce(force);
        body->setCenterOfMassTransform(transCenterMass);
    }
}

void VehicleComponent::decelerate()
{
    qDebug() << "decelerate" ;

    Rigidbody *body = gameObject->getComponent<Rigidbody>();
    QMatrix4x4 model = gameObject->getModelMatrix();
    Transform * trans = gameObject->getComponent<Transform>();
    QVector3D upVector = Utils::getUpVectorFromQuat(trans->getRotation());
    btVector3 btUpVector = btVector3(upVector.x(),upVector.y(),upVector.z());
    QVector3D center = model*gameObject->getCenter();
    btVector3 btCenter = btVector3(center.x(),center.y(),center.z());
    btVector3 begin = btCenter - btUpVector*3;

    btVector3 end = begin-btUpVector*4;

    if(onGround) {


        gameObject->getComponent<Rigidbody>()->activate(true);
        Transform *transform = gameObject->getComponent<Transform>();

        QQuaternion q = transform->getRotation();
        QVector3D forwardDirection = Utils::getForwardVectorFromQuat(q);

        forwardDirection *= -decelerateFactor/body->getInvMass();

        btVector3 force = btVector3(btScalar(forwardDirection.x()),btScalar(forwardDirection.y()),btScalar(forwardDirection.z()));

        btTransform transCenterMass = body->getCenterOfMassTransform();
        btTransform transCenterMassSwitch;
        btVector3 scale = btVector3(trans->getScale().x(),trans->getScale().y(),trans->getScale().z());
        transCenterMassSwitch.setOrigin(btCenter - btUpVector*scale*2);
        body->setCenterOfMassTransform(transCenterMassSwitch);
        gameObject->getComponent<Rigidbody>()->applyCentralForce(force);
        body->setCenterOfMassTransform(transCenterMass);
    }
}

void VehicleComponent::turnLeft()
{
    qDebug() << "turnLeft" ;
    gameObject->getComponent<Rigidbody>()->activate(true);
    Transform *transform = gameObject->getComponent<Transform>();

    Rigidbody *body = gameObject->getComponent<Rigidbody>();
    QMatrix4x4 model = gameObject->getModelMatrix();
    Transform * trans = gameObject->getComponent<Transform>();
    QVector3D upVector = Utils::getUpVectorFromQuat(trans->getRotation());
    QVector3D center = model*gameObject->getCenter();

    QQuaternion q = transform->getRotation();
    QVector3D forwardDirection = Utils::getForwardVectorFromQuat(q);
    QVector3D strafe = QVector3D::crossProduct(upVector,forwardDirection);
    btVector3 vel = body->getVelocityInLocalPoint(body->getCenterOfMassPosition());
    QVector3D back = center - forwardDirection * trans->getScale() + strafe* trans->getScale()- upVector * trans->getScale();
    btVector3 btBack = btVector3(back.x(),back.y(),back.z());

    //strafe*=turnFactor*10;

    btVector3 btStrafe = btVector3(strafe.x(),strafe.y(),strafe.z());
    btVector3 opositeForce = vel*btStrafe;
    gameObject->getComponent<Rigidbody>()->applyCentralForce(opositeForce);

    upVector*=turnFactor*5000;
    gameObject->getComponent<Rigidbody>()->applyTorque(btVector3(upVector.x(),upVector.y(),upVector.z()));

}

void VehicleComponent::turnRight()
{
    qDebug() << "turnRight" ;
    gameObject->getComponent<Rigidbody>()->activate(true);
    Transform *transform = gameObject->getComponent<Transform>();

    Rigidbody *body = gameObject->getComponent<Rigidbody>();
    QMatrix4x4 model = gameObject->getModelMatrix();
    Transform * trans = gameObject->getComponent<Transform>();
    QVector3D upVector = Utils::getUpVectorFromQuat(trans->getRotation());
    QVector3D center = model*gameObject->getCenter();

    QQuaternion q = transform->getRotation();
    QVector3D forwardDirection = Utils::getForwardVectorFromQuat(q);
    QVector3D strafe = QVector3D::crossProduct(upVector,forwardDirection);
    btVector3 vel = body->getVelocityInLocalPoint(body->getCenterOfMassPosition());
    QVector3D back = center - forwardDirection * trans->getScale() + strafe* trans->getScale()- upVector * trans->getScale();
    btVector3 btBack = btVector3(back.x(),back.y(),back.z());

    //strafe*=turnFactor*10;

    btVector3 btStrafe = btVector3(strafe.x(),strafe.y(),strafe.z());
    btVector3 opositeForce = vel*btStrafe;
    gameObject->getComponent<Rigidbody>()->applyCentralForce(opositeForce);

    upVector*=-turnFactor*5000;
    gameObject->getComponent<Rigidbody>()->applyTorque(btVector3(upVector.x(),upVector.y(),upVector.z()));
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
    Rigidbody *body = gameObject->getComponent<Rigidbody>();
    body->activate(true);


    // Vecteurs de rays
    QVector3D QBegin[4];
    QBegin[0] = QVector3D(-1.f,-1.f,1.f);
    QBegin[1] = QVector3D(1.f,-1.f,1.f);
    QBegin[2] = QVector3D(-1.f,-1.f,-1.f);
    QBegin[3] = QVector3D(1.f,-1.f,-1.f);


    float dist = 0;
    float maxDist = 4;
    btVector3 begin;
    btVector3 end;
    QMatrix4x4 model = gameObject->getModelMatrix();
    Transform * trans = gameObject->getComponent<Transform>();
    QVector3D upVector = Utils::getUpVectorFromQuat(trans->getRotation());
    btVector3 btUpVector = btVector3(upVector.x(),upVector.y(),upVector.z());
    btVector3 force;
    btTransform centerTranform ;
    onGround = false;
    //0.5 0.8 ok
    for (int i=0;i<4;i++)
    {

        QVector3D QBeginD = model*QBegin[i];

        QVector3D QEnd = QBeginD-upVector*maxDist;
        begin = btVector3(QBeginD.x(),QBeginD.y(),QBeginD.z());
        end = btVector3(QEnd.x(),QEnd.y(),QEnd.z());

        btDynamicsWorld::AllHitsRayResultCallback RayCallback(begin, end);
        btDynamicsWorld * world = scene->getWorld();
        world->rayTest(begin, end, RayCallback);
        bool hasHitOther = false;
        if(RayCallback.hasHit()) {
            body->setDamping(0.5,0.5);
            body->applyDamping(0.05);

            int j;
            for(j=0;j<RayCallback.m_hitPointWorld.size();++j){
                if(RayCallback.m_collisionObjects.at(j) != body){
                    hasHitOther = true;
                    break;
                }
            }
            if(hasHitOther){
                onGround = true;
                btVector3 hitPoint = RayCallback.m_hitPointWorld.at(j);
                btVector3 vel= body->getVelocityInLocalPoint(btVector3(QBegin[i].x()*trans->getPosition().x(),QBegin[i].y()*trans->getPosition().y(),QBegin[i].z()*trans->getPosition().z()));;
                btVector3 currentForce = btUpVector*btUpVector.dot(vel) ;
                dist = ((hitPoint.distance(begin)/(maxDist)));
                force = btUpVector * (-body->getGravity()/4/0.75)*(1-dist) / body->getInvMass(); // compression force

                body->applyCentralForce(force);
                qDebug() << "Ray "<<i<<" Hit: " << force.x()<< " " << force.y() << " "  << force.z() << " "<< dist ;

            }
        }


    }

    body->setDamping(0,0);


    elapsedTimer.restart();
}
