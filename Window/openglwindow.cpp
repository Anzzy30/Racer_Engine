#include "openglwindow.h"

#include <QCoreApplication>

#include <math.h>
#include <iostream>
OpenGLWindow::OpenGLWindow(QWidget *parent) :
    QOpenGLWidget(parent),
    plane(0),
    texture(0)
{
#ifdef QT_NO_DEBUG
    // release mode code
#else
    qDebug() << "OpenGLWindow.cpp => OpenGLWindow();";
#endif
}

OpenGLWindow::~OpenGLWindow()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete plane;
    doneCurrent();
}

void OpenGLWindow::timerEvent(QTimerEvent *)
{
    update();
}


void OpenGLWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glDisable(GL_CULL_FACE);


    int msec = 1000/60;
    timer.start(msec, this);
    plane = new PlaneTest();

    camera.move(0,0,0,0,0,0,0);
    qreal aspect = qreal(this->size().width()) / qreal(this->size().height());
    const qreal zNear = 0.1, zFar = 1000.0, fov = 45.0;
    QMatrix4x4 projection;
    projection.perspective(fov, aspect, zNear, zFar);
    camera.setProjectionMatrix(projection);


}


void OpenGLWindow::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Resources/Shader/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Resources/Shader/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}

/*=============================================== */
/*Supprimer et faire une classe material pour les textures */
void OpenGLWindow::initTextures()
{
    texture = new QOpenGLTexture(QImage(":/Resources/Texture/heightmap-3.png").mirrored());

    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    texture->setWrapMode(QOpenGLTexture::Repeat);
}
/*=============================================== */

void OpenGLWindow::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.1, zFar = 1000.0, fov = 45.0;

    QMatrix4x4 projection;
    projection.perspective(fov, aspect, zNear, zFar);
    camera.setProjectionMatrix(projection);

}




void OpenGLWindow::paintGL()
{
    glViewport(0,0,this->size().width(),this->size().height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.move(0,0,0,0,0,0,0);
    /*========================================================*/
    /*Test camera et plane*/
    texture->bind();
    QMatrix4x4 mvp = camera.getProjectionMatrix()*camera.getViewMatrix();
    program.setUniformValue("mvp_matrix", mvp);
    program.setUniformValue("texture", 0);

    plane->drawPlane(&program);
    /*========================================================*/
}
