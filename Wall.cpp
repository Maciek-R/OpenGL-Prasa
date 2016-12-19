#include "Wall.h"

Wall::Wall(Camera * cam, Light * light, float X, float Y, float Z, float rotationY, float rotationZ) {
	init(cam, light, X, Y, Z, rotationY, rotationZ);

	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	
}

Wall::Wall(Camera * cam, Light * light, float X, float Y, float Z, float scaleX, float scaleY, float scaleZ, float rotationY, float rotationZ) {
	init(cam, light, X, Y, Z, rotationY, rotationZ);

	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
	
}

void Wall::init(Camera * cam, Light* light, float X, float Y, float Z, float rotationY, float rotationZ) {
	this->cam = cam;
	this->light = light;
	posX = X;
	posY = Y;
	posZ = Z;
	RotationY = rotationY;
	RotationZ = rotationZ;
	this->textureName = "res/deski.png";
	multi = 1;
}


void Wall::createWall() {


	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);


	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

	glGenBuffers(1, &colorId);
	glBindBuffer(GL_ARRAY_BUFFER, colorId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(COLORS), COLORS, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

	glGenBuffers(1, &normalId);
	glBindBuffer(GL_ARRAY_BUFFER, normalId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(NORMALS), NORMALS, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

	glGenBuffers(1, &texId);
	glBindBuffer(GL_ARRAY_BUFFER, texId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TEXTURE_COORDS), TEXTURE_COORDS, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (GLvoid*)0);



	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	texture0 = LoadMipmapTexture(GL_TEXTURE0, textureName);
}

void Wall::drawWall() {

	ViewMatrix = glm::lookAt(cam->getVec3(), cam->getVec3() + cam->getLookAt(), glm::vec3(0, 1, 0));
	ModelMatrix = glm::mat4(1.0f);

	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(posX, posY, posZ));
	ModelMatrix = glm::rotate(ModelMatrix, RotationY * (float)(PI / 180), glm::vec3(0, 1, 0));
	ModelMatrix = glm::rotate(ModelMatrix, RotationZ * (float)(PI / 180), glm::vec3(1, 0, 0));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(scaleX, scaleY, scaleZ));



	
	glUseProgram(ProgramId);
	loadUniformLocations();

	
	glBindVertexArray(vaoId);
	glDrawArrays(GL_TRIANGLES, 0, _countof(VERTICES) / 3);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Wall::setMulti(int a) {
	multi = a;
}