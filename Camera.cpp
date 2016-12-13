#include "Camera.h"

Camera::Camera(float X, float Y, float Z) {
	this->X = X;
	this->Y = Y;
	this->Z = Z;
}

glm::vec3 Camera::getVec3() {
	return glm::vec3(X, Y, Z);
}

glm::vec3 Camera::getLookAt() {					//only works when camera position is (0,0,0) in glm::lookAt (first parameter)
	float cosAlfa = glm::cos(glm::radians(AngleHor));
	float cosBeta = glm::cos(glm::radians(AngleVer));
	float sinAlfa = glm::sin(glm::radians(AngleHor));
	float sinBeta = glm::sin(glm::radians(AngleVer));

	float x = cosAlfa*cosBeta;
	float y = sinBeta;
	float z = sinAlfa*cosBeta;

	return glm::vec3(x, y, z);
};
glm::vec3 Camera::getLookAt(glm::vec3 vector) {					//only works when camera position is (0,0,0) in glm::lookAt (first parameter)

	glm::vec3 out = glm::vec3(vector.x-X, vector.y-Y, vector.z-Z);


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

	float przes = 30 * ((float)(Now - LastTime) / CLOCKS_PER_SEC);

	//std::cout << AngleHor << std::endl;
	//std::cout << "X: "<<cameraPosX << std::endl;
	//std::cout << "Z: " << cameraPosZ << std::endl;

	if (isPressingA) {
		Z += przes * glm::sin(glm::radians(AngleHor - 90));
		X+= przes * glm::cos(glm::radians(AngleHor - 90));
	}
	if (isPressingD) {
		Z+= przes * glm::sin(glm::radians(AngleHor + 90));
		X+= przes * glm::cos(glm::radians(AngleHor + 90));
	}
	if (isPressingW) {
		if (FIRST_PERSON_MODE) {
			Z += przes * glm::sin(glm::radians(AngleHor));
			X += przes * glm::cos(glm::radians(AngleHor));
		}
		else {

		}
	}
	if (isPressingS) {
		Z-= przes * glm::sin(glm::radians(AngleHor));
		X-= przes * glm::cos(glm::radians(AngleHor));
	}

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