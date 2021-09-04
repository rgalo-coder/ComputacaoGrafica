
#include <stdio.h>
#include <string.h>

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogldev_math_3d.h"
#include "BuleUtah.h"


#include <vector>

#include "DadosBule.cpp"
//
//struct Vertex {
//	Vector3f pos;
//	Vector3f color;
//
//	Vertex() {}
//
//	Vertex(float x, float y, float z)
//	{
//		pos = Vector3f(x, y, z);
//		float red = (float)rand() / (float)RAND_MAX;
//		float green = (float)rand() / (float)RAND_MAX;
//		float blue = (float)rand() / (float)RAND_MAX;
//		color = Vector3f(red, green, 0.0f);
//	}
//
//	//Normalizar vetor
//	Vertex& Normalizar()
//	{
//		float x = this->pos.x;
//		float y = this->pos.y;
//		float z = this->pos.z;
//		const float Length = sqrtf(x * x + y * y + z * z);
//
//		assert(Length != 0);
//
//		this->pos.x /= Length;
//		this->pos.y /= Length;
//		this->pos.z /= Length;
//
//		return *this;
//	}
//
//};

unsigned int IndicesBule[60000] = {};
Vertex P[20000];


void CriarBuleUtah(GLuint* VBO, GLuint* IBO)
{
    RenderizarPatches();

    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(P), P, GL_STATIC_DRAW);

    glGenBuffers(1, IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndicesBule), IndicesBule, GL_STATIC_DRAW);
		
    
}


Vertex calcularCurvaBezier(Vertex* P, const float& t)
{
    float b0 = (1 - t) * (1 - t) * (1 - t);
    float b1 = 3 * t * (1 - t) * (1 - t);
    float b2 = 3 * t * t * (1 - t);
    float b3 = t * t * t;

    Vertex r1;
            
    r1.pos.x = P[0].pos.x * b0 + P[1].pos.x * b1 + P[2].pos.x * b2 + P[3].pos.x * b3;
    r1.pos.y = P[0].pos.y * b0 + P[1].pos.y * b1 + P[2].pos.y * b2 + P[3].pos.y * b3;
    r1.pos.z = P[0].pos.z * b0 + P[1].pos.z * b1 + P[2].pos.z * b2 + P[3].pos.z * b3;
	r1.color = Vector3f(1, 0.4, .5);
    return r1;
}

Vertex calcularPatchBezier(Vertex* controlPoints, const float& u, const float& v)
{
    Vertex uCurve[4];
    for (int i = 0; i < 4; ++i) uCurve[i] = calcularCurvaBezier(controlPoints + 4 * i, u);
    return calcularCurvaBezier(uCurve, v);
}

void RenderizarPatches()
{
    //numero de subdivioes de cada linha do patch
    int divs = 16; 
 //   int* nvertices = new int[divs * divs];
//    int* vertices = new int[divs * divs * 4];
    Vertex controlPoints[16];
	int nVertices = 0;
	int nIndices = 0;
	int indicepatch;

    for (int np = 0; np < 32; ++np) 
	{
        // set the control points for the current patch                                                                                                                                                    
        for (int i = 0; i < 16; ++i)
        {
			indicepatch = IndicesPatche[np][i];      
			controlPoints[i] = VerticesPatches[indicepatch];
        }

        // generate grid                                                                                                                                                                                   
        for (int j = 0, k = 0; j <= divs; ++j) 
		{
            for (int i = 0; i <= divs; ++i, ++k) 
			{
                P[nVertices] = calcularPatchBezier(controlPoints, i / (float)divs, j / (float)divs);

                //azul aleatorio
                float azulaleatorio = ((float)rand() / (float)RAND_MAX / 2) + 0.5f;
                P[nVertices].color = Vector3f(0.0f, 0.0f, azulaleatorio);
				nVertices++;
            }
        }

        // face connectivity
        for (int j = 0, k = 0; j < divs; ++j) 
		{
            for (int i = 0; i < divs; ++i, ++k) 
			{
				int offset = (divs + 1) * (divs + 1) * np ;

				IndicesBule[nIndices ] =	(divs + 1) * j + i + offset;
				IndicesBule[nIndices + 2] =	(divs + 1) * j + i + 1 + offset;
				IndicesBule[nIndices + 1] =	(divs + 1) * (j + 1 ) + i + offset;
				
				IndicesBule[nIndices + 3] =	(divs + 1) * (j + 1) + i + offset;
				IndicesBule[nIndices + 4] =	(divs + 1) * (j + 1) + i + 1 + offset;
				IndicesBule[nIndices + 5] =	(divs + 1) * j + i + 1 + offset;
				
				nIndices = nIndices + 6;
		
            }
        }		      
    }
}

