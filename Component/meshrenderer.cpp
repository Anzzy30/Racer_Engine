#include "meshrenderer.h"

MeshRenderer::MeshRenderer(GameObject * gameObject,Mesh *mesh):
    Component(gameObject),
    mesh(mesh)

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
    ProgramShader *p = gameObject->getComponent<ProgramShader>();
    if(!p)
        return;
    QOpenGLShaderProgram * program = p->getProgram();

    mesh->getMaterials().at(0).getMap_Kd()->bind(0);
    mesh->getArrayBuf().bind();
    mesh->getIndexBuf().bind();
    quintptr offset = 0;
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(Vertex));


    offset += sizeof(QVector3D);

    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(Vertex));

    offset += sizeof(QVector2D);

    int normalLocation = program->attributeLocation("a_normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(Vertex));


    glDrawElements(GL_TRIANGLES, mesh->getIndexBuf().size()/sizeof(GLuint), GL_UNSIGNED_INT, 0);

}
