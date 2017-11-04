#include "meshrenderer.h"

MeshRenderer::MeshRenderer(GameObject * gameObject,Mesh *mesh , QOpenGLShaderProgram *program):
    Component(gameObject),
    mesh(mesh),
    program(program)

{

}



MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::update()
{
    renderMesh();
}

void MeshRenderer::renderMesh()
{
    mesh->getArrayBuf().bind();
    mesh->getIndexBuf().bind();

    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));

    glDrawElements(GL_TRIANGLES, mesh->getIndexBuf().size(), GL_UNSIGNED_INT, 0);
}
