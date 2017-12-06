#ifndef PROGRAMSHADER_H
#define PROGRAMSHADER_H



#include <QOpenGLShaderProgram>


#include "Component/component.h"
#include "Utils/mesh.h"
class Component;

class ProgramShader : public Component
{
public:
    ProgramShader(GameObject *gameObject);

    virtual void update();


    void setProgram(QOpenGLShaderProgram *value);

    QOpenGLShaderProgram *getProgram() const;

private:
    QOpenGLShaderProgram *program;

};

#endif // PROGRAMSHADER_H
