#include "model.h"

Model::Model()
{

}

Model::Model(QString name, QVector3D position, QQuaternion rotation, QVector3D scale, Mesh* mesh):
    GameObject(name,position,rotation,scale)
{
    addComponent(new MeshRenderer(this,mesh));
    this->center = mesh->getCenter();
}

Model::~Model()
{
}









