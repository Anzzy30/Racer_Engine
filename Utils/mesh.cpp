#include "mesh.h"

Mesh::Mesh():
    indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();
    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

}

Mesh::~Mesh()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void Mesh::plyLoader(QString path)
{
    Logger::Info(("plyLoader()"),0);
    QFile plyFile(path);
    if(!plyFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Logger::Warning("Unable to open ply file (plyLoader)",0);
        return;
    }
    QTextStream in(&plyFile);
    QString line = in.readLine();
    if(line.compare("ply") != 0){
        Logger::Warning("Wrong file format (plyLoader)",0);
        return;
    }

    /*format*/
    line = in.readLine();

    /*comment*/
    line = in.readLine();

    line = in.readLine();
    QStringList fields = line.split(" ");
    QString element_vertex = fields.at(2);

    int vertexCount = element_vertex.toInt();
    /*property only vertex + normal file here*/
    while ((line = in.readLine()) != NULL)
    {
        fields = line.split(" ");
        if (((QString)fields.at(0)).compare( "property") != 0)
            break;
    }
    QString element_face = fields.at(2);

    int faceCount = element_face.toInt();

    while ((line = in.readLine())!= NULL)
    {
        if (line.compare( "end_header") == 0)
            break;
    }
    QVector<QVector3D> vertices,normals;
    QVector<GLuint> indices;
    for(int i=0;i<vertexCount;++i){
        line = in.readLine();

        fields = line.split(" ");
        QVector3D v;
        QVector3D n;

        v.setX(((QString)fields.at(0)).toFloat());
        v.setY(((QString)fields.at(1)).toFloat());
        v.setZ(((QString)fields.at(2)).toFloat());
        if(i==0 || (v.x() < min_v.x() && v.y() < min_v.y() && v.z() < min_v.z() ))
            min_v = v;
        if(i==0 || (v.x() > max_v.x() && v.y() > max_v.y() && v.z() > max_v.z() ))
            max_v = v;


        if(fields.size() > 4){
            n.setX(((QString)fields.at(3)).toFloat());
            n.setY(((QString)fields.at(4)).toFloat());
            n.setZ(((QString)fields.at(5)).toFloat());
        }

        vertices.push_back(v);

        normals.push_back(n);

    }
    QVector<Face> tmp_faces;

    for(int i=0;i<faceCount;++i){
        line = in.readLine();
        fields = line.split(" ");
        Face f;
        f.count = ((QString)fields.at(0)).toInt();

        for(GLuint j=1;j<=f.count;++j){
            f.indices.push_back(((QString)fields.at(j)).toInt());
        }
        tmp_faces.push_back(f);
    }

    plyFile.close();

    center = min_v+(max_v-min_v)/2;

    facesToTriangle(tmp_faces,false,false);

    for(auto const& face: faces) {

        if(face.count >= 3){
            for(GLuint i=1;i<face.count-1;++i){

                indices.push_back(face.indices[0]);
                indices.push_back(face.indices[i]);
                indices.push_back(face.indices[i+1]);
            }
        }
    }


    arrayBuf.bind();
    arrayBuf.allocate(&vertices[0], vertices.size() * sizeof(QVector3D));

    indexBuf.bind();
    indexBuf.allocate(&indices[0], indices.size() * sizeof(GLuint));
}


