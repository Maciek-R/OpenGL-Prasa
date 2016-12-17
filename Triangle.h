#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"

class Triangle : public Shape {
private:

	GLuint INDICES[18]=
	{
		0,3,1,
		1,3,2,
		0,1,4,
		1,2,4,
		2,3,4,
		3,0,4
	};
	
	GLfloat VERTICES[15] =
	{ -.5f,  0,   .5f,
		.5f,  0,   .5f,
		.5f,  0,  -.5f,
		-.5f, 0,  -.5f,
		0, 1,     0 };

	GLfloat COLORS[15] =
	{ 0, 0, 1,
		1, 0, 0,
		0, 1, 0,
		0, 1, 1,
		1, 1, 0};
		
	

public:
	Triangle(Camera*);
	void createNewTriangle();
	void drawNewTriangle();


};

#endif