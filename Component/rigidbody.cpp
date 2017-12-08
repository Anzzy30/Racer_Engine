#include "Component/rigidbody.h"


Rigidbody::Rigidbody(GameObject *gameObject):
    Component(gameObject)
{
    transform = gameObject->getComponent<Transform>();
    velocity = QVector3D(0,0,0);
    angularVelocity = QVector3D(0,0,0);
    elapsedTimer.start();
    QVector3D v1 = QVector3D(1.000000, -1.000000, -1.000000);
    QVector3D v2 = QVector3D(1.000000, -1.000000, 1.000000);
    QVector3D v3 = QVector3D(-1.000000, -1.000000, 1.000000);
    QVector3D v4 = QVector3D(-1.000000, -1.000000, -1.000000);
    QVector3D v5 = QVector3D(1.000000, 1.000000, -1.000000);
    QVector3D v6 = QVector3D(1.000000, 1.000000, 1.000000);
    QVector3D v7 = QVector3D(-1.000000, 1.000000, 1.000000);
    QVector3D v8 = QVector3D(-1.000000, 1.000000, -1.000000);

    QVector<QVector3D> vertices;
    QMatrix4x4 model = gameObject->getModelMatrix();
    vertices.push_back(model*v1);
    vertices.push_back(model*v2);
    vertices.push_back(model*v3);
    vertices.push_back(model*v4);
    vertices.push_back(model*v5);
    vertices.push_back(model*v6);
    vertices.push_back(model*v7);
    vertices.push_back(model*v8);
    initInertia(vertices);
    //applyForce(QVector3D(50,0,50),gameObject->getModelMatrix()*gameObject->getCenter() + QVector3D(-1,-1,-1)*gameObject->getModelMatrix());
}

Rigidbody::~Rigidbody()
{

}
void Rigidbody::applyForce(QVector3D force,QVector3D point)
{

    QVector3D momentum = force  * delta_time ;
    QVector3D torque = QVector3D::crossProduct((point-gameObject->getModelMatrix()*gameObject->getCenter())  ,force);

    QVector3D angularMomentum = (torque)*delta_time;

    angularVelocity += inertiaTensor.inverted()*angularMomentum;
    velocity += momentum / mass;

}

void Rigidbody::initInertia(QVector<QVector3D> vertices){
    inertiaTensor.setToIdentity();

    for(QVector3D v: vertices){
        inertiaTensor(0,0) += (v.y() * v.y() + v.z()*v.z()) ;
        inertiaTensor(1,1) += (v.x() * v.x  () + v.z()*v.z())  ;
        inertiaTensor(2,2) += (v.y() * v.y() + v.x()*v.x())  ;
        inertiaTensor(1,0) = inertiaTensor(0,1) += -v.x() * v.y() ;//0
        inertiaTensor(2,0) = inertiaTensor(0,2) += -v.z() * v.y() ;//0
        inertiaTensor(2,1) = inertiaTensor(1,2) += -v.x() * v.z() ;//0
    }
    float density = mass / pow(20,3);
    inertiaTensor *= density;

    inertiaTensor(3,3) = 1;//0

}

void Rigidbody::deleteThisPLZ()
{
    QMatrix4x4 model = gameObject->getModelMatrix();

    QVector3D v1 = QVector3D(1.000000, -1.000000, -1.000000);
    QVector3D v2 = QVector3D(1.000000, -1.000000, 1.000000);
    QVector3D v3 = QVector3D(-1.000000, -1.000000, 1.000000);
    QVector3D v4 = QVector3D(-1.000000, -1.000000, -1.000000);
    QVector3D v5 = QVector3D(1.000000, 1.000000, -1.000000);
    QVector3D v6 = QVector3D(1.000000, 1.000000, 1.000000);
    QVector3D v7 = QVector3D(-1.000000, 1.000000, 1.000000);
    QVector3D v8 = QVector3D(-1.000000, 1.000000, -1.000000);
    QVector3D vx = gameObject->getCenter();
    QVector<QVector3D> vertices;
    vertices.push_back(model*v1);
    vertices.push_back(model*v2);
    vertices.push_back(model*v3);
    vertices.push_back(model*v4);
    vertices.push_back(model*v5);
    vertices.push_back(model*v6);
    vertices.push_back(model*v7);
    vertices.push_back(model*v8);

    QVector3D lowerVertex = QVector3D(0,0,0);
    QVector3D averagePos = QVector3D();
    int cpt =0;

    for(auto v:vertices){
        if(v.y() < 0){
            if(lowerVertex.y() > v.y())
                lowerVertex.setY(v.y());
            averagePos+=v;
            cpt++;
        }
    }
    if(cpt >0)
        averagePos = averagePos/cpt;
    Transform *transform = gameObject->getComponent<Transform>();
    model = gameObject->getModelMatrix();

    model.setToIdentity();
    model.translate(gameObject->getCenter());


    model.translate((transform->getPosition()-velocity));

    model.rotate(transform->getRotation()-spin);

    model.scale(transform->getScale());

    if(lowerVertex.y() < 0){
        //angularVelocity *= 0;


        QVector3D force =  gameObject->getModelMatrix()*gameObject->getCenter() - model*gameObject->getCenter()  ;
        float d = QVector3D::dotProduct(velocity,QVector3D(0,1,0));
        float j = std::max( - ( 1 + 0.5 ) * d, 0. );
        velocity += j * QVector3D(0,1,0);

        QVector3D contactPoint =  gameObject->getModelMatrix()*gameObject->getCenter() - averagePos;
        j = - ( 1 + 0.1 ) * QVector3D::dotProduct(velocity,QVector3D(0,1,0)) /
                (pow(mass,-1) + QVector3D::dotProduct(inertiaTensor*QVector3D::crossProduct(QVector3D::crossProduct(contactPoint,
                                                                                                                    QVector3D(0,1,0)),
                                                                                            contactPoint),
                                                      QVector3D(0,1,0) ));
        QVector3D t =  velocity - (QVector3D::dotProduct(velocity,QVector3D(0,1,0))*QVector3D(0,1,0))/(velocity - (QVector3D::dotProduct(velocity,QVector3D(0,1,0)))*QVector3D(0,1,0)).length();
        float jt = -QVector3D::dotProduct(velocity,t) / (pow(mass,-1) + QVector3D::dotProduct(inertiaTensor*QVector3D::crossProduct(QVector3D::crossProduct(contactPoint,
                                                                                                                                                             t),
                                                                                                                                     contactPoint),
                                                                                               t ));
        QVector3D jr = j *QVector3D(1,1,1);
        angularVelocity += jr*inertiaTensor.inverted()*(QVector3D::crossProduct(contactPoint,QVector3D(0,1,0)));
        qDebug() << (velocity - (QVector3D::dotProduct(velocity,QVector3D(0,1,0)))*QVector3D(0,1,0));
    }
    if(lowerVertex.y() < 0){
        transform->setPosition(transform->getPosition()-lowerVertex);
    }
}


void Rigidbody::update()
{
    delta_time = elapsedTimer.elapsed()/1000.0f;
    applyForce(QVector3D(0,-1,0),gameObject->getModelMatrix()*gameObject->getCenter());


    QQuaternion q = QQuaternion( 0, angularVelocity);
    spin = 0.5f * q * transform->getRotation().normalized();

    transform->setPosition(transform->getPosition()+velocity);
    transform->setRotation((transform->getRotation().normalized()+spin).normalized());

    deleteThisPLZ();

    elapsedTimer.restart();
}


