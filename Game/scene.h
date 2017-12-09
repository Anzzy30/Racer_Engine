#ifndef SCENE_H
#define SCENE_H


#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLTexture>

#include <QFile>

#include "GameObject/firstpersoncamera.h"
#include "GameObject/thirdpersoncamera.h"
#include "GameObject/planetest.h"
#include "Controller/inputhandler.h"
#include "Window/openglwindow.h"
#include "GameObject/model.h"
#include "Component/rigidbody.h"
#include "Component/vehiclecomponent.h"
#include "Utils/resourcemanager.h"

#ifdef QT_DEBUG
    #include <Logger/logger.h>
#endif

#include "external\bullet3-2.87\src\btBulletDynamicsCommon.h"

class OpenGLWindow;

class Scene : protected QOpenGLFunctions
{
public:
    Scene(OpenGLWindow *oglWindow, InputHandler *input);
    ~Scene();

    void initScene();

    void initBind();
    void initIGBind();
    void initShaders();
    void initTextures();
    void loadScene();
    btDiscreteDynamicsWorld * getWorld() {return dynamicsWorld;}

    void update();


    Camera *getMainCamera() const;

private:
    OpenGLWindow *openGLWindow;

    QOpenGLShaderProgram program;

    ThirdPersonCamera *mainCamera;
    InputHandler *input;
    PlaneTest *plane;
    QOpenGLTexture * texture;

    QVector<GameObject*> gameObjects;
    GameObject * mCar;

    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
    btAlignedObjectArray<btCollisionShape*> collisionShapes;
    Mesh *mesh;

    ResourceManager RM;

    bool IG = false;

    MeshRenderer * meshrend;
};

#endif // SCENE_H
