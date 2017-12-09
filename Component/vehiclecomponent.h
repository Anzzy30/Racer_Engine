#ifndef VEHICLECOMPONENT_H
#define VEHICLECOMPONENT_H

#include "Component/component.h"
#include "GameObject/gameobject.h"
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
