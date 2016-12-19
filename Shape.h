#ifndef SHAPE_H
#define SHAPE_H

#include <math.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <iostream>
#include "Camera.h"
#include "Light.h"
#include "SOIL.h"

static const double PI = 3.14159265358979323846;
class Shape {
protected:
	GLuint
		VertexShaderId,
		FragmentShaderId,
		ProgramId,

		vaoId,
		vboId,
		colorId,
		normalId,
		texId;

	char* textureName;

	GLuint Model_Location;
	GLuint View_Location;
	GLuint Projection_Location;
	GLint lightPosLoc;
	GLint lightColorLoc;
	GLint ambientColorLoc;
	GLint MultiLoc;
	GLuint texture0;

	Camera * cam;
	Light * light;
	float posX = 3;
	float posY = 0;
	float posZ = 0;
	float Angle;
	float przes;
	int multi;
	clock_t LastTime = 0;

	glm::mat4 ProjectionMatrix;
	glm::mat4  ViewMatrix;
	glm::mat4  ModelMatrix;
	GLuint LoadMipmapTexture(GLuint texId, const char* fname);
	void destroyVbo();
	void destroyShaders();
	void loadUniformLocations();
public:
	Shape();
	~Shape();
	
	float getZ();
	float getY();
	void setZ(float Z);

	void setTexture(char *);

	virtual void create();
	virtual void draw();
	virtual void createShader();
	virtual void serveTime();
	virtual void doNotMove();
	virtual void move(int);
	virtual void setScaleYOf(Shape *);
	
};


#endif