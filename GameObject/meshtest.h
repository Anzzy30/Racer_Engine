#ifndef MESHTEST_H
#define MESHTEST_H

#include <GameObject/gameobject.h>
#include <Component/mesh.h>

class MeshTest : public GameObject
{
public:
    MeshTest();
    MeshTest(QVector3D position, QVector3D rotation, QVector3D scale, QOpenGLShaderProgram *program);
    ~MeshTest();
    void draw();

private:

    Mesh *mesh;
    QOpenGLShaderProgram *program;


};

#endif // MESHTEST_H
