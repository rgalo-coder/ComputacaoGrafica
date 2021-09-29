#pragma once


/// <summary>
/// Classe para gerar o Icosaedro e subdividi-lo
/// </summary>
class Icosaedro
{
public:
	/// <summary>
	/// Construtor para geracao do Icosaedro subdivido
	/// 
	/// </summary>
	/// <param name="VBO">Vertex Buffer para insercao dos dados de vertice</param>
	/// <param name="IBO">Index Buffer para insercao dos dados de indice</param> 
	/// <param name="graus">quantidade de vezes que o icosaedro sera subdivido</param>
	Icosaedro(GLuint* VBO, GLuint* IBO, int graus);

	/// <summary>
	/// Retorna a quantidade de indices criados
	/// </summary>
	/// <returns></returns>
	unsigned int RetornarNumIndices();

	void HSVtoRGB(float H, float S, float V, float* rgb);

	void OnKeyboard(unsigned char Key);





private:
	GLuint* VBO;
	GLuint* IBO;
	void AtualizarBuffer();

	float CorHSV_h, CorHSV_s, CorHSV_v;
	void AtualizarCor();
	int indicevertice;
	/// <summary>
	/// Subdivide icosaedro pelo numero de graus desejado
	/// </summary>
	void SubdividirIcosaedro(int graus);

	float cor[3];
	/// <summary>
	/// Copia vetores 2 para vetores 1
	/// </summary>
	void CopiarVet2para1();

	/// <summary>
	/// Calcula ponto medio entre dois pontos
	/// </summary>
	Vertex PontoMedio(Vertex ponto1, Vertex ponto2);

	/// <summary>
	/// Busca se determinado ponto já existe no vetor de vertices
	/// </summary>
	/// <returns>Indice em que o ponto foi encontrado. Retorna -1 caso não encontre</returns>
	int Buscar(Vertex* vertices, int size, Vertex target);
	
	/// <summary>
	/// Adiciona determinado ponto no vetor de vertices
	/// </summary>
	/// <returns>Indice qual a posicao do vetor de indices que o ponto foi adicionado</returns>
	int AdicionarVertice(Vertex* vertices, unsigned int* indices, int* posI, int* posV, Vertex ponto);

};


