#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <QOpenGLShaderProgram>

#include "Component/programshader.h"
#include "GameObject/gameobject.h"

#include "Component/component.h"
#include "Utils/mesh.h"
class Component;

class MeshRenderer :public Component
{
public:
    MeshRenderer(GameObject * gameObject, Mesh *mesh);

    ~MeshRenderer();
    virtual void update();

    void renderMesh();

private:

    Mesh *mesh;


};

#endif // MESHRENDERER_H
