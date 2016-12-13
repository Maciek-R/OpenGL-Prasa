#include "Triangle.h"

Triangle::Triangle(Camera * cam) {
	this->cam = cam;

	posX = 3;
	posY = 1;
	posZ = 0;

}

void Triangle::createNewTriangle() {


	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);


	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);

	glGenBuffers(1, &colorId);
	glBindBuffer(GL_ARRAY_BUFFER, colorId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(COLORS), COLORS, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);

	glGenBuffers(1, &eboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Triangle::drawNewTriangle() {
	float CubeAngle;





	glm::mat4  ProjectionMatrix = glm::perspective(glm::radians(70.0f), (float)1024 / (float)768, 0.1f, 100.0f);
	glm::mat4  ViewMatrix = glm::lookAt(cam->getVec3(), cam->getVec3() + cam->getLookAt(), glm::vec3(0, 1, 0));
	glm::mat4  ModelMatrix = glm::mat4(1.0f);




	//YYY = glm::sin(Angle);
	//ZZZ = glm::cos(Angle);

	//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(3-cam->getX(),  -1-cam->getY(),  0-cam->getZ()));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(posX, posY, posZ));

	//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(XXX - 1 - cameraPosX, YYY - cameraPosY, 0 - cameraPosZ));
	//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(XXX - 1 - cameraPosX, -1 - cameraPosY, 0 - cameraPosZ));
	ModelMatrix = glm::rotate(ModelMatrix, Angle / 5, glm::vec3(0, 1, 0));
	//ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1, 1, 1));


	glm::mat4 mvp = ProjectionMatrix*ViewMatrix*  ModelMatrix;


	glUseProgram(ProgramId);
	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);

	glBindVertexArray(vaoId);
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (GLvoid*)0);
	glBindVertexArray(0);
	glUseProgram(0);
}