#ifndef MESH_H
#define MESH_H


#include <QOpenGLFunctions>
#include <QVector3D>
#include <QVector2D>
#include <QString>
#include <QFile>
#include <QStringList>
#include <QOpenGLBuffer>

#include <vector>
#include <string>
#include <fstream>

#include "Component/component.h"
#include "Utils/material.h"
#ifdef QT_DEBUG
    #include <Logger/logger.h>
#endif



typedef struct Face{
    GLuint count;
    std::vector<GLuint> indices;
    std::vector<GLuint> normals;
} Face;

struct Vertex
{
    // Position Vector
    QVector3D position;

    // Normal Vector
   // QVector3D normal;

    // Texture Coordinate Vector
   // QVector2D textureCoordinate;
};

class Component;

class Mesh: protected  QOpenGLFunctions
{
public:
    Mesh();
    ~Mesh();
    void plyLoader(QString path);
    void objLoader(QString path);

    void facesToTriangle();
    void computeNormalPerVertex();
    void loadMaterial(QString path);

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


    QVector<Material> materials;
};

#endif // MESH_H
