
#include <stdio.h>
#include <string.h>

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogldev_math_3d.h"


#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 600

GLuint VBO;
GLuint IBO;
GLuint gWorldLocation;

float ContadorCor = 0.3f;



static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    static float ScaleX = 0.0f;
    static float ScaleY = 0.0f;
    static float ScaleZ = 0.0f;

    static float Scale = 0.3f;

    static float movimento = 0.0f;

    static float TransX = 0.0f;
    static float TransY = 0.0f;
    static float TransZ = 2.0f;

#ifdef _WIN64
    movimento += 0.00f ;
 //   ScaleZ += 0.02f;
 //   ScaleX += 0.02f;

#else
#endif
    Matrix4f Scaling(Scale, 0.0f, 0.0f, 0.0f,
                    0.0f, Scale, 0.0f, 0.0f,
                    0.0f, 0.0f, Scale, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);

    Matrix4f RotationX(1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, cosf(ScaleX), -sinf(ScaleX), 0.0f,
                        0.0f, sinf(ScaleX), cosf(ScaleX), 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f);

    Matrix4f RotationY(cosf(ScaleY), 0.0f, sinf(ScaleY), 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    -sinf(ScaleY), 0.0f, cosf(ScaleY), 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);

    Matrix4f RotationZ(cosf(ScaleZ), -sinf(ScaleZ), 0.0f,  0.0f,
                        sinf(ScaleZ), cosf(ScaleZ), 0.0f,  0.0f,
                         0.0f, 0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f);

    Matrix4f Translation(1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 2.0f,
        0.0f, 0.0f, 0.0f, 1.0f);

    Matrix4f World = Translation * RotationX * RotationY * RotationZ;

    Vector3f CameraPos(5.0f, 3.0f, -5.0f);
    Vector3f U(1.0f, 0.0f, 0.0f);
    Vector3f V(0.0f, 1.0f, 0.0f);
    Vector3f N(0.0f, 0.0f, 1.0f);

    Matrix4f Camera(U.x, U.y, U.z, -CameraPos.x,
        V.x, V.y, V.z, -CameraPos.y,
        N.x, N.y, N.z, -CameraPos.z,
        0.0f, 0.0f, 0.0f, 1.0f);

    float VFOV = 45.0f;
    float tanHalfVFOV = tanf(ToRadian(VFOV / 2.0f));
    float d = 1 / tanHalfVFOV;
    float ar = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;

    float NearZ = 1.0f;
    float FarZ = 10.0f;

    float zRange = NearZ - FarZ;

    float A = (-FarZ - NearZ) / zRange;
    float B = 2.0f * FarZ * NearZ / zRange;

    Matrix4f Projection(d / ar, 0.0f, 0.0f, 0.0f,
                        0.0f, d, 0.0f, 0.0f,
                        0.0f, 0.0f, A, B,
                        0.0f, 0.0f, 1.0f, 0.0f);

    Matrix4f WVP = Projection * Camera * World;

   //Matrix4f FinalMatrix = Translation * Rotation;

 //   Matrix4f FinalMatrix = Projection * Translation ;

    glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &WVP.m[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

    // color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
   //glDrawElements(GL_TRIANGLES, 96, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, 96*10, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    

    glutPostRedisplay();

    glutSwapBuffers();
}


struct Vertex {
    Vector3f pos;
    Vector3f color;

    Vertex() 
    {
       
    }

    Vertex(float x, float y, float z)
    {
        pos = Vector3f(x, y, z);

        //float red = (float)rand() / (float)RAND_MAX;
        //float green = (float)rand() / (float)RAND_MAX;
        //float blue = (float)rand() / (float)RAND_MAX;
        //color = Vector3f(red, green, blue);

        
        color = Vector3f(ContadorCor, ContadorCor, 0.0f);
   

    }
};

