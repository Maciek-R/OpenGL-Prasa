#ifndef CUBE_H
#define CUBE_H
#include "Shape.h"
#include <SOIL.h>
class Cube : public Shape {
private:

	GLuint INDICES[18] =
	{
		0,3,1,
		1,3,2,
		0,1,4,
		1,2,4,
		2,3,4,
		3,0,4
	};

	GLfloat VERTICES[20] =
	{ -.5f,  0,   .5f, 1,
		.5f,  0,   .5f, 1,
		.5f,  0,  -.5f, 1,
		-.5f, 0,  -.5f, 1,
		0, 1,     0, 1 };

	GLfloat COLORS[20] =
	{ 0, 0, 1, 1,
		1, 0, 0, 1,
		0, 1, 0, 1,
		0, 1, 1, 1,
		1, 1, 0, 1 };

	GLuint Model_Location;
	GLuint View_Location;
	GLuint Projection_Location;


	GLint lightPosLoc;
	GLuint texture0;
public:
	Cube(Camera *);
	void createShader();
	void drawCube();
	void createCube();

};

#endif