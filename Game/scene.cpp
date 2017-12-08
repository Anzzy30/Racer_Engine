#include "scene.h"
#include <QtCore/qmath.h>



Scene::Scene(OpenGLWindow *oglWindow, InputHandler *input):
    openGLWindow(oglWindow),
    input(input)
{
    mainCamera = new FirstPersonCamera();

    /// INITIALISATION PHYSIQUE

    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    collisionConfiguration = new btDefaultCollisionConfiguration();

    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    dispatcher = new btCollisionDispatcher(collisionConfiguration);

    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    overlappingPairCache = new btDbvtBroadphase();

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    solver = new btSequentialImpulseConstraintSolver;

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0, -10, 0));

    /// FIN INITIALISATION PHYSIQUE

}

Scene::~Scene()
{
    /// CLEANUP PHYSIQUE
    for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
    {
        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if (body && body->getMotionState())
        {
            delete body->getMotionState();
        }
        dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }

    //delete collision shapes
    for (int j = 0; j < collisionShapes.size(); j++)
    {
        btCollisionShape* shape = collisionShapes[j];
        collisionShapes[j] = 0;
        delete shape;
    }

    //delete dynamics world
    delete dynamicsWorld;

    //delete solver
    delete solver;

    //delete broadphase
    delete overlappingPairCache;

    //delete dispatcher
    delete dispatcher;

    delete collisionConfiguration;

    //next line is optional: it will be cleared by the destructor when the array goes out of scope
    collisionShapes.clear();

    /// FIN CLEANUP PHYSIQUE
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

    //loadScene();


    plane = new PlaneTest();
    QQuaternion q = QQuaternion().fromEulerAngles(30,0,0);

    //quat rotation example

    {
        btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

        collisionShapes.push_back(groundShape);

        btTransform groundTransform;
        groundTransform.setIdentity();
        groundTransform.setOrigin(btVector3(0, -56, 0));
        btQuaternion qq;
        qq.setW(btScalar(q.scalar()));
        qq.setX(btScalar(q.x()));
        qq.setY(btScalar(q.y()));
        qq.setZ(btScalar(q.z()));
        groundTransform.setRotation(qq);

        btScalar mass(0.);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            groundShape->calculateLocalInertia(mass, localInertia);

        //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
        btRigidBody* body = new btRigidBody(rbInfo);

        //add the body to the dynamics world
        dynamicsWorld->addRigidBody(body);
    }

    {
        //create a dynamic rigidbody

        //btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
        btCollisionShape* colShape = new btSphereShape(btScalar(2.));
        collisionShapes.push_back(colShape);

        /// Create Dynamic Objects
        btTransform startTransform;
        startTransform.setIdentity();

        btScalar mass(10.f);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            colShape->calculateLocalInertia(mass, localInertia);

        startTransform.setOrigin(btVector3(51, 20, 0));

        //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
        btRigidBody* body = new btRigidBody(rbInfo);

        dynamicsWorld->addRigidBody(body);
    }



    float rotationAngle = qDegreesToRadians(90.0f);
    float x = 0.5f * qSin(rotationAngle / 2);
    float y = 0.0f * qSin(rotationAngle / 2);
    float z = 0.f * qSin(rotationAngle / 2);
    float w = cos(rotationAngle / 2);

    Mesh *mesh = new Mesh();
    mesh->objLoader(":/Resources/Models/cube.obj");
    Model * m1,*m2;
    m1 = new Model("Model",QVector3D(0,-56,0),q,QVector3D(50,50,50),mesh);
    m1->addComponent(new ProgramShader(m1));
    //m1->addComponent(new Rigidbody(m1));
    m2 = new Model("Model",QVector3D(51,10,0),QQuaternion(),QVector3D(2,2,2),mesh);
    m2->addComponent(new ProgramShader(m2));
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

void Scene::loadScene()
{
    QFile file(":/scene.scn");
    if(!file.open(QIODevice::ReadOnly| QIODevice::Text)) {
        #ifdef QT_DEBUG
            Logger::Warning(file.errorString()+ ": Can't load scene.scn",0);
        #endif
    }

    QTextStream in(&file);
    Model * obj;
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ");

            if (fields.at(0) == "Model")
            {
                if (fields.size() != 11)
                {
                #ifdef QT_DEBUG
                    Logger::Warning(" Malformed statment in scene.scn: " + QString::number(fields.size()),0);
                #endif
                }
                else
                {
                    QString path = fields.at(1);
                    float x = fields.at(2).toFloat();
                    float y = fields.at(3).toFloat();
                    float z = fields.at(4).toFloat();
                    float rx = (fields.at(5).toFloat());
                    float ry = (fields.at(6).toFloat());
                    float rz = (fields.at(7).toFloat());
                    float sx = fields.at(8).toFloat();
                    float sy = fields.at(9).toFloat();
                    float sz = fields.at(10).toFloat();
                    Mesh *mesh = new Mesh();
                    mesh->objLoader(path);
                    QQuaternion q = QQuaternion().fromEulerAngles(rx,ry,rz);
                    obj = new Model(QString("Model"),QVector3D(x,y,z),q,QVector3D(sx,sy,sz),mesh);
                    gameObjects.push_back(obj);
                }
            }
            else if (fields.at(0) == "ChildModel")
            {
                if (fields.size() != 11)
                {
                #ifdef QT_DEBUG
                    Logger::Warning(" Malformed statment in scene.scn: " + QString::number(fields.size()),0);
                #endif
                }
                else
                {
                    Model * child;
                    QString path = fields.at(1);
                    float x = fields.at(2).toFloat();
                    float y = fields.at(3).toFloat();
                    float z = fields.at(4).toFloat();
                    float rx = (fields.at(5).toFloat());
                    float ry = (fields.at(6).toFloat());
                    float rz = (fields.at(7).toFloat());
                    float sx = fields.at(8).toFloat();
                    float sy = fields.at(9).toFloat();
                    float sz = fields.at(10).toFloat();
                    Mesh *mesh = new Mesh();
                    mesh->objLoader(path);
                    QQuaternion q = QQuaternion().fromEulerAngles(rx,ry,rz);

                    child = new Model(QString("Model"),QVector3D(x,y,z),q,QVector3D(sx,sy,sz),mesh);
                    obj->addChild(child);
                    gameObjects.push_back(child);
                }
            }
            else if (fields.at(0) == "Camera")
            {
                if (fields.size() != 6)
                {
                #ifdef QT_DEBUG
                    Logger::Warning(" Malformed statment in scene.scn: " + QString::number(fields.size()),0);
                #endif
                }
                else
                {
                    float x = fields.at(1).toFloat();
                    float y = fields.at(2).toFloat();
                    float z = fields.at(3).toFloat();
                    float pitch = fields.at(4).toFloat();
                    float yaw = fields.at(5).toFloat();
                    mainCamera->getComponent<Transform>()->setPosition(QVector3D(x,y,z));
                    mainCamera->setPitch(pitch);
                    mainCamera->setYaw(yaw);
                }
            }
        }

    file.close();
}


void Scene::update()
{
    /// TEST PHYSIQUE

    dynamicsWorld->stepSimulation(1.f / 30.f, 10);

    //print positions of all objects
    for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
    {
        btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
        btRigidBody* body = btRigidBody::upcast(obj);
        btTransform trans;
        if (body && body->getMotionState())
        {
            body->getMotionState()->getWorldTransform(trans);
        }
        else
        {
            trans = obj->getWorldTransform();
        }
        if (j==1)
        {
            printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
            GameObject* m = gameObjects.at(1);
            m->getComponent<Transform>()->setPosition(QVector3D(trans.getOrigin().getX(),trans.getOrigin().getY(),trans.getOrigin().getZ()));
            m->getComponent<Transform>()->setRotation(QQuaternion(trans.getRotation().getW(),QVector3D(trans.getRotation().getX(),trans.getRotation().getY(),trans.getRotation().getZ())));
        }
    }

    /// FIN TEST PHYSIQUE

    input->update();
    mainCamera->update();

    texture->bind();
    QMatrix4x4 model;
    model.setToIdentity();
    QMatrix4x4 mvp =  mainCamera->getProjectionMatrix() * mainCamera->getViewMatrix() * model;
    program.setUniformValue("mvp_matrix", mvp);
    program.setUniformValue("texture", 0);
    //plane->drawPlane(&program);


    for(auto &g : gameObjects){
        ProgramShader *p = g->getComponent<ProgramShader>();




        if(!p)
            continue;
        p->setProgram(&program);
        mvp = mainCamera->getProjectionMatrix() * mainCamera->getViewMatrix() * g->getModelMatrix();
        program.setUniformValue("mvp_matrix", mvp);
        g->update();

    }


}




FirstPersonCamera *Scene::getMainCamera() const
{
    return mainCamera;
}


