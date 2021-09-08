#pragma once



class Icosaedro
{
public:
	Icosaedro(GLuint* VBO, GLuint* IBO, int graus);
	unsigned int RetornarNumIndices();
private:
	int indicevertice;
	void SubdividirIcosaedro(int graus);

	void CopiarVet2para1();

	Vertex PontoMedio(Vertex ponto1, Vertex ponto2);

	int Buscar(Vertex* vertices, int size, Vertex target);
	
	int AdicionarVertice(Vertex* vertices, unsigned int* indices, int* posI, int* posV, Vertex ponto);

};