//
//static void CreateVertexBuffer()
//{
//    Vertex Vertices[8];
//
//    Vertices[0] = Vertex(0.5f, 0.5f, 0.5f);
//    Vertices[1] = Vertex(-0.5f, 0.5f, -0.5f);
//    Vertices[2] = Vertex(-0.5f, 0.5f, 0.5f);
//    Vertices[3] = Vertex(0.5f, -0.5f, -0.5f);
//    Vertices[4] = Vertex(-0.5f, -0.5f, -0.5f);
//    Vertices[5] = Vertex(0.5f, 0.5f, -0.5f);
//    Vertices[6] = Vertex(0.5f, -0.5f, 0.5f);
//    Vertices[7] = Vertex(-0.5f, -0.5f, 0.5f);
//
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
//}
//
//struct Objeto3d 
//{
//    Vertex Vertices;
//    unsigned int Indices;
//    
//    Objeto3d(int vernum, int indnum)
//    {
//        Vertices = Vertices[vernum];
//        Indices = Indices[indnum];
//    }
//};

class Cilindro
{

private:
    float x, y, z, angle;
    int ind;

public:
    Vertex Vertices[1000];
    unsigned int Indices[1000] = {};
    int n;


    Cilindro(int _numtriangulos, Vertex base, float radius, float height, float colorR, float colorG, float colorB)
    {
        /*      Vertices = new Vertex[_numtriangulos + 11];
        Indices = new unsigned int[_numtriangulos * 12];*/
        n = _numtriangulos;

        Vertices[0] = base; //centro da base
        Vertices[n + 1] = Vertex(base.pos.x, base.pos.y, base.pos.z + height); //centro do topo
        
        Indices[0] = 0;
        
        ind = 0;

        for (int i = 0; i < n; i++)
        {
            angle = i * 360.0f / n;
            x = base.pos.x + radius * cosf(ToRadian(angle));
            y = base.pos.y + radius * sinf(ToRadian(angle));
            z = base.pos.z;

            Vertices[i + 1] = Vertex(x, y, z);
            Vertices[i + 1].color = Vector3f(colorR, colorG, colorB);
            Vertices[i + n + 2] = Vertex(x, y, z + height);
            Vertices[i + n + 2].color = Vector3f(1, 1, 1);

        }

        for (int i = 0; i < n - 1; i++)
        {
            Indices[ind] = 0;
            Indices[ind + 1] = i + 2;
            Indices[ind + 2] = i + 1;

            Indices[ind + 3] = 1 + n;
            Indices[ind + 4] = i + 2 + n;
            Indices[ind + 5] = i + 3 + n;

            Indices[ind + 6] = i + 1;
            Indices[ind + 7] = i + 2;
            Indices[ind + 8] = i + n + 2;

            Indices[ind + 9] = i + 2;
            Indices[ind + 11] = i + n + 2;
            Indices[ind + 10] = i + n + 3;
            ind = ind + 12;

            if (i == n - 2)
            {
                Indices[ind] = 0;
                Indices[ind + 1] = 1;
                Indices[ind + 2] = i + 2;

                Indices[ind + 3] = n + 1;
                Indices[ind + 5] = n + 2;
                Indices[ind + 4] = n + i + 3;

                Indices[ind + 6] = 1;
                Indices[ind + 8] = i + 2;
                Indices[ind + 7] = i + n + 3;

                Indices[ind + 9] = 1;
                Indices[ind + 11] = i + n + 3;
                Indices[ind + 10] = n + 2;

                ind = ind + 12;
            }
        }
    }


    unsigned int NumeroVertices()
    {
        return n * (3 + 3 + 3 + 3) ;
    }

    unsigned int NumeroIndices()
    {
        return ind;
    }

};

static void EnviarBuffer(Vertex *Vertices, int tamanhoVertices, unsigned int *Indices, int tamanhoIndices)
{
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, tamanhoVertices, Vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, tamanhoIndices, Indices, GL_STATIC_DRAW);

}


static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(1);
    }

    const GLchar* p[1];
    p[0] = pShaderText;

    GLint Lengths[1];
    Lengths[0] = (GLint)strlen(pShaderText);

    glShaderSource(ShaderObj, 1, p, Lengths);

    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";

static void CompileShaders()
{
    GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    std::string vs, fs;

    if (!ReadFile(pVSFileName, vs)) {
        exit(1);
    };

    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

    if (!ReadFile(pFSFileName, fs)) {
        exit(1);
    };

    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);

    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
    if (Success == 0) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld");
    if (gWorldLocation == -1) {
        printf("Error getting uniform location of 'gWorld'\n");
        exit(1);
    }

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(ShaderProgram);
}





