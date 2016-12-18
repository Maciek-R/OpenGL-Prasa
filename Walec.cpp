#include "Walec.h"

Walec::Walec(Camera * cam) {
	posX = 5;
	posY = 2.0f;
	posZ = 6;
	this->cam = cam;
	scaleY = 0.5;
	up = 0;
	running = false;
}

const GLchar* VertexShaderWalec =
{
	"#version 400\n"\

	"layout(location=0) in vec3 in_Position;\n"\
	"layout(location=2) in vec3 normal;\n"\
	"layout(location=1) in vec3 in_Color;\n"\
	"layout(location=3) in vec2 texCoord;\n"\
	/*"layout(location=3) in vec2 texCoord;\n"\*/
	"out vec4 ex_Color;\n"\
	"out vec3 Normal;\n"
	"out vec3 FragPos;\n"
	"out vec2 TexCoord;\n"\
	"uniform mat4 ModelMatrix;\n"
	"uniform mat4 ViewMatrix;\n"
	"uniform mat4 ProjectionMatrix;\n"

	"void main(void)\n"\
	"{\n"\
	//"gl_Position = in_Position;\n"
	//"  gl_Position = (ProjectionMatrix * ViewMatrix * ModelMatrix) * in_Position;\n"
	//"gl_Position = ViewMatrix * ModelMatrix * in_Position;\n"
	/*"gl_Position = mvp * in_Position;\n"\*/
	"gl_Position = ProjectionMatrix*ViewMatrix*ModelMatrix * vec4(in_Position, 1.0);\n"\
	"  ex_Color = vec4(in_Color, 1.0);\n"\
	"mat3 normalMatrix = mat3(ModelMatrix);\n"
	"normalMatrix = inverse(normalMatrix);\n"
	"normalMatrix = transpose(normalMatrix);\n"
	"Normal = normalize(normalMatrix*normal);\n"
	"FragPos = vec3(ModelMatrix*vec4(in_Position, 1.0));\n"
	"TexCoord = texCoord;\n"\
	/*"  ex_Color = vec4(1.0, 0,0, 1.0);\n"\*/
	"}\n"
};

const GLchar* FragmentShaderWalec =
{
	"#version 400\n"\

	"in vec4 ex_Color;\n"\
	"in vec2 TexCoord;\n"\
	"out vec4 out_Color;\n"\

	"in vec3 Normal;\n"
	"in vec3 FragPos;\n"

	"uniform vec3 lightPos; \n"

	"uniform sampler2D Texture0;\n"\

	"void main(void)\n"\
	"{\n"\

	"vec3 norm = normalize(Normal);\n"
	"vec3 lightDir = normalize(lightPos - FragPos);\n"
	"float diff = max(dot(norm, lightDir), 0.0);\n"
	"vec3 diffuse = diff * vec3(1.0f, 1.0f, 1.0f);\n"

	/*"  out_Color = ex_Color;\n"\*/
	"out_Color = texture(Texture0, TexCoord*5)*vec4((diffuse + vec3(0.25f, 0.25f, 0.25f)), 1.0);\n"
	/*"  out_Color = texture(Texture0, TexCoord);\n"\*/
	"}\n"
};

