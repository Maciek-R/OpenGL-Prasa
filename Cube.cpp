#include "Cube.h"

Cube::Cube(Camera* cam) {
	posX = 5;
	posY = -1.5;
	posZ = 0;
	this->cam = cam;
}

const GLchar* VertexShaderCube =
{
	"#version 400\n"\

	"layout(location=0) in vec3 in_Position;\n"\
	"layout(location=1) in vec3 normal;\n"\
	"layout(location=2) in vec3 in_Color;\n"\
	"layout(location=3) in vec2 texCoord;\n"\
	"out vec4 ex_Color;\n"\
	"out vec2 TexCoord;\n"\
	"out vec3 Normal;\n"
	"out vec3 FragPos;\n"
	"uniform mat4 ModelMatrix;\n"
	"uniform mat4 ViewMatrix;\n"
	"uniform mat4 ProjectionMatrix;\n"
	/*"uniform mat4 mvp;\n"\*/
	"void main(void)\n"\
	"{\n"\
	//"gl_Position = in_Position;\n"
	//"  gl_Position = (ProjectionMatrix * ViewMatrix * ModelMatrix) * in_Position;\n"
	//"gl_Position = ViewMatrix * ModelMatrix * in_Position;\n"
	/*"gl_Position = mvp * in_Position;\n"\*/
	"gl_Position = ProjectionMatrix*ViewMatrix*ModelMatrix * vec4(in_Position, 1.0f);\n"\
	"  ex_Color = vec4(in_Color, 1.0);\n"\
	"TexCoord = texCoord;\n"\
	"mat3 normalMatrix = mat3(ModelMatrix);\n"
	"normalMatrix = inverse(normalMatrix);\n"
	"normalMatrix = transpose(normalMatrix);\n"
	"Normal = normalize(normalMatrix*normal);\n"
	"FragPos = vec3(ModelMatrix*vec4(in_Position, 1.0));\n"
	/*"  ex_Color = vec4(1.0, 0,0, 1.0);\n"\*/
	"}\n"
};

const GLchar* FragmentShaderCube =
{
	"#version 400\n"\

	"in vec4 ex_Color;\n"\
	"in vec2 TexCoord;\n"\
	"out vec4 out_Color;\n"\
	"in vec3 Normal;\n"
	"in vec3 FragPos;\n"

	"uniform sampler2D Texture0;\n"\
	"uniform vec3 lightPos; \n"

	"void main(void)\n"\
	"{\n"\

	"vec3 norm = normalize(Normal);\n"
	"vec3 lightDir = normalize(lightPos - FragPos);\n"
	"float diff = max(dot(norm, lightDir), 0.0);\n"
	"vec3 diffuse = diff * vec3(1.0f, 1.0f, 1.0f);\n"

	/*"  out_Color = ex_Color;\n"\*/
	"  out_Color = texture(Texture0, TexCoord)*vec4((diffuse + vec3(0.25f, 0.25f, 0.25f)), 1.0);\n"\
	"}\n"
};

void Cube::createShader() {
	GLenum ErrorCheckValue = glGetError();
	//ShaderIds[0] = glCreateProgram();
	ProgramId = glCreateProgram();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShaderCube, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShaderCube, NULL);
	glCompileShader(FragmentShaderId);


	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	//glUseProgram(ProgramId);

	//mvp_location = glGetUniformLocation(ProgramId, "mvp");
	Model_Location = glGetUniformLocation(ProgramId, "ModelMatrix");
	View_Location = glGetUniformLocation(ProgramId, "ViewMatrix");
	Projection_Location = glGetUniformLocation(ProgramId, "ProjectionMatrix");
	lightPosLoc = glGetUniformLocation(ProgramId, "lightPos");
}
static GLuint LoadMipmapTexture(GLuint texId, const char* fname)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	//if (image == nullptr)
	//throw exception("Failed to load texture file");

	GLuint texture;
	glGenTextures(1, &texture);

	glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

