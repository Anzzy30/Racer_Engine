#version 330

uniform sampler2D texture;
in vec2 v_texcoord;


void main()
{
    gl_FragColor = vec4(1,1,0,0);//texture2D(texture, v_texcoord);
}

