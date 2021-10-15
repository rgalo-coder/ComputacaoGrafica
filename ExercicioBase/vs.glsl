#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec3 Normal;    

uniform mat4 gWVP;
uniform mat4 gTrans;

mat4 gTotal = gWVP * gTrans ;

vec4 normalcorrigida;
vec3 normal3;

out vec3 Color;
out vec4 normal0;


void main()
{    
    gl_Position = gTotal * vec4(Position, 1.0);   
//    normalcorrigida = gTotal * vec4(Normal,1.0);
//    normal0 = vec3(normalcorrigida);   
    normal0 = vec4(Normal,0.0) ;
    Color = inColor;
}