/*Triangle obj file only*/
void Mesh::objLoader(QString path)
{
    Logger::Info(("objLoader()"),0);
    QFile objFile(path);
    if(!objFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Logger::Warning("Unable to open obj file (objLoader)",0);
        return;
    }
    QTextStream in(&objFile);
    QString line = in.readLine();

    QStringList splitLine;

    QVector<QVector3D> normalsPerFace;
    QVector<QVector2D> vertexTexture;

    QVector<Vertex> vertexArray;

    QVector<Face> tmp_faces;
    QVector<GLuint> indices;

    while ((line = in.readLine()) != NULL)
    {
        if(line.at(0) == '#')
            continue;

        if(line.at(0) == 'o'){
            continue;

        }
        splitLine = line.split(" ");
        if(((QString)splitLine.at(0)).compare("mtllib") == 0){
            loadMaterial(splitLine.at(1));
        }else if (((QString)splitLine.at(0)).compare("v") == 0){
            QVector3D v;
            v.setX(((QString)splitLine.at(1)).toFloat());
            v.setY(((QString)splitLine.at(2)).toFloat());
            v.setZ(((QString)splitLine.at(3)).toFloat());
            if(vertexArray.size() == 0 ){
                min_v = v;
                max_v = v;
            }
            if(v.x() < min_v.x())
                min_v.setX(v.x());
            if(v.y() < min_v.y())
                min_v.setY(v.y());
            if( v.z() < min_v.z())
                min_v.setZ(v.z());

            if(v.x() > max_v.x() )
                max_v.setX(v.x());
            if(v.y() > max_v.y())
                max_v.setY(v.y());
            if(v.z() > max_v.z())
                max_v.setZ(v.z());
            Vertex vData;
            vData.position = v;
            vData.normal = QVector3D(0,0,0);
            vertexArray.push_back(vData);
        }else if(((QString)splitLine.at(0)).compare("vt") == 0){
            QVector2D vt;
            vt.setX(((QString)splitLine.at(1)).toFloat());
            vt.setY(((QString)splitLine.at(2)).toFloat());
            vertexTexture.push_back(vt);
        }else if(((QString)splitLine.at(0)).compare("vn") == 0){
            QVector3D n;
            n.setX(((QString)splitLine.at(1)).toFloat());
            n.setY(((QString)splitLine.at(2)).toFloat());
            n.setZ(((QString)splitLine.at(3)).toFloat());
            normalsPerFace.push_back(n);
        }else if(((QString)splitLine.at(0)).compare("f") == 0){
            Face f;
            f.count = 0;

            for(auto const& field : splitLine){

                if(field.compare("") == 0 || field.compare("f")==0){
                    continue;
                }
                QStringList vertexData = field.split("/");
                f.count++;

                f.indices.push_back(((QString)vertexData.at(0)).toUInt()-1);
                f.textures.push_back(((QString)vertexData.at(1)).toUInt()-1);
                f.normals.push_back(((QString)vertexData.at(2)).toUInt()-1);

                vertexArray[f.indices.at(f.count-1)].textureCoordinate = vertexTexture.at(f.textures.at(f.count-1));
                vertexArray[f.indices.at(f.count-1)].normal = normalsPerFace.at(f.normals.at(f.count-1));

            }



            tmp_faces.push_back(f);
        }
    }
    objFile.close();



    facesToTriangle(tmp_faces,true,true);
    /*Normal & texture per vertex (duplicate vertex with multiple uv*/

    GLuint nbVertex = vertexArray.size();
    for(GLuint i=0;i<nbVertex;++i){
        QVector<QVector3D> vertexNormals;
        QVector<int> faceIndice;
        //QVector<float> faceArea;
        for(GLuint j=0;j<faces.size();++j){
            for(GLuint k=0;k<faces[j].count;++k){

                if(i == faces[j].indices[k]){
                    faceIndice.push_back(j);
                    vertexNormals.push_back(normalsPerFace[faces[j].normals[k]]);
                    break;
                }

            }
        }

        QVector3D normal = QVector3D();
        for(int n=0; n<vertexNormals.size();++n){
            normal += vertexNormals[n];
        }
        vertexArray[i].normal = normal.normalized();

        for(int t=0; t<faceIndice.size();++t){
            for(GLuint k=0;k<faces[faceIndice[t]].count;++k){
                if(i == faces[faceIndice[t]].indices[k]){

                    if(t==0){
                        vertexArray[i].textureCoordinate = vertexTexture[faces.at(faceIndice[t]).textures[k]];
                    }else if(vertexArray[i].textureCoordinate != vertexTexture[faces.at(faceIndice[t]).textures[k]]){
                        Vertex vData;
                        vData.position = vertexArray[i].position;
                        vData.normal = vertexArray[i].normal;
                        vData.textureCoordinate = vertexTexture[faces.at(faceIndice[t]).textures[k]];
                        vertexArray.push_back(vData);
                        faces.at(faceIndice[t]).indices[k] = vertexArray.size()-1;
                    }

                }
            }

        }
    }



    center = min_v + (max_v-min_v)/2;

    for(auto const& face: faces) {

        for(GLuint i=0;i<face.count;++i){
            indices.push_back(face.indices[i]);
        }
    }


    arrayBuf.bind();
    arrayBuf.allocate(&vertexArray[0],vertexArray.size()*sizeof(Vertex));

    indexBuf.bind();
    indexBuf.allocate(&indices[0], indices.size() * sizeof(GLuint));
}


