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
#include "external\bullet3-2.87\src\BulletCollision\CollisionShapes\btBvhTriangleMeshShape.h"
#include "external\bullet3-2.87\src\BulletCollision\CollisionShapes\btTriangleMesh.h"



typedef struct Face{
    GLuint count;
    std::vector<GLuint> indices;
    std::vector<GLuint> textures;
    std::vector<GLuint> normals;
} Face;

struct Vertex
{
    // Position Vector
    QVector3D position;

    // Texture Coordinate Vector
    QVector2D textureCoordinate;

    // Normal Vector
    QVector3D normal;

};

class Component;

class Mesh: protected  QOpenGLFunctions
{
public:
    Mesh();
    ~Mesh();
    void plyLoader(QString path);
    void objLoader(QString path);


    void facesToTriangle(QVector<Face> &faces, bool hasTextures, bool hasNormals);
    void computeNormalPerVertex();
    void loadMaterial(QString path);

    QVector3D getMin_v() const;
    QVector3D getMax_v() const;
    QVector3D getCenter() const;

    QOpenGLBuffer getArrayBuf() const;
    QOpenGLBuffer getIndexBuf() const;

    void meshToCollisionShape(btTriangleMesh * btMesh);
    QVector<Material> getMaterials() const;

private:
    QString name;
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;

    QVector3D min_v;
    QVector3D max_v;
    QVector3D center;

    std::vector<Face> faces;

    QVector<Material> materials;
};

#endif // MESH_H
