
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>


//GLfloat ctrlpoints[4][4][3] = {
//    {{ -1.5, -1.5, 4.0}, { -0.5, -1.5, 2.0},
//        {0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}},
//    {{ -1.5, -0.5, 1.0}, { -0.5, -0.5, 3.0},
//        {0.5, -0.5, 0.0}, {1.5, -0.5, -1.0}},
//    {{ -1.5, 0.5, 4.0}, { -0.5, 0.5, 0.0},
//        {0.5, 0.5, 3.0}, {1.5, 0.5, 4.0}},
//    {{ -1.5, 1.5, -2.0}, { -0.5, 1.5, -2.0},
//        {0.5, 1.5, 0.0}, {1.5, 1.5, -1.0}}
//};


GLfloat patch1[4][4][3] = 
{
{	{0.0f, 0.0f, 0.0f},
    {1.4f, 0.0f, 2.4f},
    {1.4f, -0.784f, 2.4f},
    {0.78f, -1.4f, 2.4f} },

{    {0.0f, -1.4f, 2.4f},
    {1.3375f, 0.0f, 2.53125f},
    {1.3375f, -0.749f, 2.53125f},
    {0.749f, -1.3375f, 2.53125f}},

 {{0.0f, -1.3375f, 2.53125f},
    {1.4375f, 0.0f, 2.53125f},
    {1.4375f, -0.805f, 2.53125f},
    {0.805f, -1.4375f, 2.53125f}},

    {{0.0f, -1.4375f, 2.53125f},
    {1.5f, 0.0f, 2.4f},
    {1.5f, -0.84f, 2.4f},
    {0.84f, -1.5f, 2.4f}}
};

GLfloat patch2[4][4][3] =

{
    { {0.0f, -1.5f, 2.4f},
        { -0.784f, -1.4f, 2.4f },
        { -1.4f, -0.784f, 2.4f },
        { -1.4f, 0.0f, 2.4f } },

    { {-0.749f, -1.3375f, 2.53125f},
      {-1.3375f, -0.749f, 2.53125f},
      {-1.3375f, 0.0f, 2.53125f},
      {-0.805f, -1.4375f, 2.53125f} },

    { {-1.4375f, -0.805f, 2.53125f},
      {-1.4375f, 0.0f, 2.53125f},
      {-0.84f, -1.5f, 2.4f},
      {-1.5f, -0.84f, 2.4f} },

    { {-1.5f, 0.0f, 2.4f},
     {-1.4f, 0.784f, 2.4f},
     {-0.784f, 1.4f, 2.4f},
     {0.0f, 1.4f, 2.4f} }
};

void initlights(void)
{
    GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat position[] = { 0.0, 0.0, 2.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(85.0, 1.0, 1.0, 1.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
    glFlush();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
        0, 1, 12, 4, &patch1[0][0][0]);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
        0, 1, 12, 4, &patch2[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glEnable(GL_AUTO_NORMAL);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    initlights();       /* for lighted version only */
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-4.0, 4.0, -4.0 * (GLfloat)h / (GLfloat)w,
            4.0 * (GLfloat)h / (GLfloat)w, -4.0, 4.0);
    else
        glOrtho(-4.0 * (GLfloat)w / (GLfloat)h,
            4.0 * (GLfloat)w / (GLfloat)h, -4.0, 4.0, -4.0, 4.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}
 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}