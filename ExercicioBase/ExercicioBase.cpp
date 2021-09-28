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
GLuint VAO;

ExercicioBase* exercicioBase;

int TipoProjecao;


WorldTrans CubeWorldTransform,TransBule, TransIcosaedro, TransMesa;

Camera GameCamera;
bool mousebotaoesquerdo = false;


float FOV = 45.0f;
float zNear = 1.0f;
float zFar = 10.0f;
PersProjInfo PersProjInfo = { FOV, WINDOW_WIDTH, WINDOW_HEIGHT, zNear, zFar };
OrthoProjInfo OrthoProjInfo = { 2.0f, -2.0f , -2.0f, +2.0f, zNear, zFar };

unsigned int numTotalIndices, numIndicesMesa, numIndicesIcosaedro, numIndicesBule = 0;

void ExercicioBase::RenderSceneCB()
{
    //Ting: limpar o buffer de profundidade 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

#ifdef _WIN64
  //  float YRotationAngle = 0.1f;
#else
    float YRotationAngle = 1.0f;
#endif
    auto test = this;

    CubeWorldTransform.SetPosition(0.0f, 0.0f, 2.0f);
   
  //  CubeWorldTransform.Rotate(0.0f, YRotationAngle, 0.0f);
    Matrix4f World = CubeWorldTransform.GetMatrix();

    Matrix4f View = GameCamera.GetMatrix();

    Matrix4f Projection;
    if (TipoProjecao == PERSPECTIVA)
        Projection.InitPersProjTransform(PersProjInfo);
    if (TipoProjecao == PARALELA)
        Projection.InitOrthoProjTransform(OrthoProjInfo);

  
    Matrix4f WVP = Projection * View * World;



    //desenhar mesa
    DesenharMesa(WVP);

    //desenhar bule
    TransBule.SetScale(0.1f);
    DesenharBule(WVP, TransBule.GetMatrix());

   //desenhar icosaedro
    TransIcosaedro.SetScale(0.1f);
    TransIcosaedro.SetPosition(0.4f, 0.5f, 0.1f);
    DesenharIcosaedro(WVP, TransIcosaedro.GetMatrix());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glutPostRedisplay();

    glutSwapBuffers();
}
 
void ExercicioBase::DesenharMesa(Matrix4f WVP) {
    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, &WVP.m[0][0]);

    //desenhar mesa
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[0]);

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

    // color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glDrawElements(GL_TRIANGLES, numIndicesMesa, GL_UNSIGNED_INT, 0);
}
 
void ExercicioBase::DesenharBule(Matrix4f WVP, Matrix4f transformacao)
{

    WVP = WVP * transformacao;

    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, &WVP.m[0][0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[1]);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

    // color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glDrawElements(GL_TRIANGLES, numIndicesBule, GL_UNSIGNED_INT, 0);
}

void ExercicioBase::DesenharIcosaedro(Matrix4f WVP, Matrix4f transformacao)
{
    WVP = WVP * transformacao;

    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, &WVP.m[0][0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[2]);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

    // color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glDrawElements(GL_TRIANGLES, numIndicesIcosaedro, GL_UNSIGNED_INT, 0);
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
    if (gWVPLocation == -1) {
        printf("Error getting uniform location of 'gWVP'\n");
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
  //  glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
 //   glCullFace(GL_BA vCK);
    glCullFace(GL_FRONT_AND_BACK);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);

    TipoProjecao = PERSPECTIVA;
    // apenas wireframe
   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(3, VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    Mesa* mesa = new Mesa(&VBO[0], &IBO[0]);
    numIndicesMesa = mesa->RetornarNumIndices();

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    BuleUtah* bule = new BuleUtah(&VBO[1], &IBO[1]);
    numIndicesBule = bule->RetornarNumIndices();

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    Icosaedro* icosaedro = new Icosaedro(&VBO[2], &IBO[2], 3);
    numIndicesIcosaedro = icosaedro->RetornarNumIndices();
  
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
