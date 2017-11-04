#ifndef COMPONENT_H
#define COMPONENT_H


class GameObject;

class Component
{
public:
    Component(GameObject* gameObject);
    virtual ~Component();

protected:

    GameObject* gameObject;
};

#endif // COMPONENT_H
