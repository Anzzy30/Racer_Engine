#include "planetest.h"
#include <QVector2D>
#include <QVector3D>



struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

PlaneTest::PlaneTest() : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    heightMap = QImage(":/Resources/Texture/heightmap-3.png");
    initializeOpenGLFunctions();
    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    width = heightMap.width();
    height = heightMap.height();

    initPlaneGeometry();
}

PlaneTest::~PlaneTest()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void PlaneTest::initPlaneGeometry()
{



    VertexData *vertices = new VertexData[width * height];
    int offset = 0;
    for (int j=0;j<height;j++)
        for (int i=0;i<width;i++)
        {

            QRgb rgb = heightMap.pixel(i,j);
            rgb = qGray(rgb);
            float z = 35.0 * ((float)rgb/255);
                vertices[offset++] = {
                QVector3D(0.5*(i-width/2),z,0.5*(j-height/2)),
                QVector2D( i/(float)(width-1),(height-1) - j/(float)(height-1))
            };
        }

    int size = (2*width)*(height-1) + 2*(height-2) + 1;

    GLuint *indices = new GLuint[size];
    offset = 0;
    int i,j;
    for (j = 0; j < height-1; ++j) {
        if(j > 0 && j < height-1)
            indices[offset++] = j*width;
        for (i = 0; i < width; ++i) {
            indices[offset++] = j*width+i;
            indices[offset++] = (j+1)*width+i;
        }
        if(j < height - 1)
            indices[offset++] = (j+1)*width+(i-1);
    }
    arrayBuf.bind();
    arrayBuf.allocate(vertices, height*width* sizeof(VertexData));

    indexBuf.bind();
    indexBuf.allocate(indices, (offset)*sizeof(GLuint));
}


void PlaneTest::drawPlane(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();
    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));
    int size = (2*width)*(height-1) + 2*(height-2) + 1;

    // Draw plane geometry using indices from VBO 1

    glDrawElements(GL_TRIANGLE_STRIP, size, GL_UNSIGNED_INT, 0);


}
