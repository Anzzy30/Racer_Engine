#ifndef FIRSTPERSONCAMERA_H
#define FIRSTPERSONCAMERA_H
#include <QVector2D>

#include <GameObject/camera.h>

class FirstPersonCamera : public Camera
{
public:
    FirstPersonCamera();
    ~FirstPersonCamera();
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
    bool moveLeft = false;
    bool moveRight = false;
    bool moveForward = false;
    bool moveBackward = false;
    bool moveUpper = false;
    bool moveDown = false;
    QVector2D v_mv;
};

#endif // FIRSTPERSONCAMERA_H
