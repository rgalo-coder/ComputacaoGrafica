#pragma once



//Ting: eh preciso especificar a variavel
//extern struct Vertex;
extern struct Vertex P[];

extern Vertex VerticesPatches[306];

extern unsigned int IndicesPatche[32][16];

struct Vertex;

class BuleUtah
{
public:
	BuleUtah(GLuint* VBO, GLuint* IBO);
	unsigned int RetornarNumIndices();

private:
	Vertex calcularCurvaBezier(Vertex* P, const float& t);
	Vertex calcularPatchBezier(Vertex* controlPoints, const float& u, const float& v);
	void RenderizarPatches();
	unsigned int totalIndices;
};