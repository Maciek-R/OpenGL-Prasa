#ifndef LIGHT_H
#define LIGHT_H
#include "Camera.h"
#include <math.h>
#include <time.h>
#include <cmath>
#include <GL/glew.h>


class Light {
private:
	glm::vec3 lightColor;
	glm::vec3 ambientColor;

	GLuint
		VertexShaderId,
		FragmentShaderId,
		ProgramId,

		vaoId,
		vboId;

	GLuint Model_Location;
	GLuint View_Location;
	GLuint Projection_Location;
	GLint lightColorLoc;
	Camera * cam;
	//Light * light;
	float posX = 3;
	float posY = 0;
	float posZ = 0;
	float Angle;
	float przes;
	clock_t LastTime = 0;

public:
	Light(Camera *);

	void createShader();
	void createLight();
	void drawLight();
	void move();
	void serveTime();

	float getX();
	float getY();
	float getZ();
	
	float getColorR();
	float getColorG();
	float getColorB();

	glm::vec3 getAmbientColor();
};

#endif