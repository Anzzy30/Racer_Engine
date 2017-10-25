QT += core gui widgets
CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    Window/openglwindow.cpp \
    Logger/logger.cpp

HEADERS += \
    Window/openglwindow.h \
    Logger/logger.h

RESOURCES += \
    Shader/shaders.qrc

LIBS += -lopengl32
