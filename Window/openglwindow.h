#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include "openglwindow.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
//#include <QQuaternion>
//#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

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

private:
    QBasicTimer timer;
    QOpenGLShaderProgram program;

    QMatrix4x4 projection;
};

#endif // MAINWIDGET_H
