#include "skybox.h"

Skybox::Skybox():    indexBuf(QOpenGLBuffer::IndexBuffer)

{
    initializeOpenGLFunctions();
    arrayBuf.create();
    indexBuf.create();
    scale = 150000;
}

Skybox::~Skybox()
{
    arrayBuf.destroy();
    indexBuf.destroy();

    delete skyboxTexture;
}

void Skybox::initSkybox()
{
    skyboxTexture = new QOpenGLTexture(QImage(":/Resources/Texture/skybox.jpg").mirrored());

    skyboxTexture->generateMipMaps();

    skyboxTexture->setMinificationFilter(QOpenGLTexture::Nearest);

    skyboxTexture->setMagnificationFilter(QOpenGLTexture::NearestMipMapLinear);

    skyboxTexture->setWrapMode(QOpenGLTexture::Repeat);

    QVector<Vertex> vertices;
    QVector<GLuint> indices;

    Vertex v;
    v.position = QVector3D(1,-1,-1)*scale;
    v.textureCoordinate = QVector2D(2.01/3.,0.);
    vertices.push_back(v);
    v.position = QVector3D(1,-1,1)*scale;
    v.textureCoordinate = QVector2D(2.99/4.,0.);
    vertices.push_back(v);
    v.position = QVector3D(-1,-1,1)*scale;
    v.textureCoordinate = QVector2D(2.99/4.,1/3.);
    vertices.push_back(v);
    v.position = QVector3D(-1,-1,-1)*scale;
    v.textureCoordinate = QVector2D(2.01/3.,1/3.);
    vertices.push_back(v);

    v.position = QVector3D(1,1,-1)*scale;
    v.textureCoordinate = QVector2D(2.01/4.,2/3.);
    vertices.push_back(v);
    v.position = QVector3D(1,1,1)*scale;
    v.textureCoordinate = QVector2D(2.99/4.,2/3.);
    vertices.push_back(v);
    v.position = QVector3D(-1,1,1)*scale;
    v.textureCoordinate = QVector2D(2.99/4.,1.);
    vertices.push_back(v);
    v.position = QVector3D(-1,1,-1)*scale;
    v.textureCoordinate = QVector2D(2.01/4.,1.);
    vertices.push_back(v);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);

    indices.push_back(4);
    indices.push_back(7);
    indices.push_back(6);
    indices.push_back(4);
    indices.push_back(6);
    indices.push_back(5);

    v.position = QVector3D(1,-1,-1)*scale;
    v.textureCoordinate = QVector2D(2.01/4.,1/3.);
    vertices.push_back(v);
    v.position = QVector3D(1,-1,1)*scale;
    v.textureCoordinate = QVector2D(2.99/4.,1/3.);
    vertices.push_back(v);

    indices.push_back(8);
    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(8);
    indices.push_back(5);
    indices.push_back(9);


    v.position = QVector3D(1,-1,1)*scale;
    v.textureCoordinate = QVector2D(3/4.,1.01/3.);
    vertices.push_back(v);
    v.position = QVector3D(1,1,1)*scale;
    v.textureCoordinate = QVector2D(3/4.,1.99/3.);
    vertices.push_back(v);
    v.position = QVector3D(-1,1,1)*scale;
    v.textureCoordinate = QVector2D(1.,1.99/3.);
    vertices.push_back(v);
    v.position = QVector3D(-1,-1,1)*scale;
    v.textureCoordinate = QVector2D(1.,1.01/3.);
    vertices.push_back(v);


    indices.push_back(10);
    indices.push_back(11);
    indices.push_back(12);
    indices.push_back(10);
    indices.push_back(12);
    indices.push_back(13);


    v.position = QVector3D(-1,-1,1)*scale;
    v.textureCoordinate = QVector2D(0.,1.01/3.);
    vertices.push_back(v);
    v.position = QVector3D(-1,-1,-1)*scale;
    v.textureCoordinate = QVector2D(1/4.,1.01/3.);
    vertices.push_back(v);
    v.position = QVector3D(-1,1,1)*scale;
    v.textureCoordinate = QVector2D(0.,1.99/3.);
    vertices.push_back(v);
    v.position = QVector3D(-1,1,-1)*scale;
    v.textureCoordinate = QVector2D(1/4.,1.99/3.);
    vertices.push_back(v);

    indices.push_back(14);
    indices.push_back(16);
    indices.push_back(17);

    indices.push_back(14);
    indices.push_back(17);
    indices.push_back(15);


    v.position = QVector3D(1,-1,-1)*scale;
    v.textureCoordinate = QVector2D(2/4.,1.01/3.);
    vertices.push_back(v);
    v.position = QVector3D(-1,-1,-1)*scale;
    v.textureCoordinate = QVector2D(1/4.,1.01/3.);
    vertices.push_back(v);

    v.position = QVector3D(1,1,-1)*scale;
    v.textureCoordinate = QVector2D(2/4.,1.99/3.);
    vertices.push_back(v);
    v.position = QVector3D(-1,1,-1)*scale;
    v.textureCoordinate = QVector2D(1/4.,1.99/3.);
    vertices.push_back(v);

    indices.push_back(20);
    indices.push_back(18);
    indices.push_back(19);

    indices.push_back(20);
    indices.push_back(19);
    indices.push_back(21);

    arrayBuf.bind();
    arrayBuf.allocate(&vertices[0], vertices.size() * sizeof(Vertex));

    indexBuf.bind();
    indexBuf.allocate(&indices[0], indices.size() * sizeof(GLuint));


    /*
v 1.000000 -1.000000 -1.000000
v 1.000000 -1.000000 1.000000
v -1.000000 -1.000000 1.000000
v -1.000000 -1.000000 -1.000000
v 1.000000 1.000000 -0.999999
v 0.999999 1.000000 1.000001
v -1.000000 1.000000 1.000000
v -1.000000 1.000000 -1.000000

f 1/1/1 2/2/1 3/3/1 4/4/1
f 5/5/2 8/6/2 7/7/2 6/8/2
f 1/1/3 5/9/3 6/10/3 2/11/3
f 2/12/4 6/13/4 7/7/4 3/14/4
f 3/15/5 7/16/5 8/17/5 4/4/5
f 5/5/6 1/18/6 4/19/6 8/20/6
    */

}

void Skybox::renderSkybox(QOpenGLShaderProgram* shader)
{
    glDisable(GL_CULL_FACE);
    skyboxTexture->bind();
    arrayBuf.bind();
    indexBuf.bind();
    quintptr offset = 0;

    int vertexLocation = shader->attributeLocation("a_position");
    shader->enableAttributeArray(vertexLocation);
    shader->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(Vertex));


    offset += sizeof(QVector3D);

    int texcoordLocation = shader->attributeLocation("a_texcoord");
    shader->enableAttributeArray(texcoordLocation);
    shader->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(Vertex));

    offset += sizeof(QVector2D);

    int normalLocation = shader->attributeLocation("a_normal");
    shader->enableAttributeArray(normalLocation);
    shader->setAttributeBuffer(normalLocation, GL_FLOAT, offset, 3, sizeof(Vertex));


    glDrawElements(GL_TRIANGLES, indexBuf.size()/sizeof(GLuint), GL_UNSIGNED_INT, 0);

    glEnable(GL_CULL_FACE);


}

