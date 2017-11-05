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

    for(int i=0;i<faceCount;++i){
        line = in.readLine();
        fields = line.split(" ");
        Face f;
        f.count = ((QString)fields.at(0)).toInt();

        for(GLuint j=1;j<=f.count;++j){
            f.indices.push_back(((QString)fields.at(j)).toInt());
        }
        faces.push_back(f);
    }

    plyFile.close();

    center = min_v+(max_v-min_v)/2;

    facesToTriangle();

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
    QVector<QVector3D> tmp_normals;

    QVector<Vertex> vertexArray;
    int cpt = 0;
    while ((line = in.readLine()) != NULL)
    {
        if(line.at(0) == '#')
            continue;


        if(line.at(0) == 'o')
            continue;
        splitLine = line.split(" ");

        if (((QString)splitLine.at(0)).compare("v") == 0){
            QVector3D v;
            v.setX(((QString)splitLine.at(1)).toFloat());
            v.setY(((QString)splitLine.at(2)).toFloat());
            v.setZ(((QString)splitLine.at(3)).toFloat());
            if(cpt==0 || (v.x() < min_v.x() && v.y() < min_v.y() && v.z() < min_v.z() ))
                min_v = v;
            if(cpt==0 || (v.x() > max_v.x() && v.y() > max_v.y() && v.z() > max_v.z() ))
                max_v = v;
            vertices.push_back(v);
            cpt++;
        }else if(((QString)splitLine.at(0)).compare("vn") == 0){
            QVector3D n;
            n.setX(((QString)splitLine.at(1)).toFloat());
            n.setY(((QString)splitLine.at(2)).toFloat());
            n.setZ(((QString)splitLine.at(3)).toFloat());
            tmp_normals.push_back(n);
        }else if(((QString)splitLine.at(0)).compare("f") == 0){
            Face f;
            f.count = 0;

            for(auto const& field : splitLine){

                if(field.compare("") == 0 || field.compare("f")==0){
                    continue;
                }
                QStringList vertexData = field.split("//");
                f.count++;

                f.indices.push_back(((QString)vertexData.at(0)).toInt());



            }
            faces.push_back(f);
        }
    }

    facesToTriangle();

    objFile.close();

    center = min_v+(max_v-min_v)/2;



    arrayBuf.bind();
    arrayBuf.allocate(&vertices[0], vertices.size() * sizeof(QVector3D));

    indexBuf.bind();
    indexBuf.allocate(&indices[0], indices.size() * sizeof(GLuint));

}

void Mesh::facesToTriangle(){
    for(auto const& face: faces) {

        if(face.count >= 3){
            for(GLuint i=1;i<face.count-1;++i){

                indices.push_back(face.indices[0]);
                indices.push_back(face.indices[i]);
                indices.push_back(face.indices[i+1]);
            }
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
