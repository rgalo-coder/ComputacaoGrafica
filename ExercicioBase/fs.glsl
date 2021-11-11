#version 330


struct Material
{
    float ka,kd,ks,shininess;
};

uniform vec3 gCorLuz;
uniform vec3 gPosLuz;
uniform mat4 gWVP;
uniform mat4 gModel;
uniform int modoIluminacao;
uniform Material gMaterial;
uniform int modoShadowMap;   
uniform sampler2D depthMap;

in vec3 Color;
in vec3 vertPos;
in vec3 outNormal;
flat in vec3 corFlat;
in vec4 FragPosLightSpace;
in vec2 TexCoords;

mat4 gTotal = gWVP * gModel ;
vec3 normalCorrigida;
vec3 corAmbiente,corDifusa,corEspecular;



float CalcShadowFactor(vec4 LightSpacePos)
{

      vec3 ProjCoords = LightSpacePos.xyz / LightSpacePos.w;

    vec2 UVCoords;
    UVCoords.x = 0.5 * ProjCoords.x + 0.5;
    UVCoords.y = 0.5 * ProjCoords.y + 0.5;
    float z = 0.5 * ProjCoords.z + 0.5;
    float Depth = texture(depthMap, UVCoords).r;
    
    if (Depth < (z - 0.001))
        return 0.2;
    else
        return 1.0;
}


vec3 CalcularPhong()
{
    vec3 N = normalize(outNormal);
    vec3 L = normalize(gPosLuz - vertPos);

    float lambertian = max(dot(N, L), 0.0);
    float specular = 0.0;
    vec3 specularColor = gCorLuz;
    vec3 diffuseColor = Color;
    vec3 ambientColor = Color;
    if(lambertian > 0.0) 
    {
        vec3 vertPos2 = vec3(gWVP * vec4(vertPos, 1.0));
        vec3 R = reflect(-L, N);      
        vec3 V = normalize(-vertPos2); 
        float specAngle = max(dot(R, V), 0.0);
        specular = pow(specAngle, gMaterial.shininess);
    }
    vec3 ia = gMaterial.ka * ambientColor;
    vec3 id = gMaterial.kd * lambertian * diffuseColor;
    vec3 is = gMaterial.ks * specular * specularColor;
          
    float shadow = CalcShadowFactor(FragPosLightSpace);     
    
    return  ia + shadow * (id+is);
}
  

void main()
{   
    if (modoShadowMap==1)
    {

    }
    if (modoShadowMap==2)
    {         
            vec2 fragcoord = gl_FragCoord.xy / vec2(1024.0,1024.0);            
            float Depth = texture(depthMap, fragcoord.xy).r;  
            Depth = 1.0 - (1.0 - Depth) * 2;
            gl_FragColor = vec4(vec3(Depth), 1.0);        
    }
    else
    {
        if (modoIluminacao==3)
            gl_FragColor = vec4(CalcularPhong(), 1.0) ;
        if (modoIluminacao==2 )
            gl_FragColor = vec4(Color, 1.0) ;
        if (modoIluminacao==1)
            gl_FragColor = vec4(corFlat, 1.0) ;    
    }
}

