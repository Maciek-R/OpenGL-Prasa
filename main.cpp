#include "Display.h"
#include "Shape.h"
#include "Cube.h"
#include "Walec.h"
#include "House.h"
#include "Tasma.h"
#include "Wall.h"
#include "Light.h"
#include "Prasa.h"
#include <vector>
int main()
{
	Display display;
	display.init();

	Camera camera(0,0.2f,0);

	Light light(&camera);
	light.createShader();
	light.createLight();

	
	House house(&camera, &light);
	house.createHouse(0, 0, 0);

	House house2(&camera, &light);
	house2.createHouse180(0, 0, 10);

	vector<Cube*> podpory;
	Cube * pod1 = new Cube(&camera, &light, 4, 0.88, 6, 0.5, 1.75, 0.5);
	pod1->createShader();
	pod1->create();
	podpory.push_back(pod1);
	Cube * pod2 = new Cube(&camera, &light, 5, 2, 6, 0.5, 4, 0.5);
	pod2->createShader();
	pod2->setRotateZ(90);
	pod2->create();
	podpory.push_back(pod2);
	Cube * pod3 = new Cube(&camera, &light, 6, 0.88, 6, 0.5, 1.75, 0.5);
	pod3->createShader();
	pod3->create();
	podpory.push_back(pod3);


	vector<Wall *> sciany;
	sciany.push_back(new Wall(&camera, &light, 6, 6, -0.001, 6, 6, 1, 0, 0));
	sciany.push_back(new Wall(&camera, &light, 12, 6, 6, 6, 6, 1, 270, 0));
	sciany.push_back(new Wall(&camera, &light, 6, 6, 12.001, 6, 6, 1, 180, 0));
	sciany.push_back(new Wall(&camera, &light, 0, 6, 6, 6, 6, 1, 90, 0));
	sciany.push_back(new Wall(&camera, &light, 6, 12, 6, 6, 6, 1, 0, 90));
	sciany.push_back(new Wall(&camera, &light, 6, 0, 6, 6, 6, 1, 0, 270));//podloga

	for (int i = 0; i < sciany.size(); ++i) {
		sciany[i]->createShader();
		sciany[i]->createWall();
	}



	Prasa prasa(&camera, &light);

	
	do
	{
		display.prepare();  
		camera.serveEvents();
		
		light.serveTime();
		light.move();
		light.drawLight();
		
		house.drawHouse();
		house2.drawHouse();

	


		for (int i = 0; i < sciany.size(); ++i) {
			sciany[i]->drawWall();
		}

		for (int i = 0; i < podpory.size(); ++i) {
			podpory[i]->draw();
		}

		
		prasa.move();
		prasa.draw();		

		display.swapBuffers(); 
		display.pollEvents();

	} 
	while (!display.windowShouldClose());

	display.destroyWindowAndTerminate();

	return 0;
}
