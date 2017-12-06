#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include <QVector3D>
#include "Component/component.h"
#include "Component/transform.h"
#include "GameObject/gameobject.h"
#include <QVector3D>
#include <cmath>
#include <QElapsedTimer>

class Component;
class Rigidbody : public Component
{
public:
    Rigidbody(GameObject * gameObject);
    ~Rigidbody();
    void applyForce(QVector3D force, QVector3D point);

    void deleteThisPLZ();

    virtual void update();
private:
    Transform* transform;
    QVector3D velocity;


    QVector3D angularVelocity;
    QQuaternion spin;

    QElapsedTimer elapsedTimer;

    float mass = 1;
    float delta_time = 0.015;
};

#endif // RIGIDBODY_H
