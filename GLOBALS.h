#ifndef GLOBALS_H
#define GLOBALS_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

extern float AngleHor;
extern float AngleVer;

extern bool isPressingW;
extern bool isPressingS;
extern bool isPressingA;
extern bool isPressingD;
extern bool isPressingY;
extern bool isPressingH;
extern bool pressedP;

extern int PREDKOSC;

/*static glm::vec3 getLookAt() {					//only works when camera position is (0,0,0) in glm::lookAt (first parameter)
	float cosAlfa = glm::cos(glm::radians(AngleHor));
	float cosBeta = glm::cos(glm::radians(AngleVer));
	float sinAlfa = glm::sin(glm::radians(AngleHor));
	float sinBeta = glm::sin(glm::radians(AngleVer));

	float x = cosAlfa*cosBeta;
	float y = sinBeta;
	float z = sinAlfa*cosBeta;

	return glm::vec3(x, y, z);
};*/

/*static glm::vec3 getLookAt(glm::vec3 vector) {					//only works when camera position is (0,0,0) in glm::lookAt (first parameter)
	float cosAlfa = glm::cos(glm::radians(AngleHor));
	float cosBeta = glm::cos(glm::radians(AngleVer));
	float sinAlfa = glm::sin(glm::radians(AngleHor));
	float sinBeta = glm::sin(glm::radians(AngleVer));

	float x = cosAlfa*cosBeta;
	float y = sinBeta;
	float z = sinAlfa*cosBeta;

	return glm::vec3(x, y, z);
};*/

#endif