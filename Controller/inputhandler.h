#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <map>

#include <QOpenGLWidget>
#include <QKeyEvent>

#include "command.h"
#ifdef QT_DEBUG
    #include <Logger/logger.h>
#endif



class InputHandler
{
public:
    InputHandler();
    void bind(int key, Command *command);

    void update();

    void keyPressEvent(int key);
    void keyReleaseEvent(int key);

    void mousePressEvent(int button);
    void mouseReleaseEvent(int button);

private:
    /*key , action*/
    std::map<int,Command*> commands;
};

#endif // INPUTHANDLER_H
