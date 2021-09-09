#pragma once



//Ting: eh preciso especificar a variavel
//extern struct Vertex;
extern struct Vertex P[];

extern Vertex VerticesPatches[306];

extern unsigned int IndicesPatche[32][16];

struct Vertex;


/// <summary>
/// Classe para gerar o Bule de Utah atraves de patches de Bezier
/// </summary>
class BuleUtah
{
public:
	/// <summary>
	/// Construtor para o bule de utah
	/// </summary>
	/// <param name="VBO">Vertex Buffer para insercao dos dados de vertice</param>
	/// <param name="IBO">Index Buffer para insercao dos dados de indice</param>
	BuleUtah(GLuint* VBO, GLuint* IBO);
	/// <summary>
	/// Retorna a quantidade de indices criados
	/// </summary>
	/// <returns>Quantidade de indices criados</returns>
	unsigned int RetornarNumIndices();

private:
	/// <summary>
	/// Calcula a curva de Bezier
	/// <returns>Vertice do ponto calculado</returns>
	/// </summary>
	Vertex calcularCurvaBezier(Vertex* P, const float& t);

	/// <summary>
	/// Calculao o patch de Bezier
	/// <returns>Vertice do ponto calculado</returns>
	/// </summary>
	Vertex calcularPatchBezier(Vertex* controlPoints, const float& u, const float& v);

	/// <summary>
	/// Renderiza os patches
	/// </summary>
	void RenderizarPatches();

	/// <summary>
	/// Total de indices
	/// </summary>
	unsigned int totalIndices;
};