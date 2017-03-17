#include "../headers/Walec.h"

Walec::Walec(Camera * cam, Light* light, bool * stop) {
	posX = 5;
	posY = 3.5f;
	posZ = 6;
	this->cam = cam;
	this->light = light;
	this->stopp = stop;
	scaleY = 2;
	scaleX = 0.25;
	scaleZ = 0.25;
	up = 0;
	running = false;
	multi = 3;
	textureName = "res/bruk.png";
}
Walec::Walec(Camera * cam, Light* light, float X, float Y, float Z, float sX, float sY, float sZ) {
	posX = X;
	posY = Y;
	posZ = Z;
	scaleX = sX;
	scaleY = sY;
	scaleZ = sZ;
	this->cam = cam;
	this->light = light;
	multi = 3;
	textureName = "res/bruk.png";
}

void Walec::addColors() {
	int pointer = 0;
	int q = 1;
	int w = 0;
	int e = 0;

	for (int i = 0; i < VERTEX_COUNT; ++i) {

		for (int j = 0; j < 4; ++j) {
			COLORS[pointer] = q;
			COLORS[pointer + 1] = w;
			COLORS[pointer + 2] = e;
			COLORS[pointer + 3] = q;
			COLORS[pointer + 4] = w;
			COLORS[pointer + 5] = e;
			COLORS[pointer + 6] = q;
			COLORS[pointer + 7] = w;
			COLORS[pointer + 8] = e;

			pointer += 9;
		}
		
		if (q == 1) {
			q = 0;
			w = 1;
			e = 0;
		}
		else if (w == 1) {
			q = 0;
			w = 0;
			e = 1;
		}
		else if (e == 1) {
			q = 1;
			w = 0;
			e = 0;
		}
	}
}


