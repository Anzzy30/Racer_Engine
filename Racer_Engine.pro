QT += core gui widgets
CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    Window/openglwindow.cpp \
<<<<<<< HEAD
    Logger/logger.cpp
=======
    Logger/logger.cpp \
    GameObject/camera.cpp
>>>>>>> bd6c8b737bc555c2aaaf0f239f44114bd1ae2893

HEADERS += \
    Window/openglwindow.h \
    Logger/logger.h \
    GameObject/camera.h

RESOURCES += \
    Shader/shaders.qrc

LIBS += -lopengl32
