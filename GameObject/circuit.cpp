#include "circuit.h"



Circuit::Circuit():
    GameObject("Circuit",QVector3D(0,0,0),QQuaternion(),QVector3D(5,5,5)),
    indexBuf(QOpenGLBuffer::IndexBuffer)
{
    arrayBuf.create();
    indexBuf.create();


    circuitWidth = 25;
    widthResolution = 2;




    for(int i=0;i<500;++i){
        controlPoints.push_back(QVector3D(i,std::cos(i/50)*3,0));
        qDebug() << std::cos(i/50);
    }
    initCircuit();



}

void Circuit::addPoint()
{


}

void Circuit::initCircuit()
{

    int height  = controlPoints.length();

    for(int j=0;j<controlPoints.size();++j){
        QVector3D forwardVector;
        if(j == controlPoints.size()-1)
            forwardVector = controlPoints.at(j) - controlPoints.at(j-1);
        else{
            forwardVector = controlPoints.at(j+1) - controlPoints.at(j);
        }

        QVector3D rightVector = QVector3D::crossProduct(forwardVector,QVector3D(0,1,0)).normalized();

        qDebug() << forwardVector << rightVector ;
        for(int i=0; i < widthResolution;++i){
            Vertex v;
            v.position = ((QVector3D) controlPoints.at(j) ) + rightVector * i/(widthResolution-1) * circuitWidth;
            v.normal = QVector3D(0,1,0);
            v.textureCoordinate = QVector2D( i/(widthResolution-1),(height-1) - j/(float)(height-1) * 5);
            vertices.push_back(v);
        }
    }


    for(int j = 0;j<height - 1;++j)
        for(int i = 0;i<widthResolution-1;++i){
                int i1 = j*widthResolution + i , i2 = j*(widthResolution) + i+1, i3 = (j+1)*(widthResolution), i4 = (j+1)*(widthResolution) + i+1;
                indices.push_back(i1);
                indices.push_back(i2);
                indices.push_back(i3);

                indices.push_back(i2);
                indices.push_back(i4);
                indices.push_back(i3);
        }

    arrayBuf.bind();
    arrayBuf.allocate(&vertices[0], vertices.size()* sizeof(Vertex));

    indexBuf.bind();
    indexBuf.allocate(&indices[0], indices.size()*sizeof(GLuint));


    circuitMesh = new Mesh();
    circuitMesh->setArrayBuf(arrayBuf);
    circuitMesh->setIndexBuf(indexBuf);
    Material m;
    m.loadMap_Kd(":/Resources/Texture/gradient-texture-cubes.jpg");
    circuitMesh->addMaterial(m);

    addComponent(new MeshRenderer(this,circuitMesh));

}





void Circuit::genCurve()
{

}
