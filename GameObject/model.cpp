#include "model.h"

Model::Model()
{

}

Model::Model(QVector3D position, QQuaternion rotation, QVector3D scale,Mesh* mesh, QOpenGLShaderProgram *program):
    GameObject(position,rotation,scale)
{
    addComponent(new MeshRenderer(this,mesh,program));
    this->center = mesh->getCenter();
}

Model::~Model()
{
}









