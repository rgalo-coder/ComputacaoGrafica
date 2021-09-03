
#include <stdio.h>
#include <string.h>

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogldev_math_3d.h"
#include "Icosaedro.h"

struct Vertex {
	Vector3f pos;
	Vector3f color;

	Vertex() {}

	Vertex(float x, float y, float z)
	{
		pos = Vector3f(x, y, z);
		float red = (float)rand() / (float)RAND_MAX;
		float green = (float)rand() / (float)RAND_MAX;
		float blue = (float)rand() / (float)RAND_MAX;
		color = Vector3f(red, green, 0.0f);
	}

	//Normalizar vetor
	Vertex& Normalizar()
	{
		float x = this->pos.x;
		float y = this->pos.y;
		float z = this->pos.z;
		const float Length = sqrtf(x * x + y * y + z * z);

		assert(Length != 0);

		this->pos.x /= Length;
		this->pos.y /= Length;
		this->pos.z /= Length;

		return *this;
	}

};

unsigned int Indices[20][3] = {
	  {0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
	  {8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
	  {7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
	  {6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
};

Vertex Vertices[12];

unsigned int Indices2[500];
Vertex Vertices2[500];


void CriarIcosaedro(GLuint* VBO, GLuint* IBO)
{
	

	const float X = 0.525731112119133606f;
	const float Z = 0.850650808352039932f;
	const float N = 0.0f;

	float _vertices[12][3] =
	{
	  {-X,N,Z}, {X,N,Z}, {-X,N,-Z}, {X,N,-Z},
	  {N,Z,X}, {N,Z,-X}, {N,-Z,X}, {N,-Z,-X},
	  {Z,X,N}, {-Z,X, N}, {Z,-X,N}, {-Z,-X, N}
	};

	float red = 0.3f;
	float green = 0.3f;
	
		for (int i = 0; i < 12; i++)
		{			
			Vertices[i].pos.x = _vertices[i][0];
			Vertices[i].pos.y = _vertices[i][1];
			Vertices[i].pos.z = _vertices[i][2];

			/*float red = (float)rand() / (float)RAND_MAX;
			float green = (float)rand() / (float)RAND_MAX;
			float blue = (float)rand() / (float)RAND_MAX;*/

			Vertices[i].color = { red , green, 0.0f };
			red += 0.025f;
			green += 0.025f;
		}


		SubdividirIcosaedro(2);
	

glGenBuffers(1, VBO);
glBindBuffer(GL_ARRAY_BUFFER, *VBO);

//icosaedro original
//glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

//icosardro subdividido
glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices2), Vertices2, GL_STATIC_DRAW);

glGenBuffers(1, IBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *IBO);

//icosaedro original
//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

//icosardro subdividido
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices2), Indices2, GL_STATIC_DRAW);

}

Vertex PontoMedio(Vertex ponto1, Vertex ponto2)
{
	float x_medio = (ponto1.pos.x + ponto2.pos.x) / 2;
	float y_medio = (ponto1.pos.y + ponto2.pos.y) / 2;
	float z_medio = (ponto1.pos.z + ponto2.pos.z) / 2;
	Vertex _ret = Vertex(x_medio, y_medio, z_medio);
	return _ret;
}

int Buscar(Vertex* vertices, int size, Vertex target)
{
	for (int i = 0; i <= size; ++i)
	{
		if (vertices[i].pos.x == target.pos.x)
			if (vertices[i].pos.y == target.pos.y)
				if (vertices[i].pos.z == target.pos.z)
				{
					return i;
				}
	}

	return -1;
}

int AdicionarVertice(Vertex* vertices, unsigned int* indices, int* pos, Vertex ponto)
{
	int resultado = Buscar(Vertices2, *pos, ponto);
	if (resultado == -1)
	{ 
		vertices[*pos] = ponto;
		indices[*pos] = *pos;
		*pos = *pos + 1;
		return *pos;
	}
	else
	{
		indices[*pos] = resultado;
		*pos = *pos + 1;
		return resultado;
	}
}


void SubdividirIcosaedro(int graus)
{
	for (int iteracoes = 1; iteracoes <= graus; iteracoes++)
	{
		int pos = 0;
		int indicevertice = 0;

		for (int i = 0; i < 20; i++)
		{

			int indicePontoA = Indices[i][0];
			int indicePontoB = Indices[i][1];
			int indicePontoC = Indices[i][2];

			Vertex pontoA = Vertices[indicePontoA];
			Vertex pontoB = Vertices[indicePontoB];
			Vertex pontoC = Vertices[indicePontoC];

			Vertex pontoMedioAB = PontoMedio(pontoA, pontoB);
			Vertex pontoMedioBC = PontoMedio(pontoB, pontoC);
			Vertex pontoMedioCA = PontoMedio(pontoC, pontoA);

			//normaliza os pontos medios para que tenhao raio (distancia do centro) igual aos demais
			pontoMedioAB.Normalizar();
			pontoMedioBC.Normalizar();
			pontoMedioCA.Normalizar();


			//indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoA);
			//indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoB);
			//indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoC);

			//indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoMedioAB);
			//indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoMedioBC);
			//indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoMedioCA);


			//cria 4 triangulos a partir de 1
			indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoA);
			indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoMedioCA);
			indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoMedioAB);

			indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoMedioCA);
			indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoC);
			indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoMedioBC);

			indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoMedioAB);
			indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoMedioCA);
			indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoMedioBC);

			indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoMedioAB);
			indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoMedioBC);
			indicevertice = AdicionarVertice(Vertices2, Indices2, &pos, pontoB);



			/*Vertices2[pos] = Vertices[pontoA];

			Indices2[pos] = i;


			Vertices2[pos + 1] = Vertices[pontoB];
			Vertices2[pos + 2] = Vertices[pontoC];

			Vertices2[pos + 3] = pontoMedioAB;
			Vertices2[pos + 4] = pontoMedioBC;
			Vertices2[pos + 5] = pontoMedioCA;

			Indices2[pos + 1] = i+1;
			Indices2[pos + 2] = i + 2;

			Indices2[pos + 3] = i + 3;
			Indices2[pos + 4] = i + 4;
			Indices2[pos + 5] = i + 5;   */

		}
	}

	}


