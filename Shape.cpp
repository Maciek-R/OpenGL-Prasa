#include "Shape.h"
const GLchar* VertexShader =
{
	"#version 400\n"\

	"layout(location=0) in vec3 in_Position;\n"\
	"layout(location=1) in vec3 in_Color;\n"\
	"layout(location = 2) in vec2 texCoord;\n"\
	"out vec4 ex_Color;\n"\
	"out vec2 TexCoord;\n"\
	//"uniform mat4 ModelMatrix;\n"
	//"uniform mat4 ViewMatrix;\n"
	//"uniform mat4 ProjectionMatrix;\n"
	"uniform mat4 mvp;\n"\
	"void main(void)\n"\
	"{\n"\
	//"gl_Position = in_Position;\n"
	//"  gl_Position = (ProjectionMatrix * ViewMatrix * ModelMatrix) * in_Position;\n"
	//"gl_Position = ViewMatrix * ModelMatrix * in_Position;\n"
	"gl_Position = mvp * vec4(in_Position, 1.0);\n"\
	"  ex_Color = vec4(in_Color, 1.0);\n"\
	"TexCoord = texCoord;\n"\
	"}\n"
};

const GLchar* FragmentShader =
{
	"#version 400\n"\

	"in vec4 ex_Color;\n"\
	"in vec2 TexCoord;\n"\
	"out vec4 out_Color;\n"\

	"uniform sampler2D Texture0;\n"\

	"void main(void)\n"\
	"{\n"\
	/*"  out_Color = ex_Color;\n"\*/
	"  out_Color = texture(Texture0, TexCoord*5);\n"\
	"}\n"
};

Shape::Shape() {

}
Shape::Shape(Camera *cam) {
	this->cam = cam;
}





/*void Shape::drawCube(void)
{
	float CubeAngle;


	glm::mat4  ProjectionMatrix = glm::perspective(glm::radians(70.0f), (float)1024 / (float)768, 0.1f, 100.0f);
	glm::mat4  ViewMatrix = glm::lookAt(glm::vec3(0, 0, 0), cam->getLookAt(), glm::vec3(0, 1, 0));
	glm::mat4  ModelMatrix = glm::mat4(1.0f);
	//glm::mat4 viewMatrix = glm::look

	//Angle += 5 * ((float)(Now - LastTime) / CLOCKS_PER_SEC);


	//YYY = glm::sin(Angle);
	//ZZZ = 3*glm::cos(Angle);
	

	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(posX+1-cam->getX(), posY-cam->getY(), posZ-cam->getZ()));
	ModelMatrix = glm::rotate(ModelMatrix, 0.3f, glm::vec3(1, 1, 0));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.5f, 0.5, 0.5));




	glm::mat4 mvp = ProjectionMatrix*ViewMatrix*  ModelMatrix;



	glUseProgram(ProgramId);
	ExitOnGLError("ERROR: Could not use the shader program");

	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);
	ExitOnGLError("ERROR: Could not set the shader uniforms");

	glBindVertexArray(BufferIds[0]);
	ExitOnGLError("ERROR: Could not bind the VAO for drawing purposes");

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)0);
	ExitOnGLError("ERROR: Could not draw the cube");

	glBindVertexArray(0);
	glUseProgram(0);
}*/

void Shape::createShader() {
	GLenum ErrorCheckValue = glGetError();
	//ShaderIds[0] = glCreateProgram();
	ProgramId = glCreateProgram();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);


	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	//glUseProgram(ProgramId);

	mvp_location = glGetUniformLocation(ProgramId, "mvp");
}

/*void Shape::createTriangle() {
	

	GLfloat VERTICES[] = 
	 { -.5f, 0,   .5f, 1,		  0, 0, 1, 1 ,
	    .5f, 0,   .5f, 1,		  1, 0, 0, 1 ,
	    .5f, 0,  -.5f, 1,		  0, 1, 0, 1 ,
	   -.5f, 0,  -.5f, 1,		  0, 1, 1, 1 ,
	      0, 1,     0, 1 ,	      1, 1, 0, 1  };

	/*GLfloat VERTICES[] =
	{  -.5f,  0,   .5f, 1,
		.5f,  0,   .5f, 1,
		.5f,  0,  -.5f, 1,
		-.5f, 0,  -.5f, 1,
		   0, 1,     0, 1 };

	GLfloat COLORS[] = 
	{	0, 0, 1, 1,
		1, 0, 0, 1,
		0, 1, 0, 1,
		0, 1, 1, 1,
		1, 1, 0, 1}; 
		
	const GLuint INDICES[18] =
	{
		0,3,1,
		1,3,2,
		0,1,4,
		1,2,4,
		2,3,4,
		3,0,4
	};

	//createShader();


	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	glGenBuffers(1, &vboId);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8*sizeof(float), (GLvoid*)(sizeof(float)*4));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &eboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);
	ExitOnGLError("ERROR: Could not bind the IBO to the VAO");

	glBindVertexArray(0);
}*/

