#ifndef SHAPE_H
#define SHAPE_H

//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
#include "Utils.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <iostream>
#include "Camera.h"

class Shape {
protected:
	GLuint
		VertexShaderId,
		FragmentShaderId,
		ProgramId,

		mvp_location,
		//BufferIds[3] = { 0 },
		vaoId,
		vboId,
		colorId,
		eboId;

	Camera * cam;
	float posX = 3;
	float posY = 0;
	float posZ = 0;
	float Angle;
	clock_t LastTime = 0;
public:
	Shape();
	Shape(Camera *);
	

	

	void createTriangle();
	void drawTriangle();
	virtual void createShader();
	void serveTime();
};

#endif