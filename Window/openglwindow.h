#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <GameObject/firstpersoncamera.h>
#include <GameObject/planetest.h>

class PlaneTest;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit OpenGLWindow(QWidget *parent = 0);
    ~OpenGLWindow();

protected:
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();

    /*=============================================== */
    /*Supprimer et faire une classe material pour les textures */
    void initTextures();
    /*=============================================== */

private:
    QBasicTimer timer;
    QOpenGLShaderProgram program;



    FirstPersonCamera camera;
    PlaneTest *plane;
    QOpenGLTexture *texture;



};

#endif // MAINWIDGET_H
