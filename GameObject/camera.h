#ifndef CAMERA_H
#define CAMERA_H

#include <GameObject/gameobject.h>
#include <QMatrix4x4>
class Camera : public GameObject
{
public:
    Camera();
    ~Camera();

    QVector3D getLookAt() const;
    QMatrix4x4 getProjectionMatrix() const;
    virtual QMatrix4x4 getViewMatrix() = 0;

    float getPitch() const;
    float getRoll() const;
    float getYaw() const;


    float getFOV() const;
    float getFAR_PLANE() const;
    float getNEAR_PLANE() const;

    void setLookAt(const QVector3D &value);
    void setProjectionMatrix(const QMatrix4x4 &value);
    void setViewMatrix(const QMatrix4x4 &value);

    void setPitch(float value);
    void setRoll(float value);
    void setYaw(float value);

    void setFOV(float value);
    void setNEAR_PLANE(float value);
    void setFAR_PLANE(float value);



protected:
    QVector3D lookAt;
    QMatrix4x4 projectionMatrix;
    QMatrix4x4 viewMatrix;


    float pitch;
    float roll;
    float yaw;

    float FOV;
    float NEAR_PLANE;
    float FAR_PLANE;
};

#endif // CAMERA_H
