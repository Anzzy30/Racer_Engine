#include "meshtest.h"

MeshTest::MeshTest()
{

}

MeshTest::MeshTest(QVector3D position, QQuaternion rotation, QVector3D scale, QOpenGLShaderProgram *program):
    GameObject(position,rotation,scale),
    program(program)
{
    mesh = new Mesh();
    mesh->plyLoader(":/Resources/Models/autumntree.ply");
    this->center = mesh->getCenter();
    qDebug() << mesh->getMin_v();
}

MeshTest::~MeshTest()
{
    delete mesh;
}

void MeshTest::draw()
{
    mesh->drawMesh(program);
}