void Walec::create() {

	float step = 360 / VERTEX_COUNT;
	int pointer = 0;
	int pointTex = 0;

	float X[VERTEX_COUNT];
	float Z[VERTEX_COUNT];



	for (float angle = 0; angle < 360; angle += step) {
		float x = sin(angle * (float)(PI / 180));
		float z = cos(angle * (float)(PI / 180));

		X[pointer] = x;
		Z[pointer] = z;

		pointer++;
		
	}

	pointer = 0;
	
	
	for (int i = 0; i < VERTEX_COUNT; ++i) {
		VERTICES[pointer] = X[i];
		VERTICES[pointer+1] = 0;
		VERTICES[pointer+2] = Z[i];
		VERTICES[pointer+3] = 0;
		VERTICES[pointer+4] = 0;
		VERTICES[pointer+5] = 0;
		VERTICES[pointer + 6] = X[(i + 1) % VERTEX_COUNT];
		VERTICES[pointer + 7] = 0;
		VERTICES[pointer + 8] = Z[(i + 1) % VERTEX_COUNT];
		

		

		NORMALS[pointer] = 0;
		NORMALS[pointer+1] = 1;
		NORMALS[pointer+2] = 0;
		NORMALS[pointer+3] = 0;
		NORMALS[pointer+4] = 1;
		NORMALS[pointer+5] = 0;
		NORMALS[pointer+6] = 0;
		NORMALS[pointer+7] = 1;
		NORMALS[pointer+8] = 0;

		TEXTURE_COORDS[pointTex] = X[i] / 2 + 0.5;
		TEXTURE_COORDS[pointTex+1] = Z[i] / 2 + 0.5;
		TEXTURE_COORDS[pointTex+2] = 0.5;
		TEXTURE_COORDS[pointTex + 3] = 0.5;
		TEXTURE_COORDS[pointTex+4] = X[(i + 1) % VERTEX_COUNT] / 2 + 0.5;
		TEXTURE_COORDS[pointTex + 5] = Z[(i + 1) % VERTEX_COUNT] / 2 + 0.5;

		pointTex += 6;
		pointer += 9;

		VERTICES[pointer] = X[i];
		VERTICES[pointer + 1] = 0;
		VERTICES[pointer + 2] = Z[i];
		VERTICES[pointer + 3] = X[i];
		VERTICES[pointer + 4] = -1;
		VERTICES[pointer + 5] = Z[i];
		VERTICES[pointer + 6] = X[(i + 1) % VERTEX_COUNT];
		VERTICES[pointer + 7] = -1;
		VERTICES[pointer + 8] = Z[(i + 1) % VERTEX_COUNT];


		NORMALS[pointer] = X[i];//tu
		NORMALS[pointer + 1] = 0;
		NORMALS[pointer + 2] = Z[i];
		NORMALS[pointer + 3] = X[i];
		NORMALS[pointer + 4] = 0;
		NORMALS[pointer + 5] = Z[i];
		NORMALS[pointer + 6] = X[(i + 1) % VERTEX_COUNT];
		NORMALS[pointer + 7] = 0;
		NORMALS[pointer + 8] = Z[(i + 1) % VERTEX_COUNT];


		TEXTURE_COORDS[pointTex] = float(i) / VERTEX_COUNT;
		TEXTURE_COORDS[pointTex + 1] = 1;
		TEXTURE_COORDS[pointTex + 2] = float(i) / VERTEX_COUNT;
		TEXTURE_COORDS[pointTex + 3] = 0;
		TEXTURE_COORDS[pointTex + 4] = float(i+1) / VERTEX_COUNT;
		TEXTURE_COORDS[pointTex + 5] = 0;

		pointTex += 6;
		pointer += 9;

		VERTICES[pointer] = X[(i + 1) % VERTEX_COUNT];
		VERTICES[pointer + 1] = -1;
		VERTICES[pointer + 2] = Z[(i + 1) % VERTEX_COUNT];
		VERTICES[pointer + 3] = X[(i + 1) % VERTEX_COUNT];
		VERTICES[pointer + 4] = 0;
		VERTICES[pointer + 5] = Z[(i + 1) % VERTEX_COUNT];
		VERTICES[pointer + 6] = X[i];
		VERTICES[pointer + 7] = 0;
		VERTICES[pointer + 8] = Z[i];


		NORMALS[pointer] = X[(i + 1) % VERTEX_COUNT];;	//tu
		NORMALS[pointer + 1] = 0;
		NORMALS[pointer + 2] = Z[(i + 1) % VERTEX_COUNT];;
		NORMALS[pointer + 3] = X[(i + 1) % VERTEX_COUNT];;
		NORMALS[pointer + 4] = 0;
		NORMALS[pointer + 5] = Z[(i + 1) % VERTEX_COUNT];;
		NORMALS[pointer + 6] = X[i];
		NORMALS[pointer + 7] = 0;
		NORMALS[pointer + 8] = Z[i];


		TEXTURE_COORDS[pointTex] = float(i+1) / VERTEX_COUNT;
		TEXTURE_COORDS[pointTex + 1] = 0;
		TEXTURE_COORDS[pointTex + 2] = float(i+1) / VERTEX_COUNT;
		TEXTURE_COORDS[pointTex + 3] = 1;
		TEXTURE_COORDS[pointTex + 4] = float(i) / VERTEX_COUNT;
		TEXTURE_COORDS[pointTex + 5] = 1;


		pointTex += 6;
		pointer += 9;
		
		VERTICES[pointer] = X[i];
		VERTICES[pointer + 1] = -1;
		VERTICES[pointer + 2] = Z[i];
		VERTICES[pointer + 3] = 0;
		VERTICES[pointer + 4] = -1;
		VERTICES[pointer + 5] = 0;
		VERTICES[pointer + 6] = X[(i + 1) % VERTEX_COUNT];
		VERTICES[pointer + 7] = -1;
		VERTICES[pointer + 8] = Z[(i + 1) % VERTEX_COUNT];


		NORMALS[pointer] = 0;
		NORMALS[pointer + 1] = -1;
		NORMALS[pointer + 2] = 0;
		NORMALS[pointer + 3] = 0;
		NORMALS[pointer + 4] = -1;
		NORMALS[pointer + 5] = 0;
		NORMALS[pointer + 6] = 0;
		NORMALS[pointer + 7] = -1;
		NORMALS[pointer + 8] = 0;


		TEXTURE_COORDS[pointTex] = X[i] / 2 + 0.5;
		TEXTURE_COORDS[pointTex + 1] = Z[i] / 2 + 0.5;
		TEXTURE_COORDS[pointTex + 2] = 0.5;
		TEXTURE_COORDS[pointTex + 3] = 0.5;
		TEXTURE_COORDS[pointTex + 4] = X[(i + 1) % VERTEX_COUNT] / 2 + 0.5;
		TEXTURE_COORDS[pointTex + 5] = Z[(i + 1) % VERTEX_COUNT] / 2 + 0.5;


		
		pointTex += 6;
		pointer += 9;
	}

	addColors();


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

void Walec::draw() {
	ViewMatrix = glm::lookAt(cam->getVec3(), cam->getVec3() + cam->getLookAt(), glm::vec3(0, 1, 0));
	ModelMatrix = glm::mat4(1.0f);


	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(posX, posY, posZ));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(scaleX, scaleY, scaleZ));


	glUseProgram(ProgramId);
	loadUniformLocations();

	glBindVertexArray(vaoId);

	glDrawArrays(GL_TRIANGLES, 0, _countof(VERTICES)/3);

	glBindVertexArray(0);
	glUseProgram(0);
}
void Walec::serveTime() {
	clock_t Now = clock();

	if (LastTime == 0)
		LastTime = Now;

	if (running) {
		float przes = ((float)(Now - LastTime) / CLOCKS_PER_SEC);
		przes *= PREDKOSC;

		if (!up) {
			posY -= przes;
			if (posY < 2.4) up = 1;
		}
		else {
			if(posY <3.0)
				posY += przes;
			else if (posY <= 3.1)
				posY += przes / 2;
			else if (posY <= 3.2)
				posY += przes / 4;
			else if (posY < 3.3)
				posY += przes / 8;
			else if (posY <= 3.4)
				posY += przes / 16;
			else if (posY < 3.5)
				posY += przes / 32;
			
			else if (posY >= 3.5) {
				up = 0; 
				*stopp = false;
				stop();
			}
		}
	}
	
	LastTime = Now;
}
void Walec::start() {
	running = true;
}
void Walec::stop() {
	running = false;
}
float Walec::getScaleY() {
	return scaleY;
}

