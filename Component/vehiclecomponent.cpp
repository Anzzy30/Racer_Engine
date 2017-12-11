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

    if(onGround || true) {


        gameObject->getComponent<Rigidbody>()->activate(true);
        Transform *transform = gameObject->getComponent<Transform>();

        QQuaternion q = transform->getRotation();
        QVector3D forwardDirection = Utils::getForwardVectorFromQuat(q);

        QVector3D ptsAvant = center + forwardDirection * trans->getScale();
        qDebug()<<ptsAvant <<center;
        btVector3 btAvant = btVector3(ptsAvant.x(),ptsAvant.y(),ptsAvant.z());
        forwardDirection *= accelerateFactor*70;

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
    QBegin[0] = QVector3D(-1.f,-0.9f,1.f);
    QBegin[1] = QVector3D(1.f,-0.9f,1.f);
    QBegin[2] = QVector3D(-1.f,-0.9f,-1.f);
    QBegin[3] = QVector3D(1.f,-0.9f,-1.f);


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
    body->setDamping(0.5,0.8);
    body->applyDamping(0.05);
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
        //body->setContactStiffnessAndDamping(0.02,0.02);
        if(RayCallback.hasHit()) {
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

                btTransform transCenterMass = body->getCenterOfMassTransform();
                btTransform transCenterMassSwitch;
                transCenterMassSwitch.setOrigin(begin);
                //body->setCenterOfMassTransform(transCenterMassSwitch);
                body->applyCentralForce(force);
                qDebug() << "Ray "<<i<<" Hit: " << force.x()<< " " << force.y() << " "  << force.z() << " "<< dist ;
                //body->setCenterOfMassTransform(transCenterMass);

            }
        }


    }



    elapsedTimer.restart();
}
