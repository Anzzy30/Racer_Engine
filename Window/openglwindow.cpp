#include "openglwindow.h"

#include <QCoreApplication>

#include <math.h>

OpenGLWindow::OpenGLWindow(QWidget *parent) :
    QOpenGLWidget(parent)
{

}

OpenGLWindow::~OpenGLWindow()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    //delete texture;
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


    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
}


void OpenGLWindow::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}


void OpenGLWindow::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 0.1, zFar = 3000.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}


void OpenGLWindow::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    //texture->bind();

    QMatrix4x4 matrix;
    matrix.rotate(0.0f,0.0f,0.0f,0.0f);
    matrix.translate(0.0f, 0.0f, 0.0f);
    matrix.rotate(45.0f,-45.0f,0.0f,0.0f);

}