void Walec::move(int dir) {
	clock_t Now = clock();

	walec = NULL;
	if (LastTime == 0)
		LastTime = Now;

	//Angle += 10 * ((float)(Now - LastTime) / CLOCKS_PER_SEC);

	float przes = ((float)(Now - LastTime) / CLOCKS_PER_SEC);
	przes *= PREDKOSC;

	if (dir == 3)
		posZ += przes;
	else if (dir == 2)
		posZ -= przes;
	else if (dir == 0)
		posY += przes;
	else if (dir == 1)
		posY -= przes;

	LastTime = Now;
}
void Walec::doNotMove() {
	clock_t Now = clock();

	if (LastTime == 0)
		LastTime = Now;

	//	float posy = posY;

	if (walec != NULL) {

		if (walec->getY() <= 2.7) {
			scaleY -= 0.02*PREDKOSC;
			posY -= 0.02*PREDKOSC;
			scaleZ += 0.012*PREDKOSC;
			scaleX += 0.012*PREDKOSC;

		}

		if (walec->getY() <= 2.4) {
			walec = NULL;
			scaleY = 0.14;
			posY = 0.4;
			scaleZ = 0.516;
			scaleX = 0.516;
		}
	}

	LastTime = Now;
}


void Walec::setScaleYOf(Shape * walec) {
	this->walec = walec;
}