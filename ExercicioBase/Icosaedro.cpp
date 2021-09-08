
#include <stdio.h>
#include <string.h>

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogldev_math_3d.h"
#include "Icosaedro.h"

unsigned int Indices[16000] = { 0,4,1,0,9,4,9,5,4,4,5,8,4,8,1,
	  8,10,1,8,3,10,5,3,8,5,2,3,2,7,3,
	  7,10,3,7,6,10,7,11,6,11,0,6,0,1,6,
	  6,1,10,9,0,11,9,11,2,9,2,5,7,2,11

};

unsigned int Indices2[16000];

Vertex Vertices[3000];
Vertex Vertices2[3000];


Icosaedro::Icosaedro(GLuint* VBO, GLuint* IBO, int graus)
{

	indicevertice = 60;
	const float X = 0.525731112119133606f;
	const float Z = 0.850650808352039932f;
	const float N = 0.0f;

	float _vertices[12][3] =
	{
	  {-X,N,Z}, {X,N,Z}, {-X,N,-Z}, {X,N,-Z},
	  {N,Z,X}, {N,Z,-X}, {N,-Z,X}, {N,-Z,-X},
	  {Z,X,N}, {-Z,X, N}, {Z,-X,N}, {-Z,-X, N}
	};

	
	for (int i = 0; i < 12; i++)
	{
		Vertices[i].pos.x = _vertices[i][0];
		Vertices[i].pos.y = _vertices[i][1];
		Vertices[i].pos.z = _vertices[i][2];

		float amarelo = RandomFloat() / 0.6f + 0.2f;		
		Vertices[i].color = { amarelo , amarelo, 0.0f };
		
		
	}

	//inverter rotacao dos indices originais
	for (int j = 0; j < 60; j=j+3) 
	{
		int temp = Indices[j ];
		Indices[j ] = Indices[j  +1];
		Indices[j + 1] = temp;

	}
	SubdividirIcosaedro(graus);


	glGenBuffers(1, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glGenBuffers(1, IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

}

Vertex Icosaedro::PontoMedio(Vertex ponto1, Vertex ponto2)
{
	float x_medio = (ponto1.pos.x + ponto2.pos.x) / 2;
	float y_medio = (ponto1.pos.y + ponto2.pos.y) / 2;
	float z_medio = (ponto1.pos.z + ponto2.pos.z) / 2;
	Vertex _ret = Vertex(x_medio, y_medio, z_medio);
	return _ret;
}

int Icosaedro::Buscar(Vertex* vertices, int size, Vertex target)
{
	
	float erro = 0.000001f;
	for (int i = 0; i <= size; ++i)
	{
		
		if (vertices[i].pos.x >= (target.pos.x - erro) && (vertices[i].pos.x <= (target.pos.x + erro)))
			if (vertices[i].pos.y >= (target.pos.y - erro) && (vertices[i].pos.y <= (target.pos.y + erro)))
				if (vertices[i].pos.z >= (target.pos.z - erro) && (vertices[i].pos.z <= (target.pos.z + erro)))
				{
					return i;
				}
	}

	return -1;
}

int Icosaedro::AdicionarVertice(Vertex* vertices, unsigned int* indices, int* posI, int* posV, Vertex ponto)
{
	int resultado = Buscar(Vertices2, *posV, ponto);
	if (resultado == -1)
	{
		//nao encontrou vertice entao ele é adicionado na tabela de vertices
		vertices[*posV] = ponto;
		float amarelo = RandomFloat() / 0.6f + 0.2f;
		vertices[*posV].color = { amarelo, amarelo, 0.0f };
		*posV = *posV + 1;

		//adiciona vertice ao indice
		indices[*posI] = *posV - 1;
		*posI = *posI + 1;
		return *posI;
	}
	else
	{
		//vertice ja existente
		indices[*posI] = resultado;
		*posI = *posI + 1;
		//return resultado;
		return *posI;
	}
}

void Icosaedro::SubdividirIcosaedro(int graus)
{
	
	for (int iteracoes = 1; iteracoes <= graus; iteracoes++)
	{
		int posIndices = 0;
		int posVertices = 0;		
		int indicePontoA, indicePontoB, indicePontoC;
		Vertex pontoA, pontoB, pontoC;
		Vertex pontoMedioAB, pontoMedioBC, pontoMedioCA;

		int max = pow(4, (iteracoes - 1));
		max = max * 20;
		
		for (int i = 0; i < max; i++)
		{
		
			indicePontoA = Indices[3 * i + 0];
			indicePontoB = Indices[3 * i + 1];
			indicePontoC = Indices[3 * i + 2];
		
		//detecta se a iteracao é par ou impar para inverter os triangulos
			if ((graus % 2) == 0)
			{
			pontoA = Vertices[indicePontoA];
			pontoB = Vertices[indicePontoB];
			pontoC = Vertices[indicePontoC];

			}
			else
			{
				pontoA = Vertices[indicePontoA];
				pontoB = Vertices[indicePontoC];
				pontoC = Vertices[indicePontoB];
			}

			pontoMedioAB = PontoMedio(pontoA, pontoB);
			pontoMedioBC = PontoMedio(pontoB, pontoC);
			pontoMedioCA = PontoMedio(pontoC, pontoA);

			//normaliza os pontos medios para que tenhao raio (distancia do centro) igual aos demais
			pontoMedioAB.Normalizar();
			pontoMedioBC.Normalizar();
			pontoMedioCA.Normalizar();

			//cria 4 triangulos a partir de 1
			indicevertice = AdicionarVertice(Vertices2, Indices2, &posIndices, &posVertices, pontoMedioBC);
			indicevertice = AdicionarVertice(Vertices2, Indices2, &posIndices, &posVertices, pontoB);
			indicevertice = AdicionarVertice(Vertices2, Indices2, &posIndices, &posVertices, pontoMedioAB);

			indicevertice = AdicionarVertice(Vertices2, Indices2, &posIndices, &posVertices, pontoC);
			indicevertice = AdicionarVertice(Vertices2, Indices2, &posIndices, &posVertices, pontoMedioBC);
			indicevertice = AdicionarVertice(Vertices2, Indices2, &posIndices, &posVertices, pontoMedioCA);

			indicevertice = AdicionarVertice(Vertices2, Indices2, &posIndices, &posVertices, pontoA);
			indicevertice = AdicionarVertice(Vertices2, Indices2, &posIndices, &posVertices, pontoMedioCA);
			indicevertice = AdicionarVertice(Vertices2, Indices2, &posIndices, &posVertices, pontoMedioAB);

			indicevertice = AdicionarVertice(Vertices2, Indices2, &posIndices, &posVertices, pontoMedioBC);
			indicevertice = AdicionarVertice(Vertices2, Indices2, &posIndices, &posVertices, pontoMedioAB);
			indicevertice = AdicionarVertice(Vertices2, Indices2, &posIndices, &posVertices, pontoMedioCA);


		}
		Vertices2[10].color = { 1.0f,0.0f,0.0f };
		CopiarVet2para1();  //copia valores dos vetores 2 para os vetores 1 para poder repetir iteracao
	}


}

void Icosaedro::CopiarVet2para1()
{
	for (int i = 0; i < 16000; i++)
	{
		Indices[i] = Indices2[i];
		Indices2[i] = 0;
	}
	for (int i = 0; i < 3000; i++)
	{
		Vertices[i] = Vertices2[i];
		Vertices2[i] = Vertex(0,0,0);

	}
}

unsigned int Icosaedro::RetornarNumIndices() 
{
	return indicevertice;
}