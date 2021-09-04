#pragma once


void CriarBuleUtah(GLuint* VBO, GLuint* IBO);

extern struct Vertex;

Vertex calcularCurvaBezier(Vertex* P, const float& t);

Vertex calcularPatchBezier(Vertex* controlPoints, const float& u, const float& v);

void RenderizarPatches();

struct Vertex;
