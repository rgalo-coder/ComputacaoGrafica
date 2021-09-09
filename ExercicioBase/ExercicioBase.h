#pragma once


class ExercicioBase
{
public:
	ExercicioBase(int argc, char** argv);
	
	static void callback_RenderSceneCB();
	static void callback_KeyboardCB(unsigned char key, int mouse_x, int mouse_y);
	static void callback_SpecialKeyboardCB(int key, int mouse_x, int mouse_y);


private:
	 void RenderSceneCB();
	 void DesenharMesa(Matrix4f WVP);

	 void DesenharBule(Matrix4f WVP, Matrix4f transformacao);

	 void DesenharIcosaedro(Matrix4f WVP, Matrix4f transformacao);



	 void KeyboardCB(unsigned char key, int mouse_x, int mouse_y);

	 void SpecialKeyboardCB(int key, int mouse_x, int mouse_y);

	 void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);

	 void CompileShaders();

	int startup();

	const char* pVSFileName = "shader.vs";
	const char* pFSFileName = "shader.fs";

};


ExercicioBase* exercicioBase;