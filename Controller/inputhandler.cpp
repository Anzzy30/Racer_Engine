#include "inputhandler.h"

InputHandler::InputHandler()
{

}

InputHandler::~InputHandler()
{
    for (auto& command : this->commands) {
        delete command.second;
    }
}

void InputHandler::bind(int key, Command *command)
{
    if(commands.find(key) != commands.end()){
        delete commands.at(key);
        commands.erase(key);
    }
    commands.insert(std::pair<int,Command*>(key,command));
}

void InputHandler::update()
{

    for (auto& command : this->commands) {
        command.second->execute();
    }

}



void InputHandler::keyPressEvent(int key)
{

    std::map<int, Command*>::iterator iter = commands.find(key);
    if (iter != commands.end() )
    {
        commands.at(key)->setState(PRESSED);
    }
}

void InputHandler::keyReleaseEvent(int key)
{
    std::map<int, Command*>::iterator iter = commands.find(key);
    if (iter != commands.end() )
    {
        commands.at(key)->setState(RELEASED);
    }
}

void InputHandler::mousePressEvent(int button)
{
    std::map<int, Command*>::iterator iter = commands.find(button);
    if (iter != commands.end() )
    {
        commands.at(button)->setState(PRESSED);
    }
}

void InputHandler::mouseReleaseEvent(int button)
{
    std::map<int, Command*>::iterator iter = commands.find(button);
    if (iter != commands.end() )
    {
        commands.at(button)->setState(RELEASED);
    }
}




