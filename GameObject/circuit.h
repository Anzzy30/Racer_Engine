#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <GameObject/gameobject.h>
#include <QOpenGLBuffer>
#include <Utils/mesh.h>
#include <Component/MeshRenderer.h>
#include <QOpenGLFunctions>

struct CurveDataPoint{
    QVector3D pos;
    QVector3D upVector;
    QVector3D forwardVector;
};

class Circuit :public GameObject
{
public:
    Circuit();

    void addPoint();
private:

    void genCurve();
    void initCircuit();

    Mesh *circuitMesh;


    int circuitWidth;
    int widthResolution;

    QVector<QVector3D> controlPoints;
    QVector<CurveDataPoint> curveData;

    QVector3D upVector;
    QVector3D forwardVector;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    QVector<Vertex> vertices;
    QVector<GLuint> indices;

};

#endif // CIRCUIT_H
