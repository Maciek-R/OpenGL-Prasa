#include "../headers/Camera.h"

Camera::Camera(float X, float Y, float Z) {
	this->X = X;
	this->Y = Y;
	this->Z = Z;
	srand(time(NULL));
}

glm::vec3 Camera::getVec3() {
	return glm::vec3(X, Y, Z);
}

glm::vec3 Camera::getLookAt() {					
	float cosAlfa = glm::cos(glm::radians(AngleHor));
	float cosBeta = glm::cos(glm::radians(AngleVer));
	float sinAlfa = glm::sin(glm::radians(AngleHor));
	float sinBeta = glm::sin(glm::radians(AngleVer));

	float x = cosAlfa*cosBeta;
	float y = sinBeta;
	float z = sinAlfa*cosBeta;

	return glm::vec3(x, y, z);
};

void Camera::serveEvents(){
	clock_t Now = clock();

	if (LastTime == 0)
		LastTime = Now;

	float przes =10*  ((float)(Now - LastTime) / CLOCKS_PER_SEC);

	if (isPressingA) {
		Z += przes * glm::sin(glm::radians(AngleHor - 90));
		X+= przes * glm::cos(glm::radians(AngleHor - 90));
	}
	if (isPressingD) {
		Z+= przes * glm::sin(glm::radians(AngleHor + 90));
		X+= przes * glm::cos(glm::radians(AngleHor + 90));
	}
	if (isPressingW) {
			Z += przes * glm::sin(glm::radians(AngleHor));
			X += przes * glm::cos(glm::radians(AngleHor));
		
	}
	if (isPressingS) {
		Z-= przes * glm::sin(glm::radians(AngleHor));
		X-= przes * glm::cos(glm::radians(AngleHor));
	}
	if (isPressingY) {
		Y += przes;
	}
	if (isPressingH) {
		Y -= przes;
	}


	if (X < 0.15) X = 0.15;
	else if (X > 11.85) X = 11.85;

	if (Z < 0.15) Z = 0.15;
	else if (Z > 11.85) Z = 11.85;

	if (Y < 0.15) Y = 0.15;
	else if (Y > 11.85) Y = 11.85;

	LastTime = Now;
}
float Camera::getX() {
	return X;
}
float Camera::getY() {
	return Y;
}
float Camera::getZ() {
	return Z;
}
void Camera::setX(float X) {
	this->X = X;
}
void Camera::setY(float Y) {
	this->Y = Y;
}
void Camera::setZ(float Z) {
	this->Z = Z;
}