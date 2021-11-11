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


float near_plane = 1.0;
float far_plane = 6.0;


float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));
}

float ShadowCalculation1(vec4 FragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = FragPosLightSpace.xyz / FragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(depthMap, projCoords.xy).z; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}  


float ShadowCalculation(vec4 FragPosLightSpace)
{
    vec3 ShadowCoord  = FragPosLightSpace.xyz / FragPosLightSpace.w;
    float closestDepth = texture(depthMap, ShadowCoord.xy).z; 
    float shadow = 1.0;
    if ( closestDepth  <=  ShadowCoord.z + 0.0001)    
       shadow = 0.5;    
    return shadow;
}

float CalcShadowFactor(vec4 LightSpacePos)
{
    vec3 ProjCoords = LightSpacePos.xyz / LightSpacePos.w;
    vec2 UVCoords;
    UVCoords.x = 0.5 * ProjCoords.x + 0.5;
    UVCoords.y = 0.5 * ProjCoords.y + 0.5;
    float z = 0.5 * ProjCoords.z + 0.5;
    float Depth = texture(depthMap, UVCoords).r;
    
    if (Depth < (z + 0.00001))
        return 0.2;
    else
        return 1.0;
}


vec3 CalcularPhong()
{
    vec3 N = normalize(outNormal);
    vec3 L = normalize(gPosLuz - vertPos);

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
          
    float shadow = CalcShadowFactor(FragPosLightSpace);     
  //  float shadow = ShadowCalculation(FragPosLightSpace);     
    
    return  ia + shadow * (id+is);
    }
  

void main()
{   
    if (modoShadowMap==1)
    {
//        
//        float depthValue = gl_FragCoord.z;
//        depthValue = 1.0 - (1.0 - depthValue) * 0.10;
//        depthValue = 1 - depthValue / 13;
//        gl_FragColor = vec4(vec3(depthValue), 1.0);
//        float depthValue = texture(depthMap, TexCoords).r;
//        float depthValue = vertPos.z;
//
//        depthValue = 1.0 - (1.0 - depthValue) * 13;      
//        gl_FragColor = vec4(vec3(depthValue), 1.0);
//        float Depth = texture(depthMap, TexCoords).x;
//        gl_FragColor = vec4(vec3(Depth), 1.0);

//            float Depth = texture(depthMap, TexCoords).r;
//  //          Depth = 1.0 - (1.0 - Depth) * 0.50;
//            gl_FragColor = vec4(vec3(Depth), 1.0);
  //          gl_FragDepth = gl_FragCoord.z;
//                gl_FragDepth = gl_FragCoord.z;
//        
    }
    if (modoShadowMap==2)
    {           
//        float depthValue = texture(depthMap, gl_FragCoord.xy).r;
//        gl_FragColor = vec4(vec3(depthValue), 1.0);
//        float Depth = texture(depthMap, TexCoords).r;

//        vec3 projCoords = FragPosLightSpace.xyz / FragPosLightSpace.w;
//        // transform to [0,1] range
//        projCoords = projCoords * 0.5 + 0.5;
        // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
//        float depthValue = texture(depthMap, gl_FragCoord.xy).r; 
//        depthValue = 1.0 - (1.0 - depthValue*0.1) * 0.5;  

       float depthValue = texture(depthMap, gl_FragCoord.xy).y;

//       depthValue = 1.0 - (1.0 - depthValue * 0.5) * 0.1;
        gl_FragColor = vec4(vec3(depthValue), 1.0);
        
//            float depthValue = texture(depthMap, TexCoords).r;
//            gl_FragColor = vec4(vec3(LinearizeDepth(depthValue) / far_plane), 1.0); // perspective
            // FragColor = vec4(vec3(depthValue), 1.0); // orthographic
         

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

