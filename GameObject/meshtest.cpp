#include "meshtest.h"

MeshTest::MeshTest()
{

}

MeshTest::MeshTest(QVector3D position, QQuaternion rotation, QVector3D scale,Mesh* mesh, QOpenGLShaderProgram *program):
    GameObject(position,rotation,scale)
{
    addComponent(new MeshRenderer(this,mesh,program));
    this->center = mesh->getCenter();
}

MeshTest::~MeshTest()
{
}









