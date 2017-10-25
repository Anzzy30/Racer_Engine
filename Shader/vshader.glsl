#version 330

uniform mat4 mvp_matrix;
in vec4 a_position;

//! [0]
void main()
{
    gl_Position = mvp_matrix * a_position;
}
//! [0]
