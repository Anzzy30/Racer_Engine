#include "model.h"

Model::Model()
{

}

Model::Model(QString name,QVector3D position, QQuaternion rotation, QVector3D scale,Mesh* mesh, QOpenGLShaderProgram *program):
    GameObject(name,position,rotation,scale)
{
    addComponent(new MeshRenderer(this,mesh,program));
    this->center = mesh->getCenter();
}

Model::~Model()
{
}









