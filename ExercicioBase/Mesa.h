#pragma once

class Mesa 
{
public:
	Mesa (GLuint* VBO, GLuint* IBO);
	unsigned int RetornarNumIndices();

private:
	int Totalvertices;
	int TotalIndices;
};