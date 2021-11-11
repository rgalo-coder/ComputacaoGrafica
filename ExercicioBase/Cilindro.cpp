

#include <stdio.h>
#include <string.h>


#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogldev_math_3d.h"
#include "Cilindro.h"


Cilindro::Cilindro(int _numtriangulos, Vertex base, float raio, float altura, float corR, float corG, float corB)
{

    n = _numtriangulos;

    Vertices[0] = base; //centro da base
    Vertices[0].color = Vector3f(corR, corG, corB);
    Vertices[n + 1] = Vertex(base.pos.x, base.pos.y, base.pos.z + altura); //centro do topo
    Vertices[n + 1].color = Vector3f(corR, corG, corB);

    Indices[0] = 0;

    ind = 0;

    for (int i = 0; i < n; i++)
    {
        angulo = i * 360.0f / n;
        x = base.pos.x + raio * cosf(ToRadian(angulo));
        y = base.pos.y + raio * sinf(ToRadian(angulo));
        z = base.pos.z;

        //triangulos da base
        Vertices[i + 1] = Vertex(x, y, z);
        Vertices[i + 1].color = Vector3f(corR, corG, corB);

        //triangulos do topo
        Vertices[i + n + 2] = Vertex(x, y, z + altura);
        Vertices[i + n + 2].color = Vector3f(corR, corG, corB);

    }

    for (int i = 0; i < n - 1; i++)
    {
        //triangulos da base
        Indices[ind] = 0;
        Indices[ind + 1] = i + 2;
        Indices[ind + 2] = i + 1;

        //triangulos do topo
        Indices[ind + 3] = 1 + n;
        Indices[ind + 4] = i + 2 + n;
        Indices[ind + 5] = i + 3 + n;

        //triangulos laterais
        Indices[ind + 6] = i + 1;
        Indices[ind + 7] = i + 2;
        Indices[ind + 8] = i + n + 2;

        Indices[ind + 9] = i + 2;
        Indices[ind + 11] = i + n + 2;
        Indices[ind + 10] = i + n + 3;
        ind = ind + 12;

        if (i == n - 2)
        {
            //ultimos triangulos que conectam com o primeiro
            Indices[ind] = 0;
            Indices[ind + 1] = 1;
            Indices[ind + 2] = i + 2;

            Indices[ind + 3] = n + 1;
            Indices[ind + 5] = n + 2;
            Indices[ind + 4] = n + i + 3;

            Indices[ind + 7] = 1;
            Indices[ind + 6] = i + 2;
            Indices[ind + 8] = i + n + 3;

            Indices[ind + 9] = 1;
            Indices[ind + 11] = i + n + 3;
            Indices[ind + 10] = n + 2;

            ind = ind + 12;
            break;
        }
    }

}


unsigned int Cilindro::NumeroVertices()
{
    //return n * (3 + 3 + 3 + 3);
    return 2 * n + 2;
}

unsigned int Cilindro::NumeroIndices()
{
    return ind;
}
