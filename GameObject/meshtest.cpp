#include "meshtest.h"

MeshTest::MeshTest()
{

}

MeshTest::MeshTest(QVector3D position, QVector3D rotation, QVector3D scale, QOpenGLShaderProgram *program):
    program(program)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    mesh = new Mesh();
    mesh->plyLoader(":/Resources/Models/springtree.ply");
}

MeshTest::~MeshTest()
{
    delete mesh;
}

void MeshTest::draw()
{

    mesh->drawMesh(program);
}







