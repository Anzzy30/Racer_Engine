#ifndef SKYBOX_H
#define SKYBOX_H
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "Utils/mesh.h"

class Skybox : protected  QOpenGLFunctions
{
public:
    Skybox();
    ~Skybox();

    void initSkybox();
    void renderSkybox(QOpenGLShaderProgram *shader);
private:
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    QOpenGLTexture *skyboxTexture;

    int scale;
};

#endif // SKYBOX_H
