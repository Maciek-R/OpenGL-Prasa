#include <SOIL.h>
#include "Display.h"
#include "Shape.h"
#include "Triangle.h"
#include "Cube.h"
#include "Terrain.h"
#include "Walec.h"

int main()
{
	Display display;
	display.init();

	Camera camera(0,0,0);
	
	Terrain terrain(&camera);
	terrain.createShader();
	terrain.createTerrain();

	Triangle tr(&camera);
	tr.createShader();
	//tr.createCube();
	tr.createNewTriangle();

	/*Triangle ttt(&camera);
	ttt.createShader();
	ttt.createTriangle();*/

	Cube cube(&camera);
	cube.createShader();
	cube.createCube();

	Walec walec(&camera);
	walec.createShader();
	walec.createWalec();


	do
	{
		display.prepare();  
		camera.serveEvents();

		tr.serveTime();
		cube.serveTime();
		terrain.serveTime();

		//ttt.drawTriangle();
		terrain.drawTerrain();
		//tr.drawCube();
		tr.drawNewTriangle();
		cube.drawCube();

		walec.serveTime();
		walec.drawWalec();

		display.swapBuffers(); 
		display.pollEvents();

	} 
	while (!display.windowShouldClose());

	display.destroyWindowAndTerminate();

	return 0;
}





/*void DestroyVBO(void)
{
	GLenum ErrorCheckValue = glGetError();

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not destroy the VBO: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}
*/


/*void DestroyShaders(void)
{
	GLenum ErrorCheckValue = glGetError();


	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not destroy the shaders: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
}
*/




