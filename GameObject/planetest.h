#ifndef PLANETEST_H
#define PLANETEST_H


#include <GameObject/gameobject.h>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QImage>

class PlaneTest : protected  QOpenGLFunctions
{
public:
    PlaneTest();
    ~PlaneTest();

    void drawPlane(QOpenGLShaderProgram *program);
private:
    void initPlaneGeometry();


    QImage heightMap;
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    int height;
    int width;
};

#endif // PLANETEST_H
