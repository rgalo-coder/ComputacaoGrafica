#include <stdio.h>
#include <string.h>

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogldev_math_3d.h"
#include "camera.h"
#include "world_transform.h"

#include "Mesa.h"
#include "Icosaedro.h"
#include "BuleUtah.h"
#include "ExercicioBase.h"

#include <functional>


#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

GLuint VBO[3];
GLuint IBO[3];
GLuint gWVPLocation;
GLuint gCorHSVIcosaedro;
GLuint VAO;
GLuint gLuzLocation;
GLuint gDirecaoLuzLocation;
GLuint gWVPLuzLocation;
GLuint gTranformationLocation;
GLuint gMaterialLocation_ka, gMaterialLocation_ks, gMaterialLocation_kd, gMaterialLocation_shininess;
GLuint gmodoIluminacaoLocation;

ExercicioBase* exercicioBase;

int TipoProjecao;


WorldTrans CubeWorldTransform,TransBule, TransIcosaedro, TransMesa;

Camera GameCamera;
bool mousebotaoesquerdo = false;

Icosaedro* icosaedro;
Mesa* mesa;
BuleUtah* bule;

float FOV = 45.0f;
float zNear = 1.0f;
float zFar = 10.0f;
PersProjInfo PersProjInfo = { FOV, WINDOW_WIDTH, WINDOW_HEIGHT, zNear, zFar };
OrthoProjInfo OrthoProjInfo = { 2.0f, -2.0f , -2.0f, +2.0f, zNear, zFar };


Vector3f Luz = { 1.0f, 1.0f,1.0f };

Vector3f DirecaoLuz = Vector3f( +2.0f, +2.0f,+0.0f );
Matrix4f Identidade;



unsigned int numTotalIndices, numIndicesMesa, numIndicesIcosaedro, numIndicesBule = 0;



Matrix3f WVPinv;
bool setWVPinv = false;

void ExercicioBase::RenderSceneCB()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    CubeWorldTransform.SetPosition(0.0f, 0.0f, 2.0f);

    Matrix4f World = CubeWorldTransform.GetMatrix();

    Matrix4f View = GameCamera.GetMatrix();

    Matrix4f Projection;
    if (TipoProjecao == PERSPECTIVA)
        Projection.InitPersProjTransform(PersProjInfo);
    if (TipoProjecao == PARALELA)
        Projection.InitOrthoProjTransform(OrthoProjInfo);
      
    Matrix4f WVP = Projection * View * World;

    //desenhar mesa
    Material gMaterial = { 0.9,0.4,0.4,30 };
    DesenharObjeto(WVP, Identidade, numIndicesMesa, gMaterial, VBO[0], IBO[0]);

    //desenhar bule
    TransBule.SetScale(0.1f);
    gMaterial = { 0.9,0.9,1.0,80 };
    DesenharObjeto(WVP, TransBule.GetMatrix(), numIndicesBule, gMaterial, VBO[1], IBO[1]);

   //desenhar icosaedro
    TransIcosaedro.SetScale(0.1f);
    TransIcosaedro.SetPosition(0.4f, 0.5f, 0.1f);
    gMaterial = { 0.9,0.9,1.0,80 };
    DesenharObjeto(WVP, TransIcosaedro.GetMatrix(),numIndicesIcosaedro, gMaterial, VBO[2], IBO[2]);
    

    glUniform3fv(gLuzLocation, 1, Luz);

    glUniform3fv(gDirecaoLuzLocation, 1, DirecaoLuz);
    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, &WVP.m[0][0]);
    glUniform1i(gmodoIluminacaoLocation, 3);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glutPostRedisplay();

    glutSwapBuffers();
}
 


void ExercicioBase::DesenharObjeto(Matrix4f WVP, Matrix4f transformacao, unsigned int numIndices, Material gMaterial, GLuint &_VBO, GLuint &_IBO)
{
    
    glUniform1f(gMaterialLocation_ka, gMaterial.ka);
    glUniform1f(gMaterialLocation_kd, gMaterial.kd);
    glUniform1f(gMaterialLocation_ks, gMaterial.ks);
    glUniform1f(gMaterialLocation_shininess, gMaterial.shininess);

    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, &WVP.m[0][0]);
    glUniformMatrix4fv(gTranformationLocation, 1, GL_TRUE, &transformacao.m[0][0]);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO);

    //posicao vertice
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);

    // cor
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));

    // normal
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);

}


void ExercicioBase::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
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
     
void ExercicioBase::CompileShaders()
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

    gWVPLocation = glGetUniformLocation(ShaderProgram, "gWVP");
    gLuzLocation = glGetUniformLocation(ShaderProgram, "gLuz");
    gDirecaoLuzLocation = glGetUniformLocation(ShaderProgram, "gDirLuz");
    gTranformationLocation = glGetUniformLocation(ShaderProgram, "gTrans");
    gTranformationLocation = glGetUniformLocation(ShaderProgram, "gTrans");
 
    gMaterialLocation_ka = glGetUniformLocation(ShaderProgram, "gMaterial.ka");
    gMaterialLocation_ks = glGetUniformLocation(ShaderProgram, "gMaterial.ks");
    gMaterialLocation_kd = glGetUniformLocation(ShaderProgram, "gMaterial.kd");
    gMaterialLocation_shininess = glGetUniformLocation(ShaderProgram, "gMaterial.shininess");
   
    gmodoIluminacaoLocation = glGetUniformLocation(ShaderProgram, "modoIluminacao");

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(ShaderProgram);
}

int ExercicioBase::startup()
{
    #ifdef _WIN64
    srand(GetCurrentProcessId());
    #else
    srandom(getpid());
    #endif 
    
    glutInitContextVersion(4, 5);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    int x = 200;
    int y = 100;

    glutInitWindowPosition(x, y);
    int win = glutCreateWindow("Exercicio IA725");
    printf("window id: %d\n", win);

    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    return 0;

}

ExercicioBase::ExercicioBase(int argc, char** argv)
{
    glutInit(&argc, argv);
    startup();
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    TipoProjecao = PERSPECTIVA;

    // apenas wireframe
   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(3, VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    mesa = new Mesa(&VBO[0], &IBO[0]);
    numIndicesMesa = mesa->RetornarNumIndices();

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    bule = new BuleUtah(&VBO[1], &IBO[1]);
    numIndicesBule = bule->RetornarNumIndices();

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    icosaedro = new Icosaedro(&VBO[2], &IBO[2], 3);
    numIndicesIcosaedro = icosaedro->RetornarNumIndices();
    printf("vertices icosaedro %i", icosaedro->RetornarNumVertices());

    Identidade.InitIdentity();

    CompileShaders();

    glutDisplayFunc(callback_RenderSceneCB);
    glutKeyboardFunc(callback_KeyboardCB);
    glutSpecialFunc(callback_SpecialKeyboardCB);
    glutMouseFunc(callback_MouseCB);
    glutMotionFunc(callback_MotionCB);    

    int opcaomenu = glutCreateMenu(callback_MenuCB);
    glutAddMenuEntry("Projetiva", 0);
    glutAddMenuEntry("Ortogonal", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    CubeWorldTransform.Rotate(-90.0f, 0.0f, 0.0f);

    glutMainLoop();

}

void ExercicioBase::callback_MenuCB(int opcao)
{   
        exercicioBase->MenuCB(opcao);
}

void ExercicioBase::callback_MouseCB(int button, int state, int x, int y)
{
    exercicioBase->MouseCB(button, state, x, y);
}

void ExercicioBase::callback_MotionCB(int x, int y)
{
    exercicioBase->MotionCB(x, y);
}

void ExercicioBase::callback_RenderSceneCB()
{
    exercicioBase->RenderSceneCB();
}

void ExercicioBase::callback_KeyboardCB(unsigned char key, int mouse_x, int mouse_y)
{
    exercicioBase->KeyboardCB(key, mouse_x,mouse_y);
}

void ExercicioBase::callback_SpecialKeyboardCB(int key, int mouse_x, int mouse_y)
{
    exercicioBase->SpecialKeyboardCB(key, mouse_x, mouse_y);
}
    
void ExercicioBase::KeyboardCB(unsigned char key, int mouse_x, int mouse_y)
{
    GameCamera.OnKeyboard(key);
    zNear = GameCamera.GetzNear();
    PersProjInfo = { FOV, WINDOW_WIDTH, WINDOW_HEIGHT, zNear, zFar };
    icosaedro->OnKeyboard(key);
}
 

void ExercicioBase::MouseCB(int button, int state, int x, int y)
{

    CubeWorldTransform.OnMouse(button, state, x, y);
}

void ExercicioBase::MotionCB(int x, int y)
{

    CubeWorldTransform.OnMotion(x, y);
}

void ExercicioBase::SpecialKeyboardCB(int key, int mouse_x, int mouse_y)
{
    GameCamera.OnKeyboard(key);

}

void ExercicioBase::MenuCB(int opcao)
{
    switch (opcao)
    {
    case 0:
        TipoProjecao = PERSPECTIVA;
        break;
    case 1:
        TipoProjecao = PARALELA;
        break;
    }
}

int main(int argc, char** argv)
{
    ExercicioBase* exercicioBase = new ExercicioBase(argc, argv);
         
    return 0;
}
