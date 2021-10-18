#version 330

struct Material
{
    float ka,kd,ks,shininess;
};

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec3 Normal;    

uniform mat4 gWVP;
uniform mat4 gTrans;
uniform vec3 gLuz;
uniform vec3 gDirLuz;
uniform int modoIluminacao;
uniform Material gMaterial;

mat4 gTotal = gWVP * gTrans ;
vec4 luzcorrigida;
float cosO;
vec3 corFinal;
vec4 luzCorrigida;
vec3 corAmbiente,corDifusa,corEspecular;
vec3 ia,id,is;

out vec3 normalCorrigida;
out vec3 Color;
out vec3 vertPos;
flat out vec3 corFlat;



vec3 CalcularGouraud()
{
    vec3 corSaida;
    corAmbiente = inColor;
    corEspecular = vec3(1.0,1.0,1.0);
    corDifusa = Color;
    luzCorrigida =  gWVP * vec4( gDirLuz,1.0);

    vec3 N = normalize(normalCorrigida);
    vec3 L =  normalize( vec3(luzCorrigida)-vertPos ) ;
    cosO = max(dot(N , L ),0);

    ia = gMaterial.ka * corAmbiente;  

    if (cosO > 0) {
        vec3 R = reflect(-L,N);
        vec3 V = normalize(-vertPos);

        id = gMaterial.kd * cosO * corDifusa;

        float anguloEspecular = max(dot(R, V), 0.0);
        is = gMaterial.ks*pow(anguloEspecular, gMaterial.shininess) * corEspecular;
        corSaida = ia+id+is;
    }
    else 
    {
        corSaida = ia;
    }
    return corSaida;

}

void main()
{    

    gl_Position = gTotal * vec4(Position, 1.0); 
    normalCorrigida = vec3(inverse(gTotal) * vec4(Normal, 0.0));  
  
    vec4 vertPos4 = gWVP * vec4(Position, 1.0);
    vertPos = vec3(vertPos4) / vertPos4.w;

    if (modoIluminacao==3 )
        Color = inColor;
    if (modoIluminacao==2 || modoIluminacao==1)
    {
        Color=CalcularGouraud();
        corFlat = Color;
      
    }
}