int ExercicioMesa(int argc, char** argv)
{
#ifdef _WIN64
    srand(GetCurrentProcessId());
#else
    srandom(getpid());
#endif

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    int x = 200;
    int y = 100;
    glutInitWindowPosition(x, y);
    int win = glutCreateWindow("Exercicio Mesa");
    printf("window id: %d\n", win);

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    Vertex base1,base2,base3,base4,base5;

    base1 = Vertex(0.4, 0.4, -0.6);
    base2 = Vertex(-0.4, 0.4, -0.6);
    base3 = Vertex(-0.4, -0.4, -0.6);
    base4 = Vertex(0.4, -0.4, -0.6);
    base5 = Vertex(0, 0, 0.4);

    Cilindro perna1(4,base1, 0.1, 1, 0.2, 0.3,0.1);
    Cilindro perna2(8,base2, 0.1, 1, 0.1, 0.4, 0.1);
    Cilindro perna3(8,base3, 0.1, 1, 0.3, 0.35, 0.1);
    Cilindro perna4(8,base4, 0.1, 1, 0.4, 0.4, 0.1);
    Cilindro mesa(0,base5, 1.0, 0.2, 0.4, 0.4, 0.1);

    int Totalvertices = perna1.NumeroVertices() + perna2.NumeroVertices() + perna3.NumeroVertices() + perna4.NumeroVertices() + mesa.NumeroVertices();
    int TotalIndices = perna1.NumeroIndices() + perna2.NumeroIndices() + perna3.NumeroIndices() + perna4.NumeroIndices() + mesa.NumeroIndices();


    Vertex TodosVertices[1000];
    unsigned int TodosIndices[1000]{};


    unsigned int j = 0;

    for (int i = 0; i < perna1.NumeroVertices(); i++)
    {
        TodosVertices[j] = perna1.Vertices[i];
        j++;
    }
    for (int i = 0; i < perna2.NumeroVertices(); i++)
    {
        TodosVertices[j] = perna2.Vertices[i];
        j++;
    }
    for (int i = 0; i < perna3.NumeroVertices(); i++)
    {
        TodosVertices[j] = perna3.Vertices[i];
        j++;
    }
    for (int i = 0; i < perna4.NumeroVertices(); i++)
    {
        TodosVertices[j] = perna4.Vertices[i];
        j++;
    }
    for (int i = 0; i < mesa.NumeroVertices(); i++)
    {
        TodosVertices[j] = mesa.Vertices[i];
        j++;
    }



    j = 0;

    for (int i = 0; i < perna1.NumeroIndices(); i++)
    {
        TodosIndices[j] = perna1.Indices[i];
        j++;
    }
    for (int i = 0; i < perna2.NumeroIndices(); i++)
    {
        TodosIndices[j] = perna2.Indices[i] + perna1.NumeroVertices();
        j++;
    }
    for (int i = 0; i < perna3.NumeroIndices(); i++)
    {
        TodosIndices[j] = perna3.Indices[i] + perna1.NumeroVertices() + perna2.NumeroVertices();
        j++;
    }
    for (int i = 0; i < perna4.NumeroIndices(); i++)
    {
        TodosIndices[j] = perna4.Indices[i] + perna1.NumeroVertices() + perna2.NumeroVertices() + perna3.NumeroVertices();
        j++;
    }
    for (int i = 0; i < mesa.NumeroIndices(); i++)
    {
        TodosIndices[j] = mesa.Indices[i] + perna1.NumeroVertices() + perna2.NumeroVertices() + perna3.NumeroVertices() + perna4.NumeroVertices();
        j++;
    }


    EnviarBuffer(TodosVertices, Totalvertices * sizeof(perna1.Vertices[0]), TodosIndices, TotalIndices * sizeof(perna1.Indices[0]));

    //CreateVertexBuffer();
    //CreateIndexBuffer();

    int textureunits = 0;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureunits);
    printf("Number of texture units %d\n", textureunits);

    CompileShaders();

    glutDisplayFunc(RenderSceneCB);

    glutMainLoop();

    return 0;
}
