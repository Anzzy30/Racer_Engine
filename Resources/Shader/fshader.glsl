#version 330

uniform sampler2D texture;
in vec2 v_texcoord;
in vec3 a_normal;



void main()
{
    if(v_texcoord.x == 0 && v_texcoord.y==0)
        gl_FragColor = vec4(1,1,1,1);
    else
        gl_FragColor = texture2D(texture, v_texcoord);
}

