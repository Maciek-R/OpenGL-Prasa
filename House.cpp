#include "House.h"

House::House(Camera * cam, Light * light) {
	this->cam = cam;
	this->light = light;

	posX = 0;
	posY = 0;
	posZ = 0;
}


void House::createHouse(float X, float Y, float Z) {

	walls.push_back(new Wall(cam, light, X + 5, Y + 1.5, Z + 2, 1, 0.5, 1, 0, 0));
	walls.push_back(new Wall(cam, light, X + 5, Y + 1.5, Z + 1.99, 1, 0.5, 1, 180, 0));

	walls.push_back(new Wall(cam, light, X + 4.375, Y + 0.5, Z + 2, 0.375, 0.5, 1, 0, 0));
	walls.push_back(new Wall(cam, light, X + 4.375, Y + 0.5, Z + 1.99, 0.375, 0.5, 1, 180, 0));

	walls.push_back(new Wall(cam, light, X + 5.625, Y + 0.5, Z + 2, 0.375, 0.5, 1, 0, 0));
	walls.push_back(new Wall(cam, light, X + 5.625, Y + 0.5, Z + 1.99, 0.375, 0.5, 1, 180, 0));

	walls.push_back(new Wall(cam, light, X + 6, Y + 1, Z + 1, 90, 0));
	walls.push_back(new Wall(cam, light, X + 5.99, Y + 1, Z + 1, 270, 0));

	walls.push_back(new Wall(cam, light, X + 4, Y + 1, Z + 1, 270, 0));
	walls.push_back(new Wall(cam, light, X + 4.01, Y + 1, Z + 1, 90, 0));

	walls.push_back(new Wall(cam, light, X + 5, Y + 2, Z + 1, 0, 270));//dach
	walls.push_back(new Wall(cam, light, X + 5, Y + 1.99, Z + 1, 0, 90));//dach

	walls.push_back(new Wall(cam, light, X + 5, Y + 0.02, Z + 1, 0, 270));//podloga

	walls.push_back(new Wall(cam, light, X + 5, Y + 1, Z + 0, 0, 0));//tyl

	for (int i = 0; i < walls.size(); ++i) {
		walls[i]->createShader();
		walls[i]->setMulti(5);
	}
	setTextures();
	for (int i = 0; i < walls.size(); ++i) {
		walls[i]->createWall();
	}

}

void House::createHouse180(float X, float Y, float Z) {

	walls.push_back(new Wall(cam, light, X + 5, Y + 1.5, Z + 0, 1, 0.5, 1, 180, 0));//
	walls.push_back(new Wall(cam, light, X + 5, Y + 1.5, Z + 0.01, 1, 0.5, 1, 0, 0));//

	walls.push_back(new Wall(cam, light, X + 4.275, Y + 0.5, Z + 0, 0.275, 0.5, 1, 180, 0));
	walls.push_back(new Wall(cam, light, X + 4.275, Y + 0.5, Z + 0.01, 0.275, 0.5, 1, 0, 0));

	walls.push_back(new Wall(cam, light, X + 5.725, Y + 0.5, Z + 0, 0.275, 0.5, 1, 180, 0));
	walls.push_back(new Wall(cam, light, X + 5.725, Y + 0.5, Z + 0.01, 0.275, 0.5, 1, 0, 0));

	walls.push_back(new Wall(cam, light, X + 6, Y + 1, Z + 1, 90, 0));
	walls.push_back(new Wall(cam, light, X + 5.99, Y + 1, Z + 1, 270, 0));

	walls.push_back(new Wall(cam, light, X + 4, Y + 1, Z + 1, 270, 0));
	walls.push_back(new Wall(cam, light, X + 4.01, Y + 1, Z + 1, 90, 0));

	walls.push_back(new Wall(cam, light, X + 5, Y + 2, Z + 1, 0, 270));//dach
	walls.push_back(new Wall(cam, light, X + 5, Y + 1.99, Z + 1, 0, 90));//dach

	walls.push_back(new Wall(cam, light, X + 5, Y + 0.02, Z + 1, 0, 270));//podloga

	walls.push_back(new Wall(cam, light, X + 5, Y + 1, Z + 2, 180, 0));//tyl  //

	for (int i = 0; i < walls.size(); ++i) {
		walls[i]->createShader();
		walls[i]->setMulti(5);
	}
	setTextures();
	for (int i = 0; i < walls.size(); ++i) {
		walls[i]->createWall();
	}
}


void House::drawHouse() {

	for (int i = 0; i < walls.size(); ++i) {
		walls[i]->drawWall();
	}
}

void House::setTextures() {
	for (int i = 0; i < walls.size(); ++i) {
		walls[i]->setTexture("bruk.png");
	}
}