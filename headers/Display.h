#ifndef DISPLAY_H
#define DISPLAY_H
#define GLEW_STATIC
#include <GL/glew.h>  

//Include GLFW  
#include <GLFW/glfw3.h>  

#include "GLOBALS.h"
#include <iostream>


class Display {

private:
	GLFWwindow* Window;

public:
	Display();
	void init();
	void prepare();
	void swapBuffers();
	void pollEvents();
	int windowShouldClose();
	void destroyWindowAndTerminate();
	//void Display::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	//void Display::error_callback(int error, const char* description);
};


#endif