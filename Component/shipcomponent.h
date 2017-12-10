#ifndef SHIPCOMPONENT_H
#define SHIPCOMPONENT_H

#include "external\bullet3-2.87\src\btBulletDynamicsCommon.h"
#include "Game/scene.h"
#include "QElapsedTimer"

class Component;
class Scene;

class ShipComponent : public Component
{
public:
    ShipComponent(GameObject *gameObject, Scene * _scene);
    virtual void update();
    void accelerate();
    void decelerate();
    void turnLeft();
    void turnRight();

private:
    Scene * scene; // To simulate world physic and raycasts

    float FragmentCount; // Circuit fragment we're on
    float ProgressionOnFragment;// % of fragment cleared

    float currentAcceleration; // Speed at which the ship travels
    float VerticalDistance; // Distance from center of the track to walls
    float HorizontalDistance; // Distance from minimum to maximum flight altitude

    const float MaxAcceleration = 40;
    const float MinAcceleration = 10;
    const float MaxHeight = 30;
    const float MinHeight = 5;
    const float FragmentSize = 1000;
};

#endif // SHIPCOMPONENT_H
