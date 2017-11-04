#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <QOpenGLShaderProgram>


#include "Component/component.h"
#include "Utils/mesh.h"
class Component;

class MeshRenderer :public Component
{
public:
    MeshRenderer(GameObject * gameObject,Mesh *mesh,QOpenGLShaderProgram *program);

    ~MeshRenderer();
    virtual void update();

    void renderMesh();

private:

    Mesh *mesh;
    QOpenGLShaderProgram *program;


};

#endif // MESHRENDERER_H
