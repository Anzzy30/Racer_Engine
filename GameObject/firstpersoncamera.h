#ifndef FIRSTPERSONCAMERA_H
#define FIRSTPERSONCAMERA_H
#include <QVector2D>

#include <GameObject/camera.h>

class FirstPersonCamera : public Camera
{
public:
    FirstPersonCamera();
    void update();
    QMatrix4x4 getViewMatrix();

    void setMoveLeft(bool value);
    void setMoveRight(bool value);
    void setMoveForward(bool value);
    void setMoveBackward(bool value);
    void setMoveUpper(bool value);
    void setMoveDown(bool value);
    void setV_mv(const QVector2D &value);

private:
    bool moveLeft;
    bool moveRight;
    bool moveForward;
    bool moveBackward;
    bool moveUpper;
    bool moveDown;
    QVector2D v_mv;
};

#endif // FIRSTPERSONCAMERA_H
