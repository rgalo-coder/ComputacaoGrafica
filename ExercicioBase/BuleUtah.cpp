
#include <stdio.h>
#include <string.h>

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogldev_math_3d.h"
#include "DadosBule.h"
#include "BuleUtah.h"


#include <vector>


Vertex P[20000];



unsigned int IndicesBule[60000] = {};

BuleUtah::BuleUtah(GLuint* VBO, GLuint* IBO)
{
    
    RenderizarPatches();

    CalcularNormalVertices(P, nVertices, IndicesBule, nIndices);

    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(Vertex), P, GL_STATIC_DRAW);

    glGenBuffers(1, IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndices * sizeof(unsigned int), IndicesBule, GL_STATIC_DRAW);
		
    
}


Vertex BuleUtah::calcularCurvaBezier(Vertex* P, const float& t)
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

Vertex BuleUtah::calcularPatchBezier(Vertex* controlPoints, const float& u, const float& v)
{
    Vertex uCurve[4];
    for (int i = 0; i < 4; ++i) uCurve[i] = calcularCurvaBezier(controlPoints + 4 * i, u);
    return calcularCurvaBezier(uCurve, v);
}

void BuleUtah::RenderizarPatches()
{
    //numero de subdivioes de cada linha do patch
    int divs = 16; 
    Vertex controlPoints[16];
	
	int indicepatch;
    float azulaleatorio;

    for (int np = 0; np < 32; ++np) 
	{
        // set the control points for the current patch                                                                                                                                                    
        //azulaleatorio = RandomFloat()/0.6f  + 0.2f;
        azulaleatorio = 0.9f;
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
                P[nVertices].normal = Vector3f(0.0f, 0.0f, 0.0f);

                //azul aleatorio
                
                
                P[nVertices].color = Vector3f(0.0f, 0.0f, azulaleatorio);
				nVertices++;
            }
        }

        // ligando os pontos do patch com triangulos
        for (int j = 0, k = 0; j < divs; ++j) 
		{
            for (int i = 0; i < divs; ++i, ++k) 
			{
				int offset = (divs + 1) * (divs + 1) * np ;

				IndicesBule[nIndices ] =	(divs + 1) * j + i + offset;
				IndicesBule[nIndices + 1] =	(divs + 1) * j + i + 1 + offset;
				IndicesBule[nIndices + 2] =	(divs + 1) * (j + 1 ) + i + offset;
				
				IndicesBule[nIndices + 3] =	(divs + 1) * (j + 1) + i + offset;
				IndicesBule[nIndices + 5] =	(divs + 1) * (j + 1) + i + 1 + offset;
				IndicesBule[nIndices + 4] =	(divs + 1) * j + i + 1 + offset;
				
				nIndices = nIndices + 6;
                
            }
        }		      
    }
}

unsigned int BuleUtah::RetornarNumIndices() 
{
    return nIndices;
}

