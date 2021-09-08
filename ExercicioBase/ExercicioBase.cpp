/*! \Codigo base para preparar sistema OpenGL e carregar modelos
 
 *
 * 
 */

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

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

GLuint VBO;
GLuint IBO;
GLuint gWVPLocation;

WorldTrans CubeWorldTransform;
Camera GameCamera;

float FOV = 45.0f;
float zNear = 1.0f;
float zFar = 10.0f;
PersProjInfo PersProjInfo = { FOV, WINDOW_WIDTH, WINDOW_HEIGHT, zNear, zFar };

unsigned int numTotalIndices, numIndicesMesa, numIndicesIcosaedro, numIndicesBule = 0;

static void RenderSceneCB()
{
    //Ting: limpar o buffer de profundidade 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );



#ifdef _WIN64
    float YRotationAngle = 0.1f;
#else
    float YRotationAngle = 1.0f;
#endif

    CubeWorldTransform.SetPosition(0.0f, 0.0f, 2.0f);

    CubeWorldTransform.Rotate(0.0f, YRotationAngle, 0.0f);
    Matrix4f World = CubeWorldTransform.GetMatrix();

    Matrix4f View = GameCamera.GetMatrix();

    Matrix4f Projection;
    Projection.InitPersProjTransform(PersProjInfo);

    Matrix4f WVP = Projection * View * World;

    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, &WVP.m[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

    // color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glDrawElements(GL_TRIANGLES, numTotalIndices, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glutPostRedisplay();

    glutSwapBuffers();
}


static void KeyboardCB(unsigned char key, int mouse_x, int mouse_y)
{
    GameCamera.OnKeyboard(key);
}


static void SpecialKeyboardCB(int key, int mouse_x, int mouse_y)
{
    GameCamera.OnKeyboard(key);
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

int main(int argc, char** argv)
{
#ifdef _WIN64
    srand(GetCurrentProcessId());
#else
    srandom(getpid());
#endif

    glutInit(&argc, argv);

    //Ting: para algumas placas onboard eh necessario configurar profile.
    glutInitContextVersion(4, 5);// Major version and minor version
    glutInitContextProfile(GLUT_CORE_PROFILE);

    //Ting: habilitar o buffer de profundidade

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    int x = 200;
    int y = 100;
    glutInitWindowPosition(x, y);
    int win = glutCreateWindow("Exercicio IA725");
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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);

    // apenas wireframe
   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  //Ting: Pela especificacao, deve-se criar um array object (VAO) que contem o estado dos vertices
  //Create an object that stores all of the state needed to suppl vertex data
    GLuint VAO_mesa;
    glGenVertexArrays(1, &VAO_mesa);
    glBindVertexArray(VAO_mesa);
    Mesa* mesa = new Mesa(&VBO, &IBO);
    numIndicesMesa = mesa->RetornarNumIndices();



    //selecionar qual exercicio mostrar e comentar os outros

    //BuleUtah* bule = new BuleUtah(&VBO, &IBO);
    //Icosaedro* icosaedro = new Icosaedro(&VBO, &IBO,3);
    //numTotalIndices = icosaedro->RetornarNumIndices();

    CompileShaders();

    glutDisplayFunc(RenderSceneCB);
    glutKeyboardFunc(KeyboardCB);
    glutSpecialFunc(SpecialKeyboardCB);

    CubeWorldTransform.Rotate(-90.0f, 0.0f, 0.0f);

    glutMainLoop();

    return 0;
}
