QT += core gui widgets
CONFIG += c++11 console
CONFIG -= app_bundle
CONFIG += resources_big

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    Window/openglwindow.cpp \
    Logger/logger.cpp \
    GameObject/camera.cpp \
    GameObject/gameobject.cpp \
    GameObject/firstpersoncamera.cpp \
    GameObject/planetest.cpp \
    Controller/inputhandler.cpp \
    Controller/command.cpp \
    Game/scene.cpp \
    Utils/mesh.cpp \
    GameObject/meshtest.cpp \
    Component/component.cpp \
    Component/transform.cpp \
    Component/meshrenderer.cpp \
    Utils/material.cpp

HEADERS += \
    Window/openglwindow.h \
    Logger/logger.h \
    GameObject/camera.h \
    GameObject/gameobject.h \
    GameObject/firstpersoncamera.h \
    GameObject/planetest.h \
    Controller/inputhandler.h \
    Controller/command.h \
    Game/scene.h \
    Utils/mesh.h \
    GameObject/meshtest.h \
    Component/component.h \
    Component/transform.h \
    Component/meshrenderer.h \
    Utils/material.h

RESOURCES += \
    shaders.qrc \
    textures.qrc \
    models.qrc

LIBS += -lopengl32

