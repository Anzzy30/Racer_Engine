#ifndef COMMAND_H
#define COMMAND_H
#include <functional>

enum State
{
    PRESSED,
    RELEASED,
    DOWN,
    UP
};

class Command
{
public:
    Command(std::function<void(State state)> action);
    void execute();

    State getState() const;
    void setState(State state);


private:
    State state = UP;
    std::function<void(State state)> action;
};

#endif // COMMAND_H
