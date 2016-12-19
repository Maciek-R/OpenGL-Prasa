#include "Light.h"

const GLchar* VertexShaderLight =
{
	"#version 400\n"\

	"layout(location=0) in vec3 in_Position;\n"\

	"out vec4 ex_Color;\n"\

	"uniform mat4 ModelMatrix;\n"
	"uniform mat4 ViewMatrix;\n"
	"uniform mat4 ProjectionMatrix;\n"

	"uniform vec3 lightColor;\n"

	"void main(void)\n"\
	"{\n"\
	"gl_Position = ProjectionMatrix*ViewMatrix*ModelMatrix * vec4(in_Position, 1.0);\n"\
	"  ex_Color = vec4(lightColor, 1.0);\n"\
	"}\n"
};

const GLchar* FragmentShaderLight =
{
	"#version 400\n"\
	"in vec4 ex_Color;\n"\
	"out vec4 out_Color;\n"\

	"void main(void)\n"\
	"{\n"\
	"out_Color = ex_Color;\n"\
	"}\n"
};

Light::Light(Camera* cam) {
	posX = 3;
	posY = 5.0f;
	posZ = 1;
	this->cam = cam;
	lightColor.r = 1;
	lightColor.g = 1;
	lightColor.b = 1;
	ambientColor.r = 0.25;
	ambientColor.g = 0.25;
	ambientColor.b = 0.25;
	dir = 0;
}

void Light::createShader() {
	ProgramId = glCreateProgram();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShaderLight, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShaderLight, NULL);
	glCompileShader(FragmentShaderId);


	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);

	Model_Location = glGetUniformLocation(ProgramId, "ModelMatrix");
	View_Location = glGetUniformLocation(ProgramId, "ViewMatrix");
	Projection_Location = glGetUniformLocation(ProgramId, "ProjectionMatrix");
	lightColorLoc = glGetUniformLocation(ProgramId, "lightColor");
}

void Light::createLight()
{
	GLfloat VERTICES[] = {
		-0.5f, -0.5f, -0.5f,	
		0.5f, -0.5f, -0.5f,		
		0.5f,  0.5f, -0.5f,		 
		0.5f,  0.5f, -0.5f,		
		-0.5f,  0.5f, -0.5f,	
		-0.5f, -0.5f, -0.5f,	

		-0.5f, -0.5f,  0.5f,	
		0.5f, -0.5f,  0.5f,		 
		0.5f,  0.5f,  0.5f,		
		0.5f,  0.5f,  0.5f,		
		-0.5f,  0.5f,  0.5f,	
		-0.5f, -0.5f,  0.5f,	 

		-0.5f,  0.5f,  0.5f,	
		-0.5f,  0.5f, -0.5f,	
		-0.5f, -0.5f, -0.5f,	
		-0.5f, -0.5f, -0.5f,	
		-0.5f, -0.5f,  0.5f,	
		-0.5f,  0.5f,  0.5f,	

		0.5f,  0.5f,  0.5f,		
		0.5f,  0.5f, -0.5f,		
		0.5f, -0.5f, -0.5f,		 
		0.5f, -0.5f, -0.5f,		
		0.5f, -0.5f,  0.5f,		
		0.5f,  0.5f,  0.5f,		

		-0.5f, -0.5f, -0.5f,	 
		0.5f, -0.5f, -0.5f,		 
		0.5f, -0.5f,  0.5f,		 
		0.5f, -0.5f,  0.5f,		
		-0.5f, -0.5f,  0.5f,	
		-0.5f, -0.5f, -0.5f,	

		-0.5f,  0.5f, -0.5f,	 
		0.5f,  0.5f, -0.5f,		
		0.5f,  0.5f,  0.5f,		
		0.5f,  0.5f,  0.5f,		 
		-0.5f,  0.5f,  0.5f,	 
		-0.5f,  0.5f, -0.5f
	};

	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Light::drawLight() {
	glm::mat4 ProjectionMatrix, ViewMatrix, ModelMatrix;

	ProjectionMatrix = glm::perspective(glm::radians(70.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
	ViewMatrix = glm::lookAt(cam->getVec3(), cam->getVec3() + cam->getLookAt(), glm::vec3(0, 1, 0));
	ModelMatrix = glm::mat4(1.0f);

	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(posX, posY, posZ));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.5, 0.5, 0.5));

	glUseProgram(ProgramId);

	glUniformMatrix4fv(Model_Location, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(View_Location, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix4fv(Projection_Location, 1, GL_FALSE, &ProjectionMatrix[0][0]);
	glUniform3f(lightColorLoc, lightColor.x, lightColor.y, lightColor.z);

	glBindVertexArray(vaoId);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Light::move() {

	float przesu = przes;
	if (dir == 0) {
		posX += przesu;
		if (posX >= 11) dir = 1;
	}
	else if (dir == 1) {
		posZ += przesu;
		if (posZ >= 11) dir = 2;
	}
	else if (dir == 2) {
		posX -= przesu;
		if (posX <= 1) dir = 3;
	}
	else if (dir == 3) {
		posZ -= przesu;
		if (posZ <= 1) dir = 0;
	}
	
}
void Light::serveTime() {
	clock_t Now = clock();

	if (LastTime == 0)
		LastTime = Now;

	przes = 10 * ((float)(Now - LastTime) / CLOCKS_PER_SEC);

	LastTime = Now;
}

float Light::getX() {
	return posX;
}
float Light::getY() {
	return posY;
}
float Light::getZ() {
	return posZ;
}

float Light::getColorR() {
	return lightColor.r;
}
float Light::getColorG() {
	return lightColor.g;
}
float Light::getColorB() {
	return lightColor.b;
}

glm::vec3 Light::getAmbientColor() {
	return ambientColor;
}