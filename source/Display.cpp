#include "../headers/Display.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void cursorPos_callback(GLFWwindow* window, double posX, double posY);
static void error_callback(int error, const char* description);

bool isPressingW = false;
bool isPressingS = false;
bool isPressingA = false;
bool isPressingD = false;
bool isPressingY = false;
bool isPressingH = false;
bool pressedP = true;

int PREDKOSC = 1;

float AngleHor = 0;
float AngleVer = 0;

Display::Display() {
	//cameraPosX = cameraPosY = cameraPosZ = 0;
	//cameraPosX = 0.0f;
	
}
void Display::init() {
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional  
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version  
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version  
	//glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing  
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  

	

	//Declare a window object  
	//GLFWwindow* indow;

	//Create a window and create its OpenGL context  
	Window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Project", glfwGetPrimaryMonitor(), NULL);
	//Window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Project", NULL, NULL);
	//If the window couldn't be created  
	if (!Window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(Window);

	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(Window, key_callback);

	glfwSetCursorPosCallback(Window, cursorPos_callback);
	glfwSetCursorPos(Window, 0, 0);


	

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);*/


	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);*/

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Display::swapBuffers() {
	glfwSwapBuffers(Window);
}
void Display::pollEvents() {
	glfwPollEvents();
}
int Display::windowShouldClose() {
	return glfwWindowShouldClose(Window);
}
void Display::destroyWindowAndTerminate() {
	glfwDestroyWindow(Window);
	glfwTerminate();
}
void Display::prepare() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		isPressingD = true;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		isPressingD = false;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		isPressingA = true;
	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		isPressingA = false;
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		isPressingW = true;
	}
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		isPressingW = false;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		isPressingS = true;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		isPressingS = false;
	}
	if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
		isPressingY = true;
	}
	else if (key == GLFW_KEY_Y && action == GLFW_RELEASE) {
		isPressingY = false;
	}
	if (key == GLFW_KEY_H && action == GLFW_PRESS) {
		isPressingH = true;
	}
	else if (key == GLFW_KEY_H && action == GLFW_RELEASE) {
		isPressingH = false;
	}
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		pressedP = true;
	}
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		pressedP = false;
	}
	if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS) {
		if (++PREDKOSC == 21)
			PREDKOSC = 20;
	}
	if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS) {
		if (--PREDKOSC == 0)
			PREDKOSC = 1;
	}
	
}

static void cursorPos_callback(GLFWwindow* window, double posX, double posY) {
	
	static double lastPosX;
	static double lastPosY;

	static bool firstTime = true;

	if (firstTime == true) {
		lastPosX = posX;
		lastPosY = posY;
		firstTime = false;
	}

	double offsetX = posX - lastPosX;
	double offsetY = posY - lastPosY;

	lastPosX = posX;
	lastPosY = posY;

	AngleHor += offsetX;
	AngleVer -= offsetY;


	if (AngleVer > 89) AngleVer = 89;
	else if (AngleVer < -89) AngleVer = -89;

}