#include "scene.h"
#include <QtCore/qmath.h>




Scene::Scene(OpenGLWindow *oglWindow, InputHandler *input):
    openGLWindow(oglWindow),
    input(input)
{

    IG = true;

    /// INITIALISATION PHYSIQUE

    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.

    collisionConfiguration = new btDefaultCollisionConfiguration();

    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);

    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    overlappingPairCache = new btDbvtBroadphase();

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    solver = new btSequentialImpulseConstraintSolver;

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0, -100, 0));

    /// FIN INITIALISATION PHYSIQUE



    elapsedTimer.start();

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
    for(auto &g : gameObjects)
        delete g;

    delete debugCamera;
    if(followCamera != NULL) delete followCamera;
    delete texture;
    delete mesh;
}

void Scene::initScene()
{
    initShaders();
    initTextures();
    initBind();

    //hud = HUD::initFreeType();

    debugCamera = new FirstPersonCamera();
    mainCamera = debugCamera;
    mesh = new Mesh();
    mesh->objLoader(":/Resources/Models/cube.obj");


    if(IG)
    {
        RM.storeMesh("CarMesh", mesh);
        QQuaternion q = QQuaternion().fromEulerAngles(0,0,0);
        mCar = new Model("Car",QVector3D(0,100,0),q,QVector3D(5,2,10),mesh);
        mCar->addComponent(new ProgramShader(mCar));
        mCar->addComponent(new VehicleComponent(mCar,this));
        followCamera = new ThirdPersonCamera(mCar);
        mainCamera = followCamera;
        {
            //create a dynamic rigidbody
            btTriangleMesh *btMesh = new btTriangleMesh();
            QVector3D scale = mCar->getComponent<Transform>()->getScale();
            QVector3D position = mCar->getComponent<Transform>()->getPosition();
            QQuaternion q = mCar->getComponent<Transform>()->getRotation();

            mesh->meshToCollisionShape(btMesh);

            btGImpactMeshShape* colShape = new btGImpactMeshShape(btMesh);
            colShape->setLocalScaling(btVector3(scale.x(),scale.y(),scale.z()));
            colShape->updateBound();
            /// Create Dynamic Objects
            btTransform startTransform;
            startTransform.setIdentity();
            btScalar mass(30.0f);
            btVector3 btCenter(position.x(),position.y(),position.z());

            collisionShapes.push_back(colShape);


            //rigidbody is dynamic if and only if mass is non zero, otherwise static
            bool isDynamic = (mass != 0.f);

            btVector3 localInertia(0, 0, 0);
            if (isDynamic)
                colShape->calculateLocalInertia(mass, localInertia);


            //startTransform.setOrigin(btVector3(position.x(), position.y(), position.z()));
            startTransform.setOrigin(btCenter);
            startTransform.setRotation(btQuaternion(q.x(),q.y(),q.z(),q.scalar()));

            btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
            btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
            Rigidbody* body = new Rigidbody(mCar,rbInfo);
            mCar->addComponent(body);
            dynamicsWorld->addRigidBody(body);
            gameObjects.push_back(mCar);


        }
        initIGBind();
    }


    //loadScene();

    QQuaternion q = QQuaternion().fromEulerAngles(0,0,0);

    //quat rotation example
    float rotationAngle = qDegreesToRadians(90.0f);
    float x = 0.5f * qSin(rotationAngle / 2);
    float y = 0.0f * qSin(rotationAngle / 2);
    float z = 0.f * qSin(rotationAngle / 2);
    float w = cos(rotationAngle / 2);

    mesh = new Mesh();
    mesh->objLoader(":/Resources/Models/cube.obj");
    Model * m1,*m2,*m3;

    QString meshName = "SampleObject";
    RM.storeMesh(meshName,new Mesh());

    Mesh * sampleMesh = RM.retrieveMesh(meshName);

    sampleMesh->objLoader(":/Resources/Models/testcircuit.obj");
    m1 = new Model("Model",QVector3D(0,-100,0),q,QVector3D(500,500,500),sampleMesh);
    m1->addComponent(new ProgramShader(m1));

    m2 = new Model("Model",QVector3D(51,10,0),QQuaternion(),QVector3D(2,2,2),mesh);
    m2->addComponent(new ProgramShader(m2));



    gameObjects.push_back(m1);
    gameObjects.push_back(m2);

    {


        btTriangleMesh *btMesh = new btTriangleMesh();
        QVector3D scale = m1->getComponent<Transform>()->getScale();
        QVector3D position = m1->getComponent<Transform>()->getPosition();
        QQuaternion q = m1->getComponent<Transform>()->getRotation();

        sampleMesh->meshToCollisionShape(btMesh);
        shapeRoute = new btGImpactMeshShape(btMesh);
        shapeRoute->setLocalScaling(btVector3(scale.x(),scale.y(),scale.z()));
        shapeRoute->updateBound();

        collisionShapes.push_back(shapeRoute);

        /// Create Dynamic Objects
        btTransform startTransform;
        startTransform.setIdentity();
        btScalar mass(0.0f);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            shapeRoute->calculateLocalInertia(mass, localInertia);


        startTransform.setOrigin(btVector3(position.x(), position.y(), position.z()));
        startTransform.setRotation(btQuaternion(q.x(),q.y(),q.z(),q.scalar()));

        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shapeRoute, localInertia);
        Rigidbody* body = new Rigidbody(m1,rbInfo);
        m1->addComponent(body);
        dynamicsWorld->addRigidBody(body);
    }

    {
        //create a dynamic rigidbody

        btCollisionShape* colShape = new btBoxShape(btVector3(2,2,2));
        collisionShapes.push_back(colShape);

        /// Create Dynamic Objects
        btTransform startTransform;
        startTransform.setIdentity();

        btScalar mass(5.0f);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            colShape->calculateLocalInertia(mass, localInertia);

        startTransform.setOrigin(btVector3(51, 20, 0));

        //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
        Rigidbody* body = new Rigidbody(m2,rbInfo);
        m2->addComponent(body);
        dynamicsWorld->addRigidBody(body);

    }
    /*
    RM.storeMesh("Megamesh",new Mesh());

    Mesh * megamesh = RM.retrieveMesh("Megamesh");
    megamesh->objLoader(":/Resources/Models/La_zouzette.obj");
    m3 = new Model("Gaming",QVector3D(0,600,0),q,QVector3D(500,500,500),megamesh);
    m3->addComponent(new ProgramShader(m3));

    gameObjects.push_back(m3);



    {


        btTriangleMesh *btMesh = new btTriangleMesh();
        QVector3D scale = m3->getComponent<Transform>()->getScale();
        QVector3D position = m3->getComponent<Transform>()->getPosition();
        QQuaternion q = m3->getComponent<Transform>()->getRotation();

        megamesh->meshToCollisionShape(btMesh);
        btBvhTriangleMeshShape * niceshape = new btBvhTriangleMeshShape(btMesh,true);
        niceshape->setLocalScaling(btVector3(scale.x(),scale.y(),scale.z()));
        //niceshape->updateBound();

        collisionShapes.push_back(niceshape);

        /// Create Dynamic Objects
        btTransform startTransform;
        startTransform.setIdentity();
        btScalar mass(0.0f);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            niceshape->calculateLocalInertia(mass, localInertia);


        startTransform.setOrigin(btVector3(position.x(), position.y(), position.z()));
        startTransform.setRotation(btQuaternion(q.x(),q.y(),q.z(),q.scalar()));

        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, niceshape, localInertia);
        Rigidbody* body = new Rigidbody(m3,rbInfo);
        m1->addComponent(body);
        dynamicsWorld->addRigidBody(body);
    }*/




    skybox = new Skybox();
    skybox->initSkybox();
}

void Scene::initBind()
{


    input->bind(Qt::Key_C,new Command([&](State state){
                    if(state == PRESSED && mainCamera == debugCamera){
                        qDebug() << "IG Camera";
                        mainCamera = followCamera;
                        initIGBind();
                    }
                }));
    input->bind(Qt::Key_Z,new Command([&](State state){
                    if(mainCamera == debugCamera){
                        if(state == PRESSED || state == DOWN){
                            ((FirstPersonCamera*)mainCamera)->setMoveForward(true);
                        }
                    }
                }));
    input->bind(Qt::Key_S,new Command([&](State state){
                    if(mainCamera == debugCamera){
                        if(state == PRESSED || state == DOWN){
                            ((FirstPersonCamera*)mainCamera)->setMoveBackward(true);
                        }
                    }
                }));
    input->bind(Qt::Key_Q,new Command([&](State state){
                    if(mainCamera == debugCamera){

                        if(state == PRESSED || state == DOWN){
                            ((FirstPersonCamera*)mainCamera)->setMoveLeft(true);
                        }
                    }
                }));
    input->bind(Qt::Key_D,new Command([&](State state){
                    if(mainCamera == debugCamera){
                        if(state == PRESSED || state == DOWN){
                            ((FirstPersonCamera*)mainCamera)->setMoveRight(true);
                        }
                    }
                }));
    input->bind(Qt::Key_Shift,new Command([&](State state){
                    if(mainCamera == debugCamera){
                        if(state == PRESSED || state == DOWN){
                            ((FirstPersonCamera*)mainCamera)->setMoveDown(true);
                        }
                    }
                }));
    input->bind(Qt::Key_Space,new Command([&](State state){
                    if(mainCamera == debugCamera){
                        if(state == PRESSED || state == DOWN){
                            ((FirstPersonCamera*)mainCamera)->setMoveUpper(true);
                        }
                    }
                }));
    input->bind(Qt::LeftButton,new Command([&](State state){
                    if(mainCamera == debugCamera){
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
                                ((FirstPersonCamera*)mainCamera)->setV_mv(QVector2D(dx,dy));
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
                    }
                }));

}

void Scene::initIGBind()
{
    input->bind(Qt::Key_X,new Command([&](State state){
                    if(state == PRESSED && mainCamera == followCamera){
                        qDebug() << "Debug Camera";
                        mainCamera = debugCamera;
                        initBind();
                    }
                }));
    input->bind(Qt::Key_Z,new Command([&](State state){
                    if(mainCamera == followCamera){
                        if(state == PRESSED || state == DOWN){
                            mCar->getComponent<VehicleComponent>()->accelerate();
                        }
                    }
                }));
    input->bind(Qt::Key_S,new Command([&](State state){
                    if(mainCamera == followCamera){
                        if(state == PRESSED || state == DOWN){
                            mCar->getComponent<VehicleComponent>()->decelerate();
                        }
                    }
                }));
    input->bind(Qt::Key_Q,new Command([&](State state){
                    if(mainCamera == followCamera){
                        if(state == PRESSED || state == DOWN){
                            mCar->getComponent<VehicleComponent>()->turnLeft();
                        }
                    }
                }));
    input->bind(Qt::Key_D,new Command([&](State state){
                    if(mainCamera == followCamera){
                        if(state == PRESSED || state == DOWN){
                            mCar->getComponent<VehicleComponent>()->turnRight();
                        }
                    }
                }));
    input->bind(Qt::Key_Shift,new Command([&](State state){
                    if(mainCamera == followCamera){
                        if(state == PRESSED || state == DOWN){
                            mCar->getComponent<VehicleComponent>()->boostKey();
                        }
                    }
                }));
    input->bind(Qt::Key_Space,new Command([&](State state){
                    if(mainCamera == followCamera){
                        if(state == PRESSED || state == DOWN){
                            mCar->getComponent<VehicleComponent>()->actionKey();
                        }
                    }
                }));
    input->bind(Qt::Key_F,new Command([&](State state){
                    if(mainCamera == followCamera){
                        if(state == PRESSED){
                            Transform * transform = mCar->getComponent<Transform>();
                            Rigidbody * rig = mCar->getComponent<Rigidbody>();
                            QQuaternion q = transform->getRotation();
                            QVector3D rot = q.toEulerAngles();
                            q = QQuaternion::fromEulerAngles(rot.x(),rot.y(),0);
                            QVector3D pos = transform->getPosition();
                            pos.setY(pos.y()+100);
                            transform->setPosition(pos);
                            transform->setRotation(q);
                            btTransform btTrans = rig->getWorldTransform();
                            btTrans.setOrigin(btVector3(pos.x(),pos.y(),pos.z()));
                            btTrans.setRotation(btQuaternion(q.x(),q.y(),q.z(),q.scalar()));
                            rig->setWorldTransform(btTrans);
                            rig->setLinearVelocity(btVector3(0,0,0));
                            rig->setAngularVelocity(btVector3(0,0,0));
                        }
                    }
                }));
    input->bind(Qt::Key_R,new Command([&](State state){
                    if(mainCamera == followCamera){
                        if(state == PRESSED){
                            Transform * transform = mCar->getComponent<Transform>();
                            transform->setPosition(QVector3D(0,100,0));
                            transform->setRotation(QQuaternion());
                            Rigidbody * rig = mCar->getComponent<Rigidbody>();
                            btTransform btTrans = rig->getWorldTransform();
                            btTrans.setOrigin(btVector3(0.,100,0.));
                            btTrans.setRotation(btQuaternion());
                            rig->setWorldTransform(btTrans);
                            rig->setLinearVelocity(btVector3(0,0,0));
                            rig->setAngularVelocity(btVector3(0,0,0));
                        }
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


    float time_step = 1/(elapsedTimer.elapsed()/1000.0f);
    //qDebug() << 1/time_step;
    dynamicsWorld->stepSimulation(0.05, 60);
    elapsedTimer.restart();

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
    model.setToIdentity();
    mvp = mainCamera->getProjectionMatrix() * mainCamera->getViewMatrix() * model;
    program.setUniformValue("mvp_matrix", mvp);

    skybox->renderSkybox(&program);
}



Camera *Scene::getMainCamera() const
{
    return mainCamera;
}

FirstPersonCamera *Scene::getDebugCamera() const
{
    return debugCamera;
}

ThirdPersonCamera *Scene::getFollowCamera() const
{
    return followCamera;
}

btGImpactMeshShape *Scene::getShapeRoute() const
{
    return shapeRoute;
}

GameObject *Scene::getCar() const
{
    return mCar;
}
