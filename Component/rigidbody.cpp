#include "Component/rigidbody.h"


Rigidbody::Rigidbody(GameObject *gameObject):
    Component(gameObject)
{
    transform = gameObject->getComponent<Transform>();
    velocity = QVector3D(0,0,0);
    angularVelocity = QVector3D(0,0,0);
    elapsedTimer.start();
    applyForce(QVector3D(0,50,0),gameObject->getModelMatrix()*gameObject->getCenter());

}

Rigidbody::~Rigidbody()
{

}
void Rigidbody::applyForce(QVector3D force,QVector3D point)
{

    //QVector3D acceleration = force / mass;

    QVector3D momentum = force  * delta_time ;
    QVector3D torque = QVector3D::crossProduct(point - gameObject->getModelMatrix()*gameObject->getCenter(),force);
    torque.normalize();

    float inertia = 1.0f/6.0f * mass;

    QVector3D angularMomentum = torque*delta_time;

    angularVelocity += angularMomentum/inertia;
    velocity += momentum/mass;
}

void Rigidbody::deleteThisPLZ()
{
    QVector3D v1 = QVector3D(1.000000, -1.000000, -1.000000);
    QVector3D v2 = QVector3D(1.000000, -1.000000, 1.000000);
    QVector3D v3 = QVector3D(-1.000000, -1.000000, 1.000000);
    QVector3D v4 = QVector3D(-1.000000, -1.000000, -1.000000);
    QVector3D v5 = QVector3D(1.000000, 1.000000, -1.000000);
    QVector3D v6 = QVector3D(1.000000, 1.000000, 1.000000);
    QVector3D v7 = QVector3D(-1.000000, 1.000000, 1.000000);
    QVector3D v8 = QVector3D(-1.000000, 1.000000, -1.000000);
    QVector3D vx = gameObject->getCenter();

    QMatrix4x4 model = gameObject->getModelMatrix();



    v1 = model*v1;
    v2 = model*v2;
    v3 = model*v3;
    v4 = model*v4;
    v5 = model*v5;
    v6 = model*v6;
    v7 = model*v7;
    v8 = model*v8;
    vx = model*vx;

    QVector3D v11 = v1;
    QVector3D v22 = v2;
    QVector3D v33 = v3;
    QVector3D v44 = v4;
    QVector3D v55 = v5;
    QVector3D v66 = v6;
    QVector3D v77 = v7;
    QVector3D v88 = v8;




    if(v1.y() < 0){
        QVector3D force =( vx-v11).normalized();
        force*=-v1.y()*10;
        qDebug() << v1.y();
        applyForce(force,v11);
    }

    if(v2.y() < 0){
        QVector3D force =( vx-v22).normalized();
        force*=-v2.y()*10;
        qDebug() << v1.y();
        applyForce(force,v22);
    }
    if(v3.y() < 0){
        QVector3D force =(vx-v33).normalized();
        force*=-v3.y()*10;
        qDebug() << v1.y();
        applyForce(force,v33);
    }
    if(v4.y() < 0){
        QVector3D force =(vx-v44).normalized();
        force*=-v4.y()*10;
        qDebug() << v1.y();
        applyForce(force,v44);
    }
    if(v5.y() < 0){
        QVector3D force =(vx-v55).normalized();
        force*=-v5.y()*10;
        qDebug() << v1.y();
        applyForce(force,v55);
    }
    if(v6.y() < 0){
        QVector3D force =(vx-v66).normalized();
        force*=-v6.y()*10;
        qDebug() << v1.y();
        applyForce(force,v66);
    }
    if(v7.y() < 0){
        QVector3D force =(vx-v77).normalized();
        force*=-v7.y()*10;
        qDebug() << v1.y();
        applyForce(force,v77);
    }

    if(v8.y() < 0){
        QVector3D force =(vx-v88).normalized();
        force*=-v8.y()*01;
        qDebug() << v1.y();
        applyForce(force,v88);
    }
}


void Rigidbody::update()
{
    applyForce(QVector3D(0,-1,0),gameObject->getModelMatrix()*gameObject->getCenter());
    deleteThisPLZ();
    delta_time = elapsedTimer.elapsed()/1000.0f;

    QQuaternion q = QQuaternion( 0,
                                 angularVelocity.x(),
                                 angularVelocity.y(),
                                 angularVelocity.z());
    spin = 0.5f * q * transform->getRotation().normalized();

    transform->setPosition(transform->getPosition()+velocity);
    transform->setRotation((transform->getRotation().normalized()+spin).normalized());

    elapsedTimer.restart();
}


