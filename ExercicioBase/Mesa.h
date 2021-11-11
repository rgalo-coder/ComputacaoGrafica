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

