#include <SOIL.h>
#include "Display.h"
#include "Shape.h"
#include "Triangle.h"
#include "Cube.h"
#include "Terrain.h"
#include "Walec.h"
#include "House.h"
#include "Tasma.h"
#include "Wall.h"

#include <vector>
int main()
{
	Display display;
	display.init();

	Camera camera(0,0.2f,0);
	
	//Terrain terrain(&camera);
	//terrain.createShader();
	//terrain.createTerrain();

	//Wall wall(&camera, 3,1,3, 1);
	//wall.createShader();
	//wall.createWall();

	House house(&camera);
	house.createHouse(0, 0, 0);

	House house2(&camera);
	house2.createHouse180(0, 0, 10);

	/*Triangle tr(&camera);
	tr.createShader();
	tr.createNewTriangle();*/

	vector<Cube*> podpory;
	Cube * pod1 = new Cube(&camera, 4, 0.88, 6, 0.5, 1.75, 0.5);
	pod1->createShader();
	pod1->createCube();
	podpory.push_back(pod1);
	Cube * pod2 = new Cube(&camera, 5, 2, 6, 0.5, 4, 0.5);
	pod2->createShader();
	pod2->setRotateZ(90);
	pod2->createCube();
	podpory.push_back(pod2);
	Cube * pod3 = new Cube(&camera, 6, 0.88, 6, 0.5, 1.75, 0.5);
	pod3->createShader();
	pod3->createCube();
	podpory.push_back(pod3);



	vector<Cube*> cubes;
	Cube * cub = new Cube(&camera, 5, 0.5f, 1, 0.5, 0.5, 0.5);
	cub->setTexture("grassy.png");
	cub->createShader();
	cub->createCube();
	cubes.push_back(cub);
	
	//Cube sciany(&camera, 6,6,6, 12,12,12);
	//sciany.setTexture("sciana.png");
	//sciany.createShader();
	//sciany.createCube();

	vector<Wall *> sciany;
	sciany.push_back(new Wall(&camera, 6, 6, -0.001, 6, 6, 1, 0, 0));
	sciany.push_back(new Wall(&camera, 12, 6, 6, 6, 6, 1, 270, 0));
	sciany.push_back(new Wall(&camera, 6, 6, 12.001, 6, 6, 1, 180, 0));
	sciany.push_back(new Wall(&camera, 0, 6, 6, 6, 6, 1, 90, 0));
	sciany.push_back(new Wall(&camera, 6, 12, 6, 6, 6, 1, 0, 90));
	sciany.push_back(new Wall(&camera, 6, 0, 6, 6, 6, 1, 0, 270));//podloga

	for (int i = 0; i < sciany.size(); ++i) {
		sciany[i]->createShader();
		sciany[i]->createWall();
	}

	//Cube tasma(&camera, 5,0,6, 0.5,0.5,12);
	//tasma.createShader();
	//tasma.createCube();

	Cube cube(&camera);
	cube.createShader();
	cube.createCube();

	Walec walec(&camera);
	walec.createShader();
	walec.createWalec();

	/*House house(&camera);
	house.createShader();
	house.createHouse();
	House house2(&camera, 5, 0, 11, 180);
	house2.createShader();
	house2.createHouse();*/

	Tasma tas(&camera);

	int indexWaitFor = 0;
	clock_t LastTime = 0;
	bool stop = false;
	do
	{
		display.prepare();  
		camera.serveEvents();

		//tr.serveTime();
		cube.serveTime();
		//terrain.serveTime();

		//wall.drawWall();
		house.drawHouse();
		house2.drawHouse();

	//	terrain.drawTerrain();
		//tr.drawNewTriangle();
		cube.drawCube();

		walec.serveTime();
		walec.drawWalec();

		for (int i = 0; i < sciany.size(); ++i) {
			sciany[i]->drawWall();
		}

		//sciany.drawCube();

	//	house.serveTime();
	//	house.drawHouse();
	//	house2.serveTime();
	//	house2.drawHouse();

		for (int i = 0; i < podpory.size(); ++i) {
			podpory[i]->drawCube();
		}

		//tasma.serveTime();
	//	tasma.drawCube();
		
		

		if (pressedP) {
			if(!stop)
			for (int i = 0; i < cubes.size(); ++i) {
				cubes[i]->move(3);
				tas.movePieces();
			}

			if (cubes[cubes.size() - 1]->getZ() > 2) {
				Cube * c = new Cube(&camera, 5, 0.5f, 1, 0.5, 0.5, 0.5);
				c->setTexture("grassy.png");
				c->createShader();
				c->createCube();
				cubes.push_back(c);
			}

			if(!stop)
			if (cubes[indexWaitFor]->getZ() >= 6) {	//wspolrzedna Z walca
				cubes[indexWaitFor]->setScaleYOf(&walec);
				stop = true;
				walec.start();
				LastTime = clock();
				std::cout << "Teraz" << std::endl;
				indexWaitFor++;
			}


			if (cubes[0]->getZ() > 11) {
				cubes.erase(cubes.begin());
				indexWaitFor--;
			}
		}
		else {
			for (int i = 0; i < cubes.size(); ++i) {
				cubes[i]->doNotMove();
				tas.doNotMovePieces();
			}

		}
		
		for (int i = 0; i < cubes.size(); ++i) {
			cubes[i]->drawCube();
		}



		if (stop) {
			for (int i = 0; i < cubes.size(); ++i) {
				cubes[i]->doNotMove();
				tas.doNotMovePieces();
			}
			clock_t Now = clock();

			
			if (((float)(Now - LastTime) / CLOCKS_PER_SEC) > 2 / float(PREDKOSC)) {
				stop = false;
				std::cout << ((float)(Now - LastTime) / CLOCKS_PER_SEC) << std::endl;
			}
		}
		//tas.movePieces();
		tas.drawPieces();

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




