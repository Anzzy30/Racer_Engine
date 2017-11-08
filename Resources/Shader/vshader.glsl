#version 330

uniform mat4 mvp_matrix;
in vec4 a_position;
in vec2 a_texcoord;
in vec3 a_normal;
out vec2 v_texcoord;
out vec3 v_normal;

void main()
{
    gl_Position =  mvp_matrix * a_position;


    v_texcoord = a_texcoord;
    v_normal = a_normal;
}
