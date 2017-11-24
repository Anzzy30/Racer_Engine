#ifndef MODEL_H
#define MODEL_H

#include <GameObject/gameobject.h>
#include <Component/meshrenderer.h>

class Model : public GameObject
{
public:
    Model();
    Model(QString name,QVector3D position, QQuaternion rotation, QVector3D scale, Mesh *mesh, QOpenGLShaderProgram *program);
    ~Model();
};

#endif // MODEL_H