void Cube::createCube()
{
	
	/*GLfloat VERTICES[] =
	{
		 -.5f, -.5f,  .5f,		0, 0, 1,
		 -.5f,  .5f,  .5f,		1, 0, 0,
		 .5f,  .5f,  .5f,		0, 1, 0,
		 .5f, -.5f,  .5f,		1, 1, 0,
		 -.5f, -.5f, -.5f,		1, 1, 1,
		 -.5f,  .5f, -.5f,		1, 0, 0,
		 .5f,  .5f, -.5f,		1, 0, 1,
		 .5f, -.5f, -.5f,		0, 0, 1 
	};*/
	GLfloat VERTICES[] = {
	-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,		1.0f, 0, 0,			0.0f, 0.5f,
	0.5f, -0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,		1.0f, 0, 0,			0.33f, 0.5f,
	0.5f,  0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,		1.0f, 0, 0,			0.33f, 0.0f,
	0.5f,  0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,		1.0f, 0, 0,			0.33f, 0.0f,
	-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,		1.0f, 0, 0,			0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,		1.0f, 0, 0,			0.0f, 0.5f,

	-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,		0, 1.0f, 0,			0.33f, 0.5f,
	0.5f, -0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,		0, 1.0f, 0,			0.66f, 0.5f,
	0.5f,  0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,		0, 1.0f, 0,			0.66f, 0.0f,
	0.5f,  0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,		0, 1.0f, 0,			0.66f, 0.0f,
	-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,		0, 1.0f, 0,			0.33f, 0.0f,
	-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,		0, 1.0f, 0,			0.33f, 0.5f,

	-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,		1.0f, 1.0f, 0,			0.66f, 0.0f,
	-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,		1.0f, 1.0f, 0,			1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,		1.0f, 1.0f, 0,			1.0f, 0.5f,
	-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,		1.0f, 1.0f, 0,			1.0f, 0.5f,
	-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,		1.0f, 1.0f, 0,			0.66f, 0.5f,
	-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,		1.0f, 1.0f, 0,			0.66f, 0.0f,

	0.5f,  0.5f,  0.5f,		 1.0f,  0.0f,  0.0f,		0, 1.0f, 1.0f,			0.0f, 0.5f,
	0.5f,  0.5f, -0.5f,		 1.0f,  0.0f,  0.0f,		0, 1.0f, 1.0f,			0.33f, 0.5f,
	0.5f, -0.5f, -0.5f,		 1.0f,  0.0f,  0.0f,		0, 1.0f, 1.0f,			0.33f, 1.0f,
	0.5f, -0.5f, -0.5f,		 1.0f,  0.0f,  0.0f,		0, 1.0f, 1.0f,			0.33f, 1.0f,
	0.5f, -0.5f,  0.5f,		 1.0f,  0.0f,  0.0f,		0, 1.0f, 1.0f,			0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,		 1.0f,  0.0f,  0.0f,		0, 1.0f, 1.0f,			0.0f, 0.5f,

	-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,		0, 0, 1.0f,			0.33f, 0.5f,
	0.5f, -0.5f, -0.5f,		 0.0f, -1.0f,  0.0f,		0, 0, 1.0f,			0.66f, 0.5f,
	0.5f, -0.5f,  0.5f,		 0.0f, -1.0f,  0.0f,		0, 0, 1.0f,			0.66f, 1.0f,
	0.5f, -0.5f,  0.5f,		 0.0f, -1.0f,  0.0f,		0, 0, 1.0f,			0.66f, 1.0f,
	-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,		0, 0, 1.0f,			0.33f, 1.0f,
	-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,		0, 0, 1.0f,			0.33f, 0.5f,

	-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,		1.0f, 0, 1.0f,			0.66f, 0.5f,
	0.5f,  0.5f, -0.5f,		 0.0f,  1.0f,  0.0f,		1.0f, 0, 1.0f,			1.0f, 0.5f,
	0.5f,  0.5f,  0.5f,		 0.0f,  1.0f,  0.0f,		1.0f, 0, 1.0f,			1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,		 0.0f,  1.0f,  0.0f,		1.0f, 0, 1.0f,			1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,		1.0f, 0, 1.0f,			0.66f, 1.0f,
	-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,		1.0f, 0, 1.0f,			0.66f, 0.5f
	};



/*	GLuint INDICES[36] =
	{
		0,2,1,  0,3,2,
		4,3,0,  4,7,3,
		4,1,5,  4,0,1,
		3,6,2,  3,7,6,
		1,6,5,  1,2,6,
		7,5,6,  7,4,5
	};*/


	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (GLvoid*)(sizeof(float)*3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (GLvoid*)(sizeof(float) * 6));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (GLvoid*)(sizeof(float) * 9));

	/*glGenBuffers(1, &eboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);*/

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

	texture0 = LoadMipmapTexture(GL_TEXTURE0, "res/all.png");
}

void Cube::drawCube() {
	glm::mat4  ProjectionMatrix, ViewMatrix, ModelMatrix;

	ProjectionMatrix = glm::perspective(glm::radians(70.0f), (float)1024 / (float)768, 0.1f, 100.0f);

	//if(cam->FIRST_PERSON_MODE)
		ViewMatrix = glm::lookAt(cam->getVec3(), cam->getVec3() + cam->getLookAt(), glm::vec3(0, 1, 0));
	//else
	//	ViewMatrix = glm::lookAt(cam->getVec3(), glm::vec3(5,0,5), glm::vec3(0, 1, 0));
	ModelMatrix = glm::mat4(1.0f);
	//glm::mat4 viewMatrix = glm::look

	//Angle += 5 * ((float)(Now - LastTime) / CLOCKS_PER_SEC);


	//YYY = glm::sin(Angle);
	//ZZZ = 3 * glm::cos(Angle);


	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(posX, posY, posZ));
	ModelMatrix = glm::rotate(ModelMatrix, Angle/5, glm::vec3(0, 1, 0));
	//ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.5f, 0.5, 0.5));


	//glm::mat4 mvp = ProjectionMatrix*ViewMatrix*ModelMatrix;




	glUseProgram(ProgramId);

	//glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(Model_Location, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(View_Location, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix4fv(Projection_Location, 1, GL_FALSE, &ProjectionMatrix[0][0]);
	//glUniform3f(lightPosLoc, cam->getX(), cam->getY(), cam->getZ());
	glUniform3f(lightPosLoc, 0, 0, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(ProgramId, "Texture0"), 0);

	glBindVertexArray(vaoId);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glUseProgram(0);
}