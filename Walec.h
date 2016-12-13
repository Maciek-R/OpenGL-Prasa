#ifndef WALEC_H
#define WALEC_H

#include "Shape.h"

#define VERTEX_COUNT 30		//liczba wierzcho³ków podstawy

class Walec : public Shape {

private:
	/*GLuint INDICES[96] =
	{
		8,1,0,
		8,2,1,
		8,3,2,
		8,4,3,
		8,5,4,
		8,6,5,
		8,7,6,
		8,0,7,

		17,10,9,
		17,11,10,
		17,12,11,
		17,13,12,
		17,14,13,
		17,15,14,
		17,16,15,
		17,9,16,

		9,0,1,
		9,1,10,
		10,1,2,
		10,2,11,
		11,2,3,
		11,3,12,
		12,3,4,
		12,4,13,
		13,4,5,
		13,5,14,
		14,5,6,
		14,6,15,
		15,6,7,
		15,7,16,
		16,7,0,
		16,0,9
	};

	GLfloat VERTICES[54] =
	{ -.38f,  0.92f,   0,
		.38f,  0.92f,   0,
		.92f,  0.38f,  0,
		.92f,  -0.38f,  0,
		.38f,  -0.92f,   0,
		-.38f,  -0.92f,   0,
		-.92f,  -0.38f,  0,
		-.92f,  0.38f,  0,
		0,0,0,
		-.38f,  0.92f,   0.5f,
		.38f,  0.92f,   0.5f,
		.92f,  0.38f,  0.5f,
		.92f,  -0.38f,  0.5f,
		.38f,  -0.92f,   0.5f,
		-.38f,  -0.92f,   0.5f,
		-.92f,  -0.38f,  0.5f,
		-.92f,  0.38f,  0.5f,
		0,0,0.5f

	};

	GLfloat COLORS[54] =
	{   0, 0, 1,
		1, 0, 0,
		0, 1, 0,
		0, 1, 1,
		1, 1, 0, 
		1, 0, 0,
		0, 1, 0,
		0, 1, 1 ,
		0,0,0,
		0, 0, 1,
		1, 0, 0,
		0, 1, 0,
		0, 1, 1,
		1, 1, 0,
		1, 0, 0,
		0, 1, 0,
		0, 1, 1 ,
		0,0,0 };*/

	//GLfloat VERTICES[(VERTEX_COUNT*3)*2 + (VERTEX_COUNT*6)];
	GLfloat VERTICES[(VERTEX_COUNT * 3)*3*2 + (VERTEX_COUNT*6*3)];
	GLfloat COLORS[(VERTEX_COUNT * 3)*3*2 + (VERTEX_COUNT * 6 * 3)];

	GLuint Model_Location;
	GLuint View_Location;
	GLuint Projection_Location;
public:
	Walec(Camera *);
	void createShader();
	void createWalec();
	void drawWalec();
};


#endif