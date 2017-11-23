#ifndef SCENE_H
#define SCENE_H


#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLTexture>

#include <QFile>

#include "GameObject/firstpersoncamera.h"
#include "GameObject/planetest.h"
#include "Controller/inputhandler.h"
#include "Window/openglwindow.h"
#include "GameObject/model.h"

#ifdef QT_DEBUG
    #include <Logger/logger.h>
#endif


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
    void loadScene();

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


    MeshRenderer * meshrend;
};

#endif // SCENE_H
