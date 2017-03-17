#include "../headers/Shape.h"

const GLchar* VertexShader =
{
	"#version 400\n"\

	"layout(location=0) in vec3 in_Position;\n"\
	"layout(location=1) in vec3 normal;\n"\
	"layout(location=3) in vec2 texCoord;\n"\
	"layout(location=2) in vec3 in_Color;\n"\

	"out vec4 ex_Color;\n"\
	"out vec3 Normal;\n"
	"out vec2 TexCoord;\n"\
	"out vec3 FragPos;\n"

	"uniform mat4 ModelMatrix;\n"
	"uniform mat4 ViewMatrix;\n"
	"uniform mat4 ProjectionMatrix;\n"

	"void main(void)\n"\
	"{\n"\
	"gl_Position = ProjectionMatrix*ViewMatrix*ModelMatrix * vec4(in_Position, 1.0);\n"\
	"  ex_Color = vec4(in_Color, 1.0);\n"\
	"TexCoord = texCoord;\n"\
	"mat3 normalMatrix = mat3(ModelMatrix);\n"
	"normalMatrix = inverse(normalMatrix);\n"
	"normalMatrix = transpose(normalMatrix);\n"
	"Normal = normalize(normalMatrix*normal);\n"
	"FragPos = vec3(ModelMatrix*vec4(in_Position, 1.0));\n"
	/*"TexCoord = texCoord;\n"\*/
	/*"  ex_Color = vec4(1.0, 0,0, 1.0);\n"\*/
	"}\n"
};

const GLchar* FragmentShader =
{
	"#version 400\n"\

	"in vec4 ex_Color;\n"\
	"in vec2 TexCoord;\n"\
	"out vec4 out_Color;\n"\

	"in vec3 Normal;\n"
	"in vec3 FragPos;\n"

	"uniform sampler2D Texture0;\n"\
	"uniform vec3 lightPos; \n"
	"uniform vec3 lightColor; \n"
	"uniform vec3 ambientColor; \n"
	"uniform int multi; \n"

	"void main(void)\n"\
	"{\n"\

	"vec3 norm = normalize(Normal);\n"
	"vec3 lightDir = normalize(lightPos - FragPos);\n"
	"float diff = max(dot(norm, lightDir), 0.0);\n"
	"vec3 diffuse = diff * lightColor;\n"


	/*"  out_Color = ex_Color;\n"\*/
	/*"out_Color = ex_Color*vec4((diffuse + vec3(0.25f, 0.25f, 0.25f)), 1.0);\n"*/
	"out_Color = texture(Texture0, TexCoord*multi)*vec4((diffuse + ambientColor), 1.0);\n"
	/*"  out_Color = texture(Texture0, TexCoord);\n"\*/
	"}\n"
};


Shape::Shape() {
	ProjectionMatrix = glm::perspective(glm::radians(70.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
	//this->cam = cam;
}


GLuint Shape::LoadMipmapTexture(GLuint texId, const char* fname)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);

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


void Shape::createShader() {
	GLenum ErrorCheckValue = glGetError();
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

	//mvp_location = glGetUniformLocation(ProgramId, "mvp");
	Model_Location = glGetUniformLocation(ProgramId, "ModelMatrix");
	View_Location = glGetUniformLocation(ProgramId, "ViewMatrix");
	Projection_Location = glGetUniformLocation(ProgramId, "ProjectionMatrix");
	lightPosLoc = glGetUniformLocation(ProgramId, "lightPos");
	lightColorLoc = glGetUniformLocation(ProgramId, "lightColor");
	ambientColorLoc = glGetUniformLocation(ProgramId, "ambientColor");
	MultiLoc = glGetUniformLocation(ProgramId, "multi");
}

void Shape::setTexture(char * textureName) {
	this->textureName = textureName;
}

void Shape::loadUniformLocations() {
	glUniformMatrix4fv(Model_Location, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(View_Location, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix4fv(Projection_Location, 1, GL_FALSE, &ProjectionMatrix[0][0]);
	//glUniform3f(lightPosLoc, cam->getX(), cam->getY(), cam->getZ());
	glUniform3f(lightPosLoc, light->getX(), light->getY(), light->getZ());
	glUniform1i(MultiLoc, multi);
	glUniform3f(lightColorLoc, light->getColorR(), light->getColorG(), light->getColorB());
	glUniform3f(ambientColorLoc, light->getAmbientColor().r, light->getAmbientColor().g, light->getAmbientColor().b);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(ProgramId, "Texture0"), 0);
}

void Shape::serveTime() {
	clock_t Now = clock();

	if (LastTime == 0)
		LastTime = Now;
	
	Angle = 10 * ((float)(Now - LastTime) / CLOCKS_PER_SEC);
	przes = 10 * ((float)(Now - LastTime) / CLOCKS_PER_SEC);

	LastTime = Now;
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

Shape::~Shape() {
	destroyVbo();
	destroyShaders();
}

void Shape::destroyVbo(){

	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &colorId);
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &normalId);
	glDeleteBuffers(1, &texId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vaoId);
}



void Shape::destroyShaders(){

	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);
}
void Shape::create() {

}
void Shape::draw() {
	
}
void Shape::doNotMove() {

}
void Shape::move(int) {

}
void Shape::setScaleYOf(Shape *) {

}



