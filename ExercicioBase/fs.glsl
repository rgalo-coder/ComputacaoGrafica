#version 330

in vec3 Color;
in vec4 normal0;

uniform vec3 gLuz;
uniform vec3 gDirLuz;

uniform mat4 gWVP;
uniform mat4 gTrans;

out vec4 FragColor;

float cosO;
vec3 coefiluminacao;
vec4 luzcorrigida;
vec3 normalcorrigida;

void main()
{   
    luzcorrigida =  vec4( gDirLuz,1.0);
    normalcorrigida = vec3(gTrans * normal0);

    cosO = dot(normalize(normalcorrigida) , - vec3(luzcorrigida) );
    if (cosO > 0) {
        coefiluminacao = gLuz * (0.7 * cosO + 0.3);        
    }
    else {
        coefiluminacao = vec3(0,0,0) + 0.3;
    }
    FragColor = vec4(Color * coefiluminacao, 1.0) ;
}

