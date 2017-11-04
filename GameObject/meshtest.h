#ifndef MESHTEST_H
#define MESHTEST_H

#include <GameObject/gameobject.h>
#include <Component/meshrenderer.h>

class MeshTest : public GameObject
{
public:
    MeshTest();
    MeshTest(QVector3D position, QQuaternion rotation, QVector3D scale, Mesh *mesh, QOpenGLShaderProgram *program);
    ~MeshTest();
};

#endif // MESHTEST_H
