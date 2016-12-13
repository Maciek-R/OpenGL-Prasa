#include "Terrain.h"


const GLchar* VertexShaderT =
{
	"#version 400\n"\

	"layout(location=0) in vec3 in_Position;\n"\
	"layout(location=1) in vec3 in_Color;\n"\
	"layout(location = 2) in vec2 texCoord;\n"\
	"out vec3 ex_Color;\n"\
	"out vec2 TexCoord;\n"\

	"uniform mat4 mvp;\n"\
	"void main(void)\n"\
	"{\n"\

	"gl_Position = mvp * vec4(in_Position, 1.0);\n"\
	"  ex_Color = in_Color;\n"\
	"TexCoord = texCoord;\n"\
	"}\n"
};

const GLchar* FragmentShaderT =
{
	"#version 400\n"\

	"in vec3 ex_Color;\n"\
	"in vec2 TexCoord;\n"\
	"out vec4 out_Color;\n"\

	"uniform sampler2D Texture0;\n"\

	"void main(void)\n"\
	"{\n"\
	/*"  out_Color = vec4(ex_Color, 1.0);\n"\*/
	"  out_Color = texture(Texture0, TexCoord*5);\n"\
	"}\n"
};

Terrain::Terrain() {

}
Terrain::Terrain(Camera *cam) {
	this->cam = cam;
}


GLuint Terrain::LoadMipmapTexture(GLuint texId, const char* fname)
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

void Terrain::createTerrain() {

	
	/*const int VERTEX_COUNT = 256;
	int SIZE = 100;
	
	GLfloat VERTICES[VERTEX_COUNT*VERTEX_COUNT * 3];
	GLfloat COLORS[VERTEX_COUNT*VERTEX_COUNT * 3];
	GLuint INDICES[6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1)];
	*/
	int counter = 0;
	int c = 0;

	for (int i = 0; i < VERTEX_COUNT; ++i) {
		for (int j = 0; j < VERTEX_COUNT; ++j) {
			GLfloat x = (float(j) / float(VERTEX_COUNT - 1)) * SIZE;
			GLfloat y = -20;
			GLfloat z = (float(i) / float(VERTEX_COUNT - 1)) * SIZE;

			VERTICES[counter] = x;
			VERTICES[counter+1] = y;
			VERTICES[counter+2] = z;
			
			COLORS[counter] = 1;
			COLORS[counter+1] = 0;
			COLORS[counter+2] = 0;

			NORMALS[counter] = 0;
			NORMALS[counter + 1] = 1.0f;
			NORMALS[counter + 2] = 0;

			TEXTURE_COORDS[c] = (float)j / ((float)VERTEX_COUNT - 1);
			TEXTURE_COORDS[c + 1] = (float)i / ((float)VERTEX_COUNT - 1);

			

			counter += 3;
			c += 2;
		}
	}

	counter = 0;
	for (int i = 0; i < VERTEX_COUNT - 1; ++i) {
		for (int j = 0; j < VERTEX_COUNT - 1; ++j) {
			int topLeft = i*VERTEX_COUNT + j;
			int topRight = i*VERTEX_COUNT + j+1;
			int bottomLeft = (i+1)*VERTEX_COUNT + j;
			int bottomRight = (i + 1)*VERTEX_COUNT + j+1;
			INDICES[counter++] = topLeft;
			INDICES[counter++] = bottomLeft;
			INDICES[counter++] = topRight;
			INDICES[counter++] = topRight;
			INDICES[counter++] = bottomLeft;
			INDICES[counter++] = bottomRight;
			
		}
	}
	
	/*GLuint INDICES[18] =
	{
		0,3,1,
		1,3,2,
		0,1,4,
		1,2,4,
		2,3,4,
		3,0,4
	};
	GLfloat VERTICES[] =
	{ -.5f,  0,   .5f,
		.5f,  0,   .5f,
		.5f,  0,  -.5f,
		-.5f, 0,  -.5f,
		0, 1,     0 };

	GLfloat COLORS[] =
	{ 0, 0, 1,
		1, 0, 0,
		0, 1, 0,
		0, 1, 1,
		1, 1, 0 };
	*/
	

	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	
	glGenBuffers(1, &colorId);
	glBindBuffer(GL_ARRAY_BUFFER, colorId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(COLORS), COLORS, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

	glGenBuffers(1, &eboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);

	glGenBuffers(1, &texId);
	glBindBuffer(GL_ARRAY_BUFFER, texId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TEXTURE_COORDS), TEXTURE_COORDS, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,  2 * sizeof(float), (GLvoid*)0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	texture0 = LoadMipmapTexture(GL_TEXTURE0, "bruk.png");

}

void Terrain::drawTerrain() {
	glm::mat4  ProjectionMatrix, ViewMatrix, ModelMatrix;

	ProjectionMatrix = glm::perspective(glm::radians(70.0f), (float)1024 / (float)768, 0.1f, 500.0f);
	if(cam->FIRST_PERSON_MODE)
		ViewMatrix = glm::lookAt(cam->getVec3(), cam->getVec3() + cam->getLookAt(), glm::vec3(0, 1, 0));
	else
		ViewMatrix = glm::lookAt(cam->getVec3(), glm::vec3(5,0,5), glm::vec3(0, 1, 0));
	ModelMatrix = glm::mat4(1.0f);




	//YYY = glm::sin(Angle);
	//ZZZ = glm::cos(Angle);

	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0 - cam->getX(), 0 - cam->getY(), 0 - cam->getZ()));
	//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(XXX - 1 - cameraPosX, YYY - cameraPosY, 0 - cameraPosZ));
	//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(XXX - 1 - cameraPosX, -1 - cameraPosY, 0 - cameraPosZ));
	//ModelMatrix = glm::rotate(ModelMatrix, Angle / 10, glm::vec3(0, 1, 0));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1, 1, 1));




	glm::mat4 mvp = ProjectionMatrix*ViewMatrix*  ModelMatrix;
	



	glUseProgram(ProgramId);
	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(ProgramId, "Texture0"), 0);

	glBindVertexArray(vaoId);

	glDrawElements(GL_TRIANGLES, 6*VERTEX_COUNT*VERTEX_COUNT, GL_UNSIGNED_INT, (GLvoid*)0);

	glBindVertexArray(0);
	glUseProgram(0);
}

void Terrain::createShader() {
	GLenum ErrorCheckValue = glGetError();
	//ShaderIds[0] = glCreateProgram();
	ProgramId = glCreateProgram();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShaderT, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShaderT, NULL);
	glCompileShader(FragmentShaderId);


	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	//glUseProgram(ProgramId);

	mvp_location = glGetUniformLocation(ProgramId, "mvp");
}







void Terrain::serveTime() {
	clock_t Now = clock();

	if (LastTime == 0)
		LastTime = Now;

	//float przes = 10 * ((float)(Now - LastTime) / CLOCKS_PER_SEC);


/*	if (isPressingA) {
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
		cam->setZ(cam->getZ() - przes * glm::sin(glm::radians(AngleHor)));
		cam->setX(cam->getX() - przes * glm::cos(glm::radians(AngleHor)));
	}*/

	LastTime = Now;
}