#ifndef VEHICLECOMPONENT_H
#define VEHICLECOMPONENT_H

#include "Component/component.h"
#include "GameObject/gameobject.h"

#include "external\bullet3-2.87\src\btBulletDynamicsCommon.h"
#include "Component/rigidbody.h"

class Component;

class VehicleComponent : public Component
{

public:
    VehicleComponent(GameObject *gameObject);
    ~VehicleComponent();
    void accelerate();
    void decelerate();
    void turnLeft();
    void turnRight();
    void actionKey();
    void boostKey();

    virtual void update();
};

#endif // VEHICLECOMPONENT_H
