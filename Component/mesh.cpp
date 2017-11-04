#include "mesh.h"
Mesh::Mesh() : indexBuf(QOpenGLBuffer::IndexBuffer)
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
    indexBuf.allocate(&indices[0], indices.size()*sizeof(GLuint));
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


void Mesh::drawMesh(QOpenGLShaderProgram *program)
{

    arrayBuf.bind();
    indexBuf.bind();
    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(QVector3D));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Draw plane geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);


}
