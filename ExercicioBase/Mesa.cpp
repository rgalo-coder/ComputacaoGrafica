
#include <stdio.h>
#include <string.h>

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogldev_math_3d.h"
#include "Mesa.h"
#include "Cilindro.h"





Mesa::Mesa(GLuint* VBO, GLuint* IBO)
{

    Vertex base1, base2, base3, base4, base5;

    base1 = Vertex(0.4, 0.4, -0.6);
    base2 = Vertex(-0.4, 0.4, -0.6);
    base3 = Vertex(-0.4, -0.4, -0.6);
    base4 = Vertex(0.4, -0.4, -0.6);
    base5 = Vertex(0, 0, -0.1);

    Cilindro perna1(4, base1, 0.05, 0.5, 0.25f, 0.20f, 0.0);
    Cilindro perna2(4, base2, 0.05, 0.5, 0.25f, 0.20f, 0.0);
    Cilindro perna3(4, base3, 0.05, 0.5, 0.25f, 0.20f, 0.0);
    Cilindro perna4(4, base4, 0.05, 0.5, 0.25f, 0.20f, 0.0);
    Cilindro mesa(40, base5, 0.8, 0.1, 0.30f, 0.20f, 0.0);

    Totalvertices = perna1.NumeroVertices() + perna2.NumeroVertices() + perna3.NumeroVertices() + perna4.NumeroVertices() + mesa.NumeroVertices();
    TotalIndices = perna1.NumeroIndices() + perna2.NumeroIndices() + perna3.NumeroIndices() + perna4.NumeroIndices() + mesa.NumeroIndices();


    Vertex TodosVertices[12000];
    unsigned int TodosIndices[12000]{};


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

    CalcularNormalVertices(TodosVertices, Totalvertices, TodosIndices, TotalIndices);

    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, Totalvertices * sizeof(Vertex), TodosVertices, GL_DYNAMIC_DRAW);

    glGenBuffers(1, IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, TotalIndices * sizeof(unsigned int), TodosIndices, GL_DYNAMIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, Totalvertices * sizeof(Vertex), TodosVertices);
    glutPostRedisplay();
}

unsigned int Mesa::RetornarNumIndices() 
{
    return TotalIndices;
}
