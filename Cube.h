#ifndef CUBE_H
#define CUBE_H
#include "Shape.h"
#include <SOIL.h>
#include "Walec.h"
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
	char* textureName;

	GLint lightPosLoc;
	GLuint texture0;
	float scaleX;
	float scaleY;
	float scaleZ;
	float RotateZ;
	Walec * walec;
public:
	Cube(Camera *);
	Cube(Camera *, float, float, float);
	Cube(Camera *, float, float, float, float, float, float);
	void createShader();
	void drawCube();
	void createCube();
	void setTexture(char *);
	void move(int);
	void doNotMove();
	void setScaleYOf(Walec *);
	void setRotateZ(float Z);

};

#endif