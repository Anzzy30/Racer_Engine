#include "programshader.h"

ProgramShader::ProgramShader(GameObject *gameObject):
    Component(gameObject)
{

}

void ProgramShader::update()
{

}

void ProgramShader::setProgram(QOpenGLShaderProgram *value)
{
    program = value;
}

QOpenGLShaderProgram *ProgramShader::getProgram() const
{
    return program;
}
