#ifndef VEHICLECOMPONENT_H
#define VEHICLECOMPONENT_H

#include "Component/component.h"
#include "GameObject/gameobject.h"

#include "external\bullet3-2.87\src\btBulletDynamicsCommon.h"
#include "Component/rigidbody.h"
#include "Game/scene.h"
#include "QElapsedTimer"
#include <cmath>

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

    float getSpeed() const;

    virtual void update();
    bool getOnGround() const;

    float getBoostCD() const;

    float getMaxBoostCD() const;

private:
    Scene * scene;
    QElapsedTimer elapsedTimer;

    float turnFactor;
    float accelerateFactor;
    float decelerateFactor;
    float maxBoostCD = 10.f;
    float gearPowers[6];
    float boostCD = 0;
    float currentPower=0;
    bool accelerating = false;

    float suspensionLenght;

    float gear = 1;

    float currentSpeed = 0;

    bool onGround;
};

#endif // VEHICLECOMPONENT_H
