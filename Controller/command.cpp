#include "command.h"

Command::Command(std::function<void(State state)> action):
    action(action)
{

}


void Command::execute()
{
    action(state);

    switch(state){
    case State::PRESSED:
        state = State::DOWN;
        break;
    case State::RELEASED:
        state = State::UP;
        break;
    default:
        break;
    }

}

void Command::setState(State state)
{
    this->state = state;
}

State Command::getState() const
{
    return state;
}
