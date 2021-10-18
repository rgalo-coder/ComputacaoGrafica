#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec3 Normal;    

uniform mat4 gWVP;
uniform mat4 gTrans;
uniform vec3 gLuz;
uniform vec3 gDirLuz;

mat4 gTotal = gWVP * gTrans ;
vec4 luzcorrigida;

out vec3 normalCorrigida;
out vec3 Color;
out vec3 vertPos;


void main()
{    


//    float cosO;
//    vec3 coefiluminacao;
//    luzcorrigida =  vec4( gDirLuz,1.0);
//    normalcorrigida = vec3(inverse(gTotal) * vec4(Normal, 0.0));
//
//    cosO = dot(normalize(normalcorrigida) , - vec3(luzcorrigida) );
//    if (cosO > 0) {
//        coefiluminacao = gLuz * (0.7 * cosO + 0.3);        
//    }
//    else {
//        coefiluminacao = vec3(0,0,0) + 0.3;
//    }
//    Color = vec3(inColor * coefiluminacao );

    gl_Position = gTotal * vec4(Position, 1.0); 
    normalCorrigida = vec3(inverse(gTotal) * vec4(Normal, 0.0));
   
    Color = inColor;
    vec4 vertPos4 = gWVP * vec4(Position, 1.0);
    vertPos = vec3(vertPos4) / vertPos4.w;
}
