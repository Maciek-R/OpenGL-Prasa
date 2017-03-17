#include "../headers/Prasa.h"

Prasa::Prasa(Camera* camera, Light * light) {
	Shape * cub = new Cube(camera, light, 5, 0.5f, 1, 0.5, 0.5, 0.5);
	cub->setTexture("res/bloczek.png");
	cub->createShader();
	cub->create();
	blocks.push_back(cub);

	tas = new Tasma(camera, light);

	walec = new Walec(camera, light, &stop);
	walec->createShader();
	walec->create();

	this->cam = camera;
	this->light = light;
	this->walec = walec;
}

void Prasa::move() {
	if (pressedP) {
		if (!stop)
			for (int i = 0; i < blocks.size(); ++i) {
				blocks[i]->move(3);
				tas->movePieces();
			}

		if (blocks[blocks.size() - 1]->getZ() > 2) {
			int x = rand() % 2;
			Shape *c;
			if (x)
				c = new Cube(cam, light, 5, 0.5f, 1, 0.5, 0.5, 0.5);
			else
				c = new Walec(cam, light, 5, 0.75f, 1, 0.3, 0.5, 0.3);

				
			
			c->setTexture("res/bloczek.png");
			c->createShader();
			c->create();
			blocks.push_back(c);
		}

		if (!stop)
			if (blocks[indexWaitFor]->getZ() >= 6) {	//wspolrzedna Z walca
				blocks[indexWaitFor]->setScaleYOf(walec);
				stop = true;
				walec->start();

				indexWaitFor++;
			}


		if (blocks[0]->getZ() > 11) {
			blocks.erase(blocks.begin());
			indexWaitFor--;
		}
	}
	else {
		for (int i = 0; i < blocks.size(); ++i) {
			blocks[i]->doNotMove();
			tas->doNotMovePieces();
		}

	}

	if (stop) {
		for (int i = 0; i < blocks.size(); ++i) {
			blocks[i]->doNotMove();
			tas->doNotMovePieces();
		}

	}

	walec->serveTime();
}

void Prasa::draw() {
	for (int i = 0; i < blocks.size(); ++i) {
		blocks[i]->draw();
	}
	tas->drawPieces();
	walec->draw();
}


