#ifndef CAMERA_H
#define CAMERA_H

#include "GLOBALS.h"
#include <stdlib.h>  
#include <time.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
using namespace std;
class Camera {
private:
	float X;
	float Y;
	float Z;

	clock_t LastTime = 0;
public:
	Camera(float, float, float);
	glm::vec3 getLookAt();

	glm::vec3 getVec3();
	void serveEvents();
	
	void setX(float);
	void setY(float);
	void setZ(float);

	float getX();
	float getY();
	float getZ();

};

#endif