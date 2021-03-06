#pragma once
#define PERSPECTIVA  0
#define PARALELA  1

#define FLAT  1
#define GOURAUD  2
#define PHONG  3

#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 1024
#define SHADOW_WIDTH  1024
#define SHADOW_HEIGHT 1024

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
	/// <summary>
	/// Cria o menu com o botao direito
	/// </summary>
	/// <param name="opcao"></param>
	static void callback_MenuCB(int opcao);
	/// <summary>
	/// Recebe os comandos do mouse
	/// </summary>
	/// <param name="button">botao utilizado</param>
	/// <param name="state">se o botao foi pressionado ou solto</param>
	/// <param name="x">posicao x durante o evento</param>
	/// <param name="y">posicao y durante o evento</param>
	static void callback_MouseCB(int button, int state, int x, int y);
	/// <summary>
	/// Recebe o movimento do mouse na janela
	/// </summary>
	/// <param name="x">Movimento no eixo x</param>
	/// <param name="y">Movimento no eixo y</param>
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
	 

	 void DesenharObjeto(Matrix4f WVP, Matrix4f transformacao, unsigned int numIndices, Material gMaterial, GLuint& _VBO, GLuint& _IBO);
	


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
	 void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	 /// <summary>
	 /// Cria o menu com o botao direito
	 /// </summary>
	 /// <param name="opcao"></param>
	 void MenuCB(int opcao);
	 /// <summary>
	 /// Recebe os comandos do mouse
	 /// </summary>
	 /// <param name="button">botao utilizado</param>
	 /// <param name="state">se o botao foi pressionado ou solto</param>
	 /// <param name="x">posicao x durante o evento</param>
	 /// <param name="y">posicao y durante o evento</param>
	 void MouseCB(int button, int state, int x, int y);

	 /// <summary>
	 /// Recebe o movimento do mouse na janela
	 /// </summary>
	 /// <param name="x">Movimento no eixo x</param>
	 /// <param name="y">Movimento no eixo y</param>
	 void MotionCB(int x, int y);

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
	const char* pVSFileName = "vs.glsl";

	/// <summary>
	/// Arquivo de Fragment Shader a ser utilizado
	/// </summary>
	const char* pFSFileName = "fs.glsl";



	void RenderScene();
	
};

/// <summary>
/// Objeto da classe ExercicioBase, programa principal
/// </summary>
//  ExercicioBase* exercicioBase;


/// <summary>
/// Ponto de entrada do programa
/// </summary>
int main(int argc, char** argv);

GLuint VBO[3];
GLuint IBO[3];
GLuint gWVPLocation;
GLuint gCorHSVIcosaedro;
GLuint VAO;
GLuint gCorLuzLocation;
GLuint gPosLuzLocation;
GLuint gWVPLuzLocation;
GLuint gModelLocation;
GLuint gMaterialLocation_ka, gMaterialLocation_ks, gMaterialLocation_kd, gMaterialLocation_shininess;
GLuint gmodoIluminacaoLocation;
GLuint gmodoShadowMapLocation;
GLuint gLightSpaceMatrixLocation;

ExercicioBase* exercicioBase;

int TipoProjecao;
int ModoIluminacao = 1;

WorldTrans TransBule, TransIcosaedro, TransMesa;

Camera GameCamera(WINDOW_WIDTH, WINDOW_HEIGHT);
Camera LuzCamera(SHADOW_WIDTH, SHADOW_HEIGHT);
bool mousebotaoesquerdo = false;

Icosaedro* icosaedro;
Mesa* mesa;
BuleUtah* bule;

float FOV = 45.0f;
float zNear = 1.0f;
float zFar = 6.0f;

PersProjInfo _PersProjInfo = { FOV, WINDOW_WIDTH, WINDOW_HEIGHT, zNear, zFar };
PersProjInfo _LightProjInfo = { FOV, WINDOW_WIDTH, WINDOW_HEIGHT, zNear, zFar };
OrthoProjInfo _OrthoProjInfo = { 2.0f, -2.0f , -2.0f, +2.0f, zNear, zFar };

Vector3f CorLuz = { 1.0f, 1.0f,1.0f };
Vector3f PosicaoLuz = { +2.0f, +2.0f, -0.8f };

Matrix4f Identidade;

unsigned int numTotalIndices, numIndicesMesa, numIndicesIcosaedro, numIndicesBule = 0;


GLuint depthMapFBO, depthMap;



