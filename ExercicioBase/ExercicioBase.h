#pragma once
#define PERSPECTIVA  0
#define PARALELA  1

/// <summary>
/// Classe principal do programa
/// </summary>
/// 
/// 
class ExercicioBase
{
public:
	/// <summary>
	/// Construtor para a classe principal do programa
	/// </summary>
	/// <param name="argc">Nao utilizado</param>
	/// <param name="argv">Nao utilizado</param>
	ExercicioBase(int argc, char** argv);
	static void callback_MenuCB(int opcao);
	static void callback_MouseCB(int button, int state, int x, int y);
	static void callback_MotionCB(int x, int y);
	/// <summary>
	/// Funcao estatica para adaptar os callbacks do glut (linguagem C) para o metodo correspondente em c++
	/// </summary>
	static void callback_RenderSceneCB();
	/// <summary>
	/// Funcao estatica para adaptar os callbacks do glut (linguagem C) para o metodo correspondente em c++
	/// </summary>
	static void callback_KeyboardCB(unsigned char key, int mouse_x, int mouse_y);
	/// <summary>
	/// Funcao estatica para adaptar os callbacks do glut (linguagem C) para o metodo correspondente em c++
	/// </summary>
	static void callback_SpecialKeyboardCB(int key, int mouse_x, int mouse_y);


private:
	/// <summary>
	/// Funcao que roda em loop e envia os vertices e indices para renderizacao pelo OpenGL
	/// </summary>
	 void RenderSceneCB();
	 /// <summary>
	 /// Funcao para gerar a mesa
	 /// </summary>
	 /// <param name="WVP">Matriz de traformacao do mundo</param>
	 void DesenharMesa(Matrix4f WVP);
	 /// <summary>
	 /// Funcao para gerar o bule
	 /// </summary>
	 /// <param name="WVP">Matriz de traformacao do mundo</param>
	 void DesenharBule(Matrix4f WVP, Matrix4f transformacao);
	 /// <summary>
	/// Funcao para gerar o Icosaedro
	/// </summary>
	/// <param name="WVP">Matriz de traformacao do mundo</param>
	 void DesenharIcosaedro(Matrix4f WVP, Matrix4f transformacao);


	 /// <summary>
	 /// Funcao que toma conta das acoes geradas pelo pressionamento de teclas
	 /// Utilizada pelo callback do GLUT
	 /// </summary>
	 /// <param name="key">Tecla pressionada</param>
	 /// <param name="mouse_x">Posicao X do mouse quando a tecla foi pressionada</param>
	 /// <param name="mouse_y">Posicao Y do mouse quando a tecla foi pressionad</param>
	 void KeyboardCB(unsigned char key, int mouse_x, int mouse_y);
	 /// <summary>
	 /// Funcao que toma conta das acoes geradas pelo pressionamento de teclas
	 /// Utilizada pelo callback do GLUT
	 /// </summary>
	 /// <param name="key">Tecla pressionada</param>
	 /// <param name="mouse_x">Posicao X do mouse quando a tecla foi pressionada</param>
	 /// <param name="mouse_y">Posicao Y do mouse quando a tecla foi pressionad</param>
	 void SpecialKeyboardCB(int key, int mouse_x, int mouse_y);
	 /// <summary>
	 /// Adiciona arquivo shader ao OpenGL
	 /// </summary>
	 /// <param name="ShaderProgram">Referencia para o shader</param>
	 /// <param name="pShaderText">Ponteiro para o conteudo do arquivo shader</param>
	 /// <param name="ShaderType">Tipo do shader</param>
	 /// 
	 void MenuCB(int opcao);
	 void MouseCB(int button, int state, int x, int y);
	 void MotionCB(int x, int y);
	 void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);

	 /// <summary>
	 /// Adiciona e compila o shader.fs e shader.vs
	 /// </summary>
	 void CompileShaders();

	 /// <summary>
	 /// Configura parametros iniciais do GLUT
	 /// </summary>
	 /// <returns>Retorna 1 em caso de erro e 0 em caso de sucesso.</returns>
	 int startup();

	/// <summary>
	/// Arquivo de Vertex Shader a ser utilizado
	/// </summary>
	const char* pVSFileName = "shader.vs";

	/// <summary>
	/// Arquivo de Fragment Shader a ser utilizado
	/// </summary>
	const char* pFSFileName = "shader.fs";

	
};

/// <summary>
/// Objeto da classe ExercicioBase, programa principal
/// </summary>
//  ExercicioBase* exercicioBase;

/// <summary>
/// Ponto de entrada do programa
/// </summary>
int main(int argc, char** argv);