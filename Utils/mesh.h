#ifndef MESH_H
#define MESH_H


#include <QOpenGLFunctions>
#include <QVector3D>
#include <QString>
#include <QFile>
#include <QStringList>
#include <QOpenGLBuffer>

#include <vector>
#include <string>
#include <fstream>

#include "Component/component.h"

#ifdef QT_DEBUG
    #include <Logger/logger.h>
#endif



typedef struct Face{
    GLuint count;
    std::vector<GLuint> indices;
} Face;

class Component;

class Mesh: protected  QOpenGLFunctions
{
public:
    Mesh();
    ~Mesh();
    void plyLoader(QString path);

    void facesToTriangle();

    QVector3D getMin_v() const;
    QVector3D getMax_v() const;
    QVector3D getCenter() const;

    QOpenGLBuffer getArrayBuf() const;
    QOpenGLBuffer getIndexBuf() const;

private:
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QVector<GLuint> indices;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    QVector3D min_v;
    QVector3D max_v;
    QVector3D center;


    std::vector<Face> faces;

};

#endif // MESH_H
