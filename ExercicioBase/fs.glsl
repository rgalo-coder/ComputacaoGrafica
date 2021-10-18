#version 330

struct Material
{
    float ka,kd,ks,shininess;
};


uniform vec3 gLuz;
uniform vec3 gDirLuz;
uniform mat4 gWVP;
uniform mat4 gTrans;
uniform int modoIluminacao;
//uniform float ka,kd,ks,shininess;
uniform Material gMaterial;

in vec3 Color;
in vec4 normal0;
in vec3 vertPos;
in vec3 normalCorrigida;

float cosO;
vec3 corFinal;
vec4 luzCorrigida;
vec3 corAmbiente,corDifusa,corEspecular;
vec3 ia,id,is;

out vec4 gl_FragColor;


vec3 CalcularPhong()
{
    vec3 corSaida;
//    ka=0.1;
//    kd= 0.9;
//    ks=0.9;
//    shininess=80;
    corAmbiente = Color;
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
    if (modoIluminacao==3)
        gl_FragColor = vec4(CalcularPhong(), 1.0) ;
    else
        gl_FragColor = vec4(corFinal, 1.0) ;

 // FragColor = vec4(Color , 1.0) ;
}

