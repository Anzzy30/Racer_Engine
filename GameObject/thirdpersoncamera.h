#ifndef THIRDPERSONCAMERA_H
#define THIRDPERSONCAMERA_H
#include <GameObject/camera.h>
#include <Utils/utils.h>
class ThirdPersonCamera : public Camera
{
public:
    ThirdPersonCamera(GameObject *target);

    QMatrix4x4 getViewMatrix();

    void update();
private:
    GameObject* target;
    QVector3D targetPreviousPosition;
    int lerpTime;
    float offset;

};

#endif // THIRDPERSONCAMERA_H








