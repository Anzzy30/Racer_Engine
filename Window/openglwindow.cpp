#include "openglwindow.h"


OpenGLWindow::OpenGLWindow(QWidget *parent) :
    QOpenGLWidget(parent)
{
#ifdef QT_DEBUG
    qDebug() << "OpenGLWindow.cpp => OpenGLWindow();";
#endif
    input = new InputHandler();
    scene = new Scene(this,input);
}

OpenGLWindow::~OpenGLWindow()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete scene;
    doneCurrent();
}

void OpenGLWindow::timerEvent(QTimerEvent *)
{
#ifdef QT_DEBUG
    Logger::Debug("Update tick",7);
#endif
    update();
}



void OpenGLWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

    scene->initScene();
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glDisable(GL_CULL_FACE);

    int msec = 1000/60;
    timer.start(msec, this);

    scene->getMainCamera()->update();

    qreal aspect = qreal(this->size().width()) / qreal(this->size().height());
    const qreal zNear = 0.1, zFar = 1000.0, fov = 45.0;
    QMatrix4x4 projection;
    projection.perspective(fov, aspect, zNear, zFar);

    scene->getMainCamera()->setProjectionMatrix(projection);


}



/*                Keyboard and Mouse Event        */

void OpenGLWindow::mousePressEvent(QMouseEvent *event)
{
    input->mousePressEvent(event->button());

}
void OpenGLWindow::mouseReleaseEvent(QMouseEvent *event)
{
    input->mouseReleaseEvent(event->button());
}
void OpenGLWindow::keyPressEvent(QKeyEvent *event)
{
    input->keyPressEvent(event->key());
}
void OpenGLWindow::keyReleaseEvent(QKeyEvent *event)
{
    input->keyReleaseEvent(event->key());
}

/*Init bind camera*/
/*=============================================== */

void OpenGLWindow::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.1, zFar = 1000.0, fov = 45.0;

    QMatrix4x4 projection;
    projection.perspective(fov, aspect, zNear, zFar);
    scene->getMainCamera()->setProjectionMatrix(projection);

}




void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->update();

}
