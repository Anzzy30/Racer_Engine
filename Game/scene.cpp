#include "scene.h"
#include <QtCore/qmath.h>

Scene::Scene(OpenGLWindow *oglWindow, InputHandler *input):
    openGLWindow(oglWindow),
    input(input)
{
    mainCamera = new FirstPersonCamera();

}

Scene::~Scene()
{

    delete plane;
    for(auto &g : gameObjects)
        delete g;

    delete mainCamera;
    delete texture;
}

void Scene::initScene()
{
    initShaders();
    initTextures();
    initBind();


    plane = new PlaneTest();
    //quat rotation example
    float rotationAngle = qDegreesToRadians(90.0f);
    float x = 0.0f * qSin(rotationAngle / 2);
    float y = 0.0f * qSin(rotationAngle / 2);
    float z = 1.0f * qSin(rotationAngle / 2);
    float w = cos(rotationAngle / 2);

    Mesh *mesh = new Mesh();
    mesh->objLoader(":/Resources/Models/cube.obj");
    Model * m1,*m2;
    m1 = new Model(QVector3D(50,50,50),QQuaternion(),QVector3D(10,10,10),mesh,&program);
    m2 = new Model(QVector3D(0,0,0),QQuaternion(),QVector3D(2,2,2),mesh,&program);
    m1->addChild(m2);
    gameObjects.push_back(m1);
    gameObjects.push_back(m2);


}

void Scene::initBind()
{
    input->bind(Qt::Key_Z,new Command([&](State state){
                    if(state == PRESSED || state == DOWN){
                        mainCamera->setMoveForward(true);
                    }
                }));
    input->bind(Qt::Key_S,new Command([&](State state){
                    if(state == PRESSED || state == DOWN){
                        mainCamera->setMoveBackward(true);
                    }
                }));
    input->bind(Qt::Key_Q,new Command([&](State state){
                    if(state == PRESSED || state == DOWN){
                        mainCamera->setMoveLeft(true);
                    }
                }));
    input->bind(Qt::Key_D,new Command([&](State state){
                    if(state == PRESSED || state == DOWN){
                        mainCamera->setMoveRight(true);
                    }
                }));
    input->bind(Qt::Key_Shift,new Command([&](State state){
                    if(state == PRESSED || state == DOWN){
                        mainCamera->setMoveDown(true);
                    }
                }));
    input->bind(Qt::Key_Space,new Command([&](State state){
                    if(state == PRESSED || state == DOWN){
                        mainCamera->setMoveUpper(true);
                    }
                }));
    input->bind(Qt::LeftButton,new Command([&](State state){
                    switch(state){
                        case State::PRESSED:
                        {
                            QCursor cursor;
                            cursor.setShape(Qt::BlankCursor);
                            cursor.setPos(openGLWindow->mapToGlobal(QPoint(openGLWindow->width() / 2, openGLWindow->height() / 2)));
                            openGLWindow->setCursor(cursor);
                        }
                        break;
                        case State::DOWN:
                        {
                            QPoint pos = openGLWindow->mapFromGlobal(QCursor::pos());
                            float dx = pos.x()-openGLWindow->width()/2;
                            float dy = pos.y()-openGLWindow->height()/2;
                            mainCamera->setV_mv(QVector2D(dx,dy));
                            QCursor cursor;
                            cursor.setShape(Qt::BlankCursor);
                            cursor.setPos(openGLWindow->mapToGlobal(QPoint(openGLWindow->width() / 2, openGLWindow->height() / 2)));

                            openGLWindow->setCursor(cursor);
                        }
                        break;
                        case State::RELEASED:
                        {
                            QCursor cursor;
                            cursor.setShape(Qt::ArrowCursor);
                            openGLWindow->setCursor(cursor);
                        }
                        break;
                        case State::UP:

                        break;
                        default:
                        break;
                    }
                }));


}

void Scene::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Resources/Shader/vshader.glsl"))
        openGLWindow->close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Resources/Shader/fshader.glsl"))
        openGLWindow->close();

    // Link shader pipeline
    if (!program.link())
        openGLWindow->close();

    // Bind shader pipeline for use
    if (!program.bind())
        openGLWindow->close();
}

void Scene::initTextures()
{
    texture = new QOpenGLTexture(QImage(":/Resources/Texture/heightmap-3.png").mirrored());

    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    texture->setWrapMode(QOpenGLTexture::Repeat);

}

void Scene::update()
{
    input->update();
    mainCamera->update();
    qDebug() << mainCamera->getComponent<Transform>()->getPosition();
    texture->bind();
    QMatrix4x4 model;
    model.setToIdentity();
    QMatrix4x4 mvp =  mainCamera->getProjectionMatrix() * mainCamera->getViewMatrix() * model;
    program.setUniformValue("mvp_matrix", mvp);
    program.setUniformValue("texture", 0);
    plane->drawPlane(&program);

    for(auto &g : gameObjects){

        mvp = mainCamera->getProjectionMatrix() * mainCamera->getViewMatrix() * g->getModelMatrix();
        program.setUniformValue("mvp_matrix", mvp);
        g->update();
    }




}




FirstPersonCamera *Scene::getMainCamera() const
{
    return mainCamera;
}


