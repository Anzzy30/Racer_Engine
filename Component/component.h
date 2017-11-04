#ifndef COMPONENT_H
#define COMPONENT_H


class GameObject;

class Component
{
public:
    Component(GameObject* gameObject);
    virtual ~Component();

    virtual void update() = 0;

protected:

    GameObject* gameObject;
};

#endif // COMPONENT_H
