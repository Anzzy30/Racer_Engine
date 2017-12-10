#ifndef VEHICLECOMPONENT_H
#define VEHICLECOMPONENT_H

#include "Component/component.h"
#include "GameObject/gameobject.h"

#include "external\bullet3-2.87\src\btBulletDynamicsCommon.h"
#include "Component/rigidbody.h"
#include "Game/scene.h"
#include "QElapsedTimer"

class Component;
class Scene;



class VehicleComponent : public Component
{

public:
    VehicleComponent(GameObject *gameObject, Scene * _scene);
    ~VehicleComponent();
    void accelerate();
    void decelerate();
    void turnLeft();
    void turnRight();
    void actionKey();
    void boostKey();

    void updateSuspensionForce();

    virtual void update();
private:
    Scene * scene;
    QElapsedTimer elapsedTimer;

    float turnFactor;
    float accelerateFactor;
    float decelerateFactor;

    float suspensionLenght;
    btDynamicsWorld::ClosestRayResultCallback *frontLeft;
    btDynamicsWorld::ClosestRayResultCallback *frontRight;
    btDynamicsWorld::ClosestRayResultCallback *backLeft;
    btDynamicsWorld::ClosestRayResultCallback *backRight;
};

#endif // VEHICLECOMPONENT_H
