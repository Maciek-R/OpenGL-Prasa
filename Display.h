#ifndef DISPLAY_H
#define DISPLAY_H
#define GLEW_STATIC
#include <GL/glew.h>  

//Include GLFW  
#include <GLFW/glfw3.h>  

#include "Utils.h"
#include "GLOBALS.h"
#include <iostream>


class Display {

private:
	GLFWwindow* Window;
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;

public:
	Display();
	void init();
	void prepare();
	void swapBuffers();
	void pollEvents();
	int windowShouldClose();
	void destroyWindowAndTerminate();
	

};


#endif