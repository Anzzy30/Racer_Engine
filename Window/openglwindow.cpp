#include "openglwindow.h"


OpenGLWindow::OpenGLWindow(QWidget *parent) :
    QOpenGLWidget(parent),
    plane(0),
    texture(0)
{
#ifdef QT_DEBUG
    qDebug() << "OpenGLWindow.cpp => OpenGLWindow();";
#endif
    input = new InputHandler();

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
#ifdef QT_DEBUG
    Logger::Debug("Update tick",7);
#endif
    update();
    input->update();
    camera.update();
}



void OpenGLWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();
    initBind();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glDisable(GL_CULL_FACE);


    int msec = 1000/60;
    timer.start(msec, this);
    plane = new PlaneTest();

    camera.update();
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


/*                Keyboard and Mouse Event        */

void OpenGLWindow::mousePressEvent(QMouseEvent *event)
{
    QMouseEvent *cast = dynamic_cast<QMouseEvent *>(event);
    if(cast)
        input->mousePressEvent(cast->button());

}

void OpenGLWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QMouseEvent *cast = dynamic_cast<QMouseEvent *>(event);
    if(cast)
        input->mouseReleaseEvent(cast->button());

}
//! [0]



void OpenGLWindow::keyPressEvent(QKeyEvent *event)
{
    QKeyEvent *cast = dynamic_cast<QKeyEvent *>(event);
    if(cast){
        input->keyPressEvent(cast->key());
    }
}

void OpenGLWindow::keyReleaseEvent(QKeyEvent *event)
{
    QKeyEvent *cast = dynamic_cast<QKeyEvent *>(event);
    if(cast){
        input->keyReleaseEvent(cast->key());
    }
}

/*Init bind camera*/
void OpenGLWindow::initBind(){
    input->bind(Qt::Key_Z,new Command([&](State state){
                    if(state == PRESSED || state == DOWN){
                        camera.setMoveForward(true);
                    }
                }));
    input->bind(Qt::Key_S,new Command([&](State state){
                    if(state == PRESSED || state == DOWN){
                        camera.setMoveBackward(true);
                    }
                }));
    input->bind(Qt::Key_Q,new Command([&](State state){
                    if(state == PRESSED || state == DOWN){
                        camera.setMoveLeft(true);
                    }
                }));
    input->bind(Qt::Key_D,new Command([&](State state){
                    if(state == PRESSED || state == DOWN){
                        camera.setMoveRight(true);
                    }
                }));
    input->bind(Qt::Key_Shift,new Command([&](State state){
                    if(state == PRESSED || state == DOWN){
                        camera.setMoveDown(true);
                    }
                }));
    input->bind(Qt::Key_Space,new Command([&](State state){
                    if(state == PRESSED || state == DOWN){
                        camera.setMoveUpper(true);
                    }
                }));
    input->bind(Qt::LeftButton,new Command([&](State state){
                    switch(state){
                        case State::PRESSED:
                        {
                            QCursor cursor;
                            cursor.setShape(Qt::BlankCursor);
                            cursor.setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
                            setCursor(cursor);
                        }
                        break;
                        case State::DOWN:
                        {
                            QPoint pos = mapFromGlobal(QCursor::pos());
                            float dx = pos.x()-width()/2;
                            float dy = pos.y()-height()/2;
                            camera.setV_mv(QVector2D(dx,dy));
                            QCursor cursor;
                            cursor.setShape(Qt::BlankCursor);
                            cursor.setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));

                            setCursor(cursor);
                        }
                        break;
                        case State::RELEASED:
                        {
                            QCursor cursor;
                            cursor.setShape(Qt::ArrowCursor);
                            setCursor(cursor);
                        }
                        break;
                        case State::UP:

                        break;
                        default:
                        break;
                    }
                }));

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    /*========================================================*/
    /*Test camera et plane*/
    texture->bind();
    QMatrix4x4 mvp = camera.getProjectionMatrix()*camera.getViewMatrix();
    program.setUniformValue("mvp_matrix", mvp);
    program.setUniformValue("texture", 0);

    plane->drawPlane(&program);
    /*========================================================*/
}
