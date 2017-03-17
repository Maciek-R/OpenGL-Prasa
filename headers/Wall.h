#ifndef WALL_H
#define WALL_H

#include "Shape.h"
class Wall : public Shape {
private:
	GLfloat VERTICES[18] = {
		-1.0, 1.0, 0.0,
		-1.0, -1.0, 0.0,
		1.0, -1.0, 0.0,
		1.0, -1.0, 0.0,
		1.0, 1.0, 0.0,
		-1.0, 1.0, 0.0
	};
	GLfloat COLORS[18] = {
		1,0,0,
		1,0,0,
		1,0,0,
		0,1,0,
		0,1,0,
		0,1,0
	};


	GLfloat TEXTURE_COORDS[12] = {
		0,1,
		0,0,
		1,0,
		1,0,
		1,1,
		0,1
	};

	GLfloat NORMALS[18] = {
		0,0,1,
		0,0,1,
		0,0,1,
		0,0,1,
		0,0,1,
		0,0,1
	};

	float RotationY;
	float RotationZ;

	float scaleX;
	float scaleY;
	float scaleZ;
	void init(Camera *, Light *, float, float, float, float, float);
public:
	Wall(Camera*, Light*, float, float, float, float, float);
	Wall(Camera*, Light*, float, float, float, float, float, float, float, float);
	//void createShader();
	void createWall();
	void drawWall();
	void setMulti(int);

};

#endif