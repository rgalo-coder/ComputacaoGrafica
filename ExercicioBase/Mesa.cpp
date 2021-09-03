
#include <stdio.h>
#include <string.h>

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogldev_math_3d.h"
#include "Mesa.h"


struct Vertex {
    Vector3f pos;
    Vector3f color;

    Vertex() {}

    Vertex(float x, float y, float z)
    {
        pos = Vector3f(x, y, z);
   /*  float red = (float)rand() / (float)RAND_MAX;
        float green = (float)rand() / (float)RAND_MAX;
        float blue = (float)rand() / (float)RAND_MAX;*/
        color = Vector3f(0.5, 0.5, 0.5);
    }
};

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
        return n * (3 + 3 + 3 + 3);
    }

    unsigned int NumeroIndices()
    {
        return ind;
    }

};


void CriarMesa(GLuint* VBO, GLuint* IBO)
{

    Vertex base1, base2, base3, base4, base5;

    base1 = Vertex(0.4, 0.4, -0.6);
    base2 = Vertex(-0.4, 0.4, -0.6);
    base3 = Vertex(-0.4, -0.4, -0.6);
    base4 = Vertex(0.4, -0.4, -0.6);
    base5 = Vertex(0, 0, 0.4);

    Cilindro perna1(4, base1, 0.1, 1, 0.2, 0.3, 0.1);
    Cilindro perna2(8, base2, 0.1, 1, 0.1, 0.4, 0.1);
    Cilindro perna3(8, base3, 0.1, 1, 0.3, 0.35, 0.1);
    Cilindro perna4(8, base4, 0.1, 1, 0.4, 0.4, 0.1);
    Cilindro mesa(16, base5, 1.0, 0.2, 0.4, 0.4, 0.1);

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


    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, Totalvertices * sizeof(perna1.Vertices[0]), TodosVertices, GL_STATIC_DRAW);

    glGenBuffers(1, IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, TotalIndices * sizeof(perna1.Indices[0]), TodosIndices, GL_STATIC_DRAW);

}
