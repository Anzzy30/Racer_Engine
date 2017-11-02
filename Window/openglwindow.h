#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H
// STD includes
#include <cmath>

// Qt includes
#include <QCoreApplication>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QCursor>

// Program includes
#include <GameObject/firstpersoncamera.h>
#include <GameObject/planetest.h>
#include <Controller/inputhandler.h>
#include <Game/scene.h>
#ifdef QT_DEBUG
    #include <Logger/logger.h>
#endif

class Scene;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit OpenGLWindow(QWidget *parent = 0);
    ~OpenGLWindow();

protected:
    void timerEvent(QTimerEvent *e) override;

    void initializeGL() override;


    void keyPressEvent(QKeyEvent *event)override;
    void keyReleaseEvent(QKeyEvent *event)override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


    void resizeGL(int w, int h) override;
    void paintGL() override;


private:
    QBasicTimer timer;

    InputHandler *input;

    QOpenGLTexture *texture;

    Scene *scene;
};

#endif // MAINWIDGET_H
