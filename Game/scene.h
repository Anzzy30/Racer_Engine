#ifndef SCENE_H
#define SCENE_H


#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLTexture>

#include "GameObject/firstpersoncamera.h"
#include "GameObject/planetest.h"
#include "Controller/inputhandler.h"
#include "Window/openglwindow.h"
#include "GameObject/meshtest.h"
class OpenGLWindow;

class Scene : protected QOpenGLFunctions
{
public:
    Scene(OpenGLWindow *oglWindow, InputHandler *input);
    ~Scene();

    void initScene();

    void initBind();
    void initShaders();
    void initTextures();

    void update();


    FirstPersonCamera *getMainCamera() const;

private:
    OpenGLWindow *openGLWindow;

    QOpenGLShaderProgram program;

    FirstPersonCamera *mainCamera;
    InputHandler *input;
    PlaneTest *plane;
    QOpenGLTexture * texture;

    QVector<GameObject*> gameObjects;
};

#endif // SCENE_H
