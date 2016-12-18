#ifndef WALL_H
#define WALL_H

#include "Shape.h"
#include "SOIL.h"
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

	GLuint Model_Location;
	GLuint View_Location;
	GLuint Projection_Location;
	GLint lightPosLoc;

	GLuint texture0;
	GLuint texId;
	GLuint LoadMipmapTexture(GLuint texId, const char* fname);
	float RotationY;
	float RotationZ;

	float scaleX;
	float scaleY;
	float scaleZ;
public:
	Wall(Camera*, float, float, float, float, float);
	Wall(Camera*, float, float, float, float, float, float, float, float);
	void createShader();
	void createWall();
	void drawWall();

};

#endif