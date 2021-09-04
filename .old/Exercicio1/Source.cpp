#define M_PI       3.14159265358979323846   // pi
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ogldev_math_3d.h"


#include "ExercicioMesa.h"
//#include "BuleUtah.h"


int main(int argc, char** argv)
{

	ExercicioMesa(0,0);
	//BuleUtah(0, 0);

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

        float red = (float)rand() / (float)RAND_MAX;
        float green = (float)rand() / (float)RAND_MAX;
        float blue = (float)rand() / (float)RAND_MAX;
        color = Vector3f(red, green, blue);



    }
};

