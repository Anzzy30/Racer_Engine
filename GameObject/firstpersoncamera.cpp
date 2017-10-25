#include "firstpersoncamera.h"

# define M_PI 3.14159265358979323846  /* pi */

FirstPersonCamera::FirstPersonCamera()
{

}

void FirstPersonCamera::move(float dx, float dy, int z, int s, int q, int d, int dh)
{
    pitch += dy * 0.3f;
    yaw += dx * 0.3f;


    if(pitch > 89.0)
         pitch = 89.0;
    else if(pitch < -89.0)
        pitch = -89.0;

    float phiRadian = ( pitch * M_PI ) / 180;
    float thetaRadian = ( yaw * M_PI ) / 180;

    lookAt.setX(cos(phiRadian) * -sin(thetaRadian));
    lookAt.setY(-sin(phiRadian));
    lookAt.setZ(cos(phiRadian) * cos(thetaRadian));

    QVector3D right;
    right.setX(sin(thetaRadian- 3.14f/2.0f));
    right.setY(0);
    right.setZ(-cos(thetaRadian- 3.14f/2.0f));

    if(z){

        position.setX(position.x() + lookAt.x() * 1.5f);
        position.setY(position.y() + lookAt.y() * 1.5f);
        position.setZ(position.z() + lookAt.z() * 1.5f);

    }
    if(s){
        position.setX(position.x() - lookAt.x() * 1.5f);
        position.setY(position.y() - lookAt.y() * 1.5f);
        position.setZ(position.z() - lookAt.z() * 1.5f);

    }
    if(q){

        position.setX(position.x() - right.x() * 1.5f);
        position.setZ(position.y() - right.z() * 1.5f);

    }
    if(d){

        position.setX(position.x() + right.x() *1.5f);
        position.setZ(position.y() + right.z() *1.5f);

    }


    position.setY(position.y() + 0.7f*dh);
}