void Walec::createShader() {
	GLenum ErrorCheckValue = glGetError();
	//ShaderIds[0] = glCreateProgram();
	ProgramId = glCreateProgram();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShaderWalec, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShaderWalec, NULL);
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
void Walec::createWalec() {
/*
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

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);*/

	float step = 360 / VERTEX_COUNT;
	int pointer = 0;
	int pointTex = 0;

	float X[VERTEX_COUNT];
	float Z[VERTEX_COUNT];



	for (float angle = 0; angle < 360; angle += step) {
		float x = sin(DegreesToRadians(angle));
		float z = cos(DegreesToRadians(angle));

		X[pointer] = x;
		Z[pointer] = z;

		pointer++;
		
	}

	pointer = 0;
	int q = 1;
	int w = 0;
	int e = 0;
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
		

		COLORS[pointer] = q;
		COLORS[pointer+1] = w;
		COLORS[pointer+2] = e;
		COLORS[pointer+3] = q;
		COLORS[pointer +4] = w;
		COLORS[pointer +5] = e;
		COLORS[pointer+6] = q;
		COLORS[pointer + 7] = w;
		COLORS[pointer + 8] = e;

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

		COLORS[pointer] = q;
		COLORS[pointer + 1] = w;
		COLORS[pointer + 2] = e;
		COLORS[pointer + 3] = q;
		COLORS[pointer + 4] = w;
		COLORS[pointer + 5] = e;
		COLORS[pointer + 6] = q;
		COLORS[pointer + 7] = w;
		COLORS[pointer + 8] = e;

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

		COLORS[pointer] = q;
		COLORS[pointer + 1] = w;
		COLORS[pointer + 2] = e;
		COLORS[pointer + 3] = q;
		COLORS[pointer + 4] = w;
		COLORS[pointer + 5] = e;
		COLORS[pointer + 6] = q;
		COLORS[pointer + 7] = w;
		COLORS[pointer + 8] = e;

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


		COLORS[pointer] = q;
		COLORS[pointer + 1] = w;
		COLORS[pointer + 2] = e;
		COLORS[pointer + 3] = q;
		COLORS[pointer + 4] = w;
		COLORS[pointer + 5] = e;
		COLORS[pointer + 6] = q;
		COLORS[pointer + 7] = w;
		COLORS[pointer + 8] = e;

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
		else if(e==1){
			q = 1;
			w = 0; 
			e = 0;
		}
		pointTex += 6;
		pointer += 9;
	}


	


//	std::cout << pointer << std::endl;
	
	//std::cout << sin(DegreesToRadians(45)) << std::endl;
	//std::cout << cos(DegreesToRadians(45)) << std::endl;

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

	glGenBuffers(1, &normalId);
	glBindBuffer(GL_ARRAY_BUFFER, normalId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(NORMALS), NORMALS, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

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

	texture0 = LoadMipmapTexture(GL_TEXTURE0, "bruk.png");


}
GLuint Walec::LoadMipmapTexture(GLuint texId, const char* fname)
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

void Walec::drawWalec() {

	glm::mat4  ProjectionMatrix, ViewMatrix, ModelMatrix;

	ProjectionMatrix = glm::perspective(glm::radians(70.0f), (float)1024 / (float)768, 0.1f, 500.0f);
	if (cam->FIRST_PERSON_MODE)
		ViewMatrix = glm::lookAt(cam->getVec3(), cam->getVec3() + cam->getLookAt(), glm::vec3(0, 1, 0));
	else
		ViewMatrix = glm::lookAt(cam->getVec3(), glm::vec3(5, 0, 5), glm::vec3(0, 1, 0));
	ModelMatrix = glm::mat4(1.0f);




	//YYY = glm::sin(Angle);
	//ZZZ = glm::cos(Angle);

	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(posX, posY, posZ));
	//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(XXX - 1 - cameraPosX, YYY - cameraPosY, 0 - cameraPosZ));
	//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(XXX - 1 - cameraPosX, -1 - cameraPosY, 0 - cameraPosZ));
	//ModelMatrix = glm::rotate(ModelMatrix, Angle / 10, glm::vec3(0, 0, 1));
	//ModelMatrix = glm::rotate(ModelMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.25, scaleY, 0.25));
	//ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1, 2, 1));




	//glm::mat4 mvp = ProjectionMatrix*ViewMatrix*  ModelMatrix;




	glUseProgram(ProgramId);
	glUniformMatrix4fv(Model_Location, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(View_Location, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix4fv(Projection_Location, 1, GL_FALSE, &ProjectionMatrix[0][0]);
	//glUniform3f(lightPosLoc, 8, 1, 2);
	glUniform3f(lightPosLoc, cam->getX(), cam->getY(), cam->getZ());


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(ProgramId, "Texture0"), 0);

	glBindVertexArray(vaoId);

	//glDrawElements(GL_TRIANGLES, _countof(INDICES), GL_UNSIGNED_INT, (GLvoid*)0);
	//std::cout << _countof(VERTICES) << std::endl;
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
			scaleY += przes;
			if (scaleY > 1.54) up = 1;
		}
		else {
			scaleY -= przes;
			if (scaleY < 0.5) {
				up = 0; 
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