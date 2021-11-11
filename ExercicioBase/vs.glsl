#version 330

struct Material
{
    float ka,kd,ks,shininess;
};

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec3 Normal;    

uniform mat4 gWVP;
uniform mat4 gModel;
uniform mat4 LightSpaceMatrix;
uniform vec3 gCorLuz;
uniform vec3 gPosLuz;
uniform int modoIluminacao;
uniform Material gMaterial;
uniform int modoShadowMap;   
uniform sampler2D depthMap;

mat4 gTotal = gWVP * gModel ;
mat4 gTotalLuz = LightSpaceMatrix * gModel;
vec3 corAmbiente,corDifusa,corEspecular;


out vec3 outNormal;
out vec3 Color;
out vec3 vertPos;
out vec4 FragPosLightSpace;
out vec2 TexCoords;
flat out vec3 corFlat;



vec3 CalcularGouraud()
{  
    vec3 N = normalize(outNormal);
    vec3 L = normalize(vec3(gPosLuz) - vertPos);

    // Lambert's cosine law
    float lambertian = max(dot(N, L), 0.0);
    float specular = 0.0;
    vec3 specularColor = gCorLuz;
    vec3 diffuseColor = Color;
    vec3 ambientColor = Color;
    if(lambertian > 0.0) 
    {
        vec3 vertPos2 = vec3(gWVP * vec4(vertPos,  1.0));
        vec3 R = reflect(-L, N);      // Reflected light vector
        vec3 V = normalize(-vertPos2); // Vector to viewer
        // Compute the specular term
        float specAngle = max(dot(R, V), 0.0);
        specular = pow(specAngle, gMaterial.shininess);
    }
    vec3 ia = gMaterial.ka * ambientColor;
    vec3 id = gMaterial.kd * lambertian * diffuseColor;
    vec3 is = gMaterial.ks * specular * specularColor;
  
    return  ia + id + is;
}

void main()
{    
    if (modoShadowMap!=0)
    {
        //gl_Position = gTotalLuz * vec4(Position, 1.0);  
          gl_Position = LightSpaceMatrix * gModel * vec4(Position, 1.0);
    }
    else
    {
 //       FragPosLightSpace = LightSpaceMatrix * gl_Position;
        vec4 vertPos4 = gModel * vec4(Position, 1.0);
        vertPos = vec3(vertPos4) / vertPos4.w;
        gl_Position = gWVP * vertPos4; 
        FragPosLightSpace = LightSpaceMatrix * vec4(vertPos, 1.0);
        outNormal = mat3(transpose(inverse(mat3(gModel)))) * Normal;
        outNormal = normalize(outNormal);
  //      FragPosLightSpace = gTotalLuz * gl_Position;
  //      normalCorrigida = vec3(transpose(inverse(gTotal)) * vec4(Normal, 0.0)); 
    //    normalCorrigida = mat3(inverse(gTotal)) * Normal;  
     

        if (modoIluminacao==3 )
            Color = inColor;
            corFlat = Color;
            
        if (modoIluminacao==2 || modoIluminacao==1)
        {
            Color=CalcularGouraud();
            corFlat = Color;      
        }
    }
}
