#pragma once

/// <summary>
/// Classe para gerar a mesa a partir de 5 cilindros 
/// 
/// (4 para as pernas e 1 para o tampao)
/// </summary>
class Mesa 
{
public:
	/// <summary>
	/// Construtor para a mesa
	/// </summary>
	/// <param name="VBO">Vertex Buffer para insercao dos dados de vertice</param>
	/// <param name="IBO">Index Buffer para insercao dos dados de indice</param>
	Mesa (GLuint* VBO, GLuint* IBO);

	/// <summary>
	/// Retorna o  numero de indices criados
	/// </summary>
	/// <returns>Numero de indices criados</returns>
	unsigned int RetornarNumIndices();

private:
	int Totalvertices;
	int TotalIndices;
};

/// <summary>
/// Classe para gerar cada cilindro
/// 
/// Gera os vertices e indices para um cilindro onde os circulos sao feitos por n-triangulos
/// </summary>
class Cilindro
{
public:
	/// <summary>
	/// Construtor para a mesa
	/// </summary>
	/// <param name="_numtriangulos">Numero de triangulos para a base</param>
	/// <param name="base">Vertex com as coordenadas do centro da base</param>
	/// <param name="raio">Raio da base</param>
	/// <param name="altura">Altura do cilindro</param>
	/// <param name="corR">Cor Red</param>
	/// <param name="corG">Cor Green</param>
	/// <param name="corB">Cor Blue</param>	
	Cilindro (int _numtriangulos, Vertex base, float raio, float altura, float corR, float corG, float corB);
	
	/// <summary>
	/// Vetor de vertices cilindro
	/// </summary>
	Vertex Vertices[1000];

	/// <summary>
	/// Vetor de indices do cilindro
	/// </summary>
	unsigned int Indices[1000] = {};

	/// <summary>
	/// Retorna o numero de vertices
	/// </summary>
	unsigned int NumeroVertices();

	/// <summary>
	/// retornar o numero de indices
	/// </summary>
	unsigned int NumeroIndices();

private:
	int n;
	float x, y, z, angulo;
	int ind;
};