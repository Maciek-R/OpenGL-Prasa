#include "../headers/Cube.h"

Cube::Cube(Camera* cam, Light* light) {
	init(cam, light);
	
	
}
Cube::Cube(Camera* cam, Light* light, float X, float Y, float Z) {
	init(cam, light);
	posX = X;
	posY = Y;
	posZ = Z;
	
}
Cube::Cube(Camera* cam, Light* light, float X, float Y, float Z, float scaleX, float scaleY, float scaleZ) {
	init(cam, light);
	posX = X;
	posY = Y;
	posZ = Z;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
}

void Cube::init(Camera * cam, Light * light) {
	posX = 3;
	posY = 0.5f;
	posZ = 1;
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	textureName = "res/prasa.png";
	this->cam = cam;
	this->light = light;
	walec = NULL;
	RotateZ = 0;
	multi = 1;
}


void Cube::create()
{
	GLfloat VERTICES[] = {
	-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,		1.0f, 0, 0,			0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,		1.0f, 0, 0,			1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,		1.0f, 0, 0,			1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,		1.0f, 0, 0,			1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,		1.0f, 0, 0,			0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,		1.0f, 0, 0,			0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,		0, 1.0f, 0,			0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,		0, 1.0f, 0,			1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,		0, 1.0f, 0,			1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,		0, 1.0f, 0,			1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,		0, 1.0f, 0,			0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,		0, 1.0f, 0,			0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,		1.0f, 1.0f, 0,			0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,		1.0f, 1.0f, 0,			1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,		1.0f, 1.0f, 0,			1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,		1.0f, 1.0f, 0,			1.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,		1.0f, 1.0f, 0,			0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,		1.0f, 1.0f, 0,			0.0f, 0.0f,

	0.5f,  0.5f,  0.5f,		 1.0f,  0.0f,  0.0f,		0, 1.0f, 1.0f,			0.0f, 0.0f,
	0.5f,  0.5f, -0.5f,		 1.0f,  0.0f,  0.0f,		0, 1.0f, 1.0f,			1.0f, 0.0f,
	0.5f, -0.5f, -0.5f,		 1.0f,  0.0f,  0.0f,		0, 1.0f, 1.0f,			1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		 1.0f,  0.0f,  0.0f,		0, 1.0f, 1.0f,			1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,		 1.0f,  0.0f,  0.0f,		0, 1.0f, 1.0f,			0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,		 1.0f,  0.0f,  0.0f,		0, 1.0f, 1.0f,			0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,		0, 0, 1.0f,			0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,		 0.0f, -1.0f,  0.0f,		0, 0, 1.0f,			1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,		 0.0f, -1.0f,  0.0f,		0, 0, 1.0f,			1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,		 0.0f, -1.0f,  0.0f,		0, 0, 1.0f,			1.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,		0, 0, 1.0f,			0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,		0, 0, 1.0f,			0.0f, 0.0f,

	-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,		1.0f, 0, 1.0f,			0.0f, 0.0f,
	0.5f,  0.5f, -0.5f,		 0.0f,  1.0f,  0.0f,		1.0f, 0, 1.0f,			1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,		 0.0f,  1.0f,  0.0f,		1.0f, 0, 1.0f,			1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,		 0.0f,  1.0f,  0.0f,		1.0f, 0, 1.0f,			1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,		1.0f, 0, 1.0f,			0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,		1.0f, 0, 1.0f,			0.0f, 0.0f,
	};

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

	texture0 = LoadMipmapTexture(GL_TEXTURE0, textureName);
}

void Cube::draw() {	
	ViewMatrix = glm::lookAt(cam->getVec3(), cam->getVec3() + cam->getLookAt(), glm::vec3(0, 1, 0));
	ModelMatrix = glm::mat4(1.0f);

	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(posX, posY, posZ));
	ModelMatrix = glm::rotate(ModelMatrix, RotateZ * (float)(PI / 180), glm::vec3(0, 0, 1));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(scaleX, scaleY, scaleZ));

	glUseProgram(ProgramId);
	loadUniformLocations();

	glBindVertexArray(vaoId);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Cube::move(int dir) {
	clock_t Now = clock();

	walec = NULL;
	if (LastTime == 0)
		LastTime = Now;

	//Angle += 10 * ((float)(Now - LastTime) / CLOCKS_PER_SEC);

	float przes =   ((float)(Now - LastTime) / CLOCKS_PER_SEC);
	przes *= PREDKOSC;

	if(dir==3)
		posZ += przes;
	else if(dir==2)
		posZ -= przes;
	else if (dir == 0)
		posY += przes;
	else if (dir == 1)
		posY -= przes;

	LastTime = Now;
}
void Cube::doNotMove() {
	clock_t Now = clock();

	if (LastTime == 0)
		LastTime = Now;

//	float posy = posY;

	if (walec != NULL) {

		if(walec->getY() <= 2.7){
			scaleY -= 0.02*PREDKOSC;
			posY -= 0.01*PREDKOSC;
			scaleZ += 0.018*PREDKOSC;
			scaleX += 0.018*PREDKOSC;
		}

		if(walec->getY() <= 2.4){
			walec = NULL;
			scaleY = 0.12;
			
			posY = 0.31;
			scaleZ = 0.842;
			scaleX = 0.842;
		}
	}

	LastTime = Now;
}


void Cube::setScaleYOf(Shape * walec) {
	this->walec = walec;
}
void Cube::setRotateZ(float Z) {
	RotateZ = Z;
}