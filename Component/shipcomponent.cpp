#include "Component/shipcomponent.h"

ShipComponent::ShipComponent(GameObject *gameObject, Scene *_scene):
    Component(gameObject)
{
    scene = _scene;
}

void ShipComponent::update()
{
    /// Algorithm:
    /// Progress along the circuit curve following acceleration.
    /// Calculate vertical drag from circuit curve
    /// Check for collision from circuit circuit limit
    /// Bounce off and lose speed if in collision with circuit limit.
    /// Check for circuit height changes, change ship accordingly

    // Calculate new position on fragment
    float oldProgressionOnFragment = ProgressionOnFragment; // Used for the circuit functions
    ProgressionOnFragment += FragmentSize/currentAcceleration;

    if (ProgressionOnFragment >= 1)
    {
        ProgressionOnFragment-=1;
        FragmentCount++;
    }

    // Calculate vertical drag

    float VerticalDrag = 0.1; // Given by the circuit object, ranging from -1 to 1;

    VerticalDistance+=VerticalDrag;
    if (VerticalDistance > 1)
    {
        VerticalDistance = 1-(1-VerticalDistance);
        currentAcceleration =MinAcceleration;
    }
    else if (VerticalDistance < 1)
    {
        VerticalDistance = -1+(-1-VerticalDistance);
        currentAcceleration =MinAcceleration;
    }

    // Calculate height delta

    float HeightDelta = 0.1; // Given by the circuit object, ranging from -1 to 1;

    HorizontalDistance += HeightDelta;

    if (HorizontalDistance > MaxHeight)
    {
        VerticalDistance = MaxHeight;
    }
    else if (HorizontalDistance < MinHeight)
    {
        VerticalDistance = MinHeight;
    }
}

void ShipComponent::accelerate()
{
    currentAcceleration++;
    if (currentAcceleration > MaxAcceleration) currentAcceleration=MaxAcceleration;
}

void ShipComponent::decelerate()
{
    currentAcceleration--;
    if (currentAcceleration < MinAcceleration) currentAcceleration=MinAcceleration;
}

void ShipComponent::turnLeft()
{
    VerticalDistance -=0.05;
    if (VerticalDistance <-1) VerticalDistance == -1;
}

void ShipComponent::turnRight()
{
    VerticalDistance +=0.05;
    if (VerticalDistance >1) VerticalDistance == 1;
}