void Mesh::facesToTriangle(QVector<Face> &faces,bool hasTextures,bool hasNormals){

    for(auto const& face: faces) {


        if(face.count >= 3){
            for(GLuint i=1;i<face.count-1;++i){
                Face f;
                f.count = 3;
                f.indices.push_back(face.indices[0]);
                f.indices.push_back(face.indices[i]);
                f.indices.push_back(face.indices[i+1]);
                if(hasTextures){
                    f.textures.push_back(face.textures[0]);
                    f.textures.push_back(face.textures[i]);
                    f.textures.push_back(face.textures[i+1]);
                }
                if(hasNormals){
                    f.normals.push_back(face.normals[0]);
                    f.normals.push_back(face.normals[i]);
                    f.normals.push_back(face.normals[i+1]);
                }

                this->faces.push_back(f);

            }

        }
    }
}

void Mesh::loadMaterial(QString path){
    Logger::Info(("LoadMaterial()"),0);
    QString relativePath = ":/Resources/Models/";
    relativePath +=path;
    QFile mtlFile(relativePath);
    if(!mtlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Logger::Warning("Unable to open mtl file (loadMaterial)",0);
        return;
    }
    QTextStream in(&mtlFile);
    QString line ;

    QStringList splitLine;
    int cursor = -1;
    while (!in.atEnd())
    {

        line = in.readLine();
        if(line.compare("") == 0)
            continue;
        if(line.at(0) == '#')
            continue;
        splitLine = line.split(" ");
        if ((((QString)splitLine.at(0)).compare("newmtl") == 0)){
            materials.push_back(Material());
            cursor++;
            materials[cursor].setName(splitLine.at(1));
        }else if (((QString)splitLine.at(0)).compare("Ns") == 0){
            materials[cursor].setNi(((QString)splitLine.at(1)).toFloat());
        }else if (((QString)splitLine.at(0)).compare("Ka") == 0){
            float x = (((QString)splitLine.at(1)).toFloat());
            float y = (((QString)splitLine.at(2)).toFloat());
            float z = (((QString)splitLine.at(3)).toFloat());
            materials[cursor].setKa(QVector3D(x,y,z));
        }else if (((QString)splitLine.at(0)).compare("Kd") == 0){
            float x = (((QString)splitLine.at(1)).toFloat());
            float y = (((QString)splitLine.at(2)).toFloat());
            float z = (((QString)splitLine.at(3)).toFloat());
            materials[cursor].setKd(QVector3D(x,y,z));
        }else if (((QString)splitLine.at(0)).compare("Ks") == 0){
            float x = (((QString)splitLine.at(1)).toFloat());
            float y = (((QString)splitLine.at(2)).toFloat());
            float z = (((QString)splitLine.at(3)).toFloat());
            materials[cursor].setKs(QVector3D(x,y,z));
        }else if (((QString)splitLine.at(0)).compare("Ni") == 0){
            materials[cursor].setNi(((QString)splitLine.at(1)).toFloat());
        }else if (((QString)splitLine.at(0)).compare("d") == 0){
            materials[cursor].setD(((QString)splitLine.at(1)).toFloat());
        }else if (((QString)splitLine.at(0)).compare("illum") == 0){
            materials[cursor].setD(((QString)splitLine.at(1)).toFloat());
        }else if (((QString)splitLine.at(0)).compare("map_Kd") == 0){
            QString relativePath = ":/Resources/Texture/";
            relativePath += ((QString)splitLine.at(1));
            materials[cursor].loadMap_Kd(relativePath);
        }
    }

}

QVector3D Mesh::getMin_v() const
{
    return min_v;
}

QVector3D Mesh::getMax_v() const
{
    return max_v;
}

QVector3D Mesh::getCenter() const
{
    return center;
}

QOpenGLBuffer Mesh::getArrayBuf() const
{
    return arrayBuf;
}

QOpenGLBuffer Mesh::getIndexBuf() const
{
    return indexBuf;
}

QVector<Material> Mesh::getMaterials() const
{
    return materials;
}
