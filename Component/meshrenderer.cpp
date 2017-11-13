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
    mesh->getMaterials().at(0).getMap_Kd()->bind();
    quintptr offset = 0;


    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(Vertex));

    offset += sizeof(QVector3D);

    int normalLocation = program->attributeLocation("v_normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(Vertex));


    offset += sizeof(QVector3D);

    int texcoordLocation = program->attributeLocation("v_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(Vertex));

    glDrawElements(GL_TRIANGLES, mesh->getIndexBuf().size()/sizeof(GLuint), GL_UNSIGNED_INT, 0);
}
