#version 330

uniform sampler2D texture;
in vec2 v_texcoord;
in vec3 a_normal;



void main()
{

        gl_FragColor = texture2D(texture, v_texcoord);
}