/*void Shape::drawTriangle() {
	float CubeAngle;
	

	//glLoadIdentity();
	
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glViewport(0, 0, 1024, 768);
	//ProjectionMatrix = glm::projecctio

	//getLookAt(Angle);

	
	glm::mat4  ProjectionMatrix = glm::perspective(glm::radians(70.0f), (float)1024 / (float)768, 0.1f, 100.0f);
	glm::mat4  ViewMatrix = glm::lookAt(cam->getVec3(), cam->getVec3() + cam->getLookAt(), glm::vec3(0, 1, 0));
	glm::mat4  ModelMatrix = glm::mat4(1.0f);
	//glm::mat4 viewMatrix = glm::look

	


	//YYY = glm::sin(Angle);
	//ZZZ = glm::cos(Angle);

	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(posX, -1, 0));
	ModelMatrix = glm::rotate(ModelMatrix, 0.5f, glm::vec3(0, 1, 0));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1, 1, 1));


	//CubeRotation += 45.0f * ((float)(Now - LastTime) / CLOCKS_PER_SEC);
	//CubeAngle = DegreesToRadians(CubeRotation);
	

	glm::mat4 mvp = ProjectionMatrix*ViewMatrix*  ModelMatrix;


	//glPopMatrix();
	//ModelMatrix = IDENTITY_MATRIX;

	//ScaleMatrix(&ModelMatrix, 0.5, 0.5, 0.5);
	//RotateAboutY(&ModelMatrix, CubeAngle);
	//RotateAboutX(&ModelMatrix, CubeAngle/10);




	glUseProgram(ProgramId);
	ExitOnGLError("ERROR: Could not use the shader program");

	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);
	//glUniformMatrix4fv(ModelMatrixUniformLocation, 1, GL_FALSE, ModelMatrix.m);
	//glUniformMatrix4fv(ViewMatrixUniformLocation, 1, GL_FALSE, ViewMatrix.m);
	ExitOnGLError("ERROR: Could not set the shader uniforms");

	glBindVertexArray(vaoId);
	ExitOnGLError("ERROR: Could not bind the VAO for drawing purposes");

	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (GLvoid*)0);
	ExitOnGLError("ERROR: Could not draw the cube");

	glBindVertexArray(0);
	glUseProgram(0);
}*/



void Shape::serveTime() {
	clock_t Now = clock();

	if (LastTime == 0)
		LastTime = Now;
	
	Angle = 10 * ((float)(Now - LastTime) / CLOCKS_PER_SEC);

	float przes = 10 * ((float)(Now - LastTime) / CLOCKS_PER_SEC);
/*
	//std::cout << AngleHor << std::endl;
	//std::cout << "X: "<<cameraPosX << std::endl;
	//std::cout << "Z: " << cameraPosZ << std::endl;

	if (isPressingA) {
		cam->setZ(cam->getZ() + przes * glm::sin(glm::radians(AngleHor - 90)));
		cam->setX(cam->getX() + przes * glm::cos(glm::radians(AngleHor - 90)));
	}
	if (isPressingD) {
		cam->setZ(cam->getZ() + przes * glm::sin(glm::radians(AngleHor + 90)));
		cam->setX(cam->getX() + przes * glm::cos(glm::radians(AngleHor + 90)));
	}
	if (isPressingW) {
		cam->setZ(cam->getZ() + przes * glm::sin(glm::radians(AngleHor)));
		cam->setX(cam->getX() + przes * glm::cos(glm::radians(AngleHor)));
	}
	if (isPressingS) {
		//cameraPosZ += przes;
		cam->setZ(cam->getZ() - przes * glm::sin(glm::radians(AngleHor)));
		cam->setX(cam->getX() - przes * glm::cos(glm::radians(AngleHor)));
	}

	LastTime = Now;*/
}

float Shape::getZ() {
	return posZ;
}
void Shape::setZ(float Z) {
	posZ = Z;
}
float Shape::getY() {
	return posY;
}