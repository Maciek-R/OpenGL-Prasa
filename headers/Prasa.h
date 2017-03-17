#ifndef PRASA_H
#define PRASA_H

#include "Shape.h"
#include <vector>
#include "Camera.h"
#include "Light.h"
#include "Tasma.h"
#include "Walec.h"

class Prasa {
private:
	std::vector<Shape*> blocks;
	Tasma * tas;

	Camera * cam;
	Light * light;
	Walec * walec;

	bool stop = false;

	int indexWaitFor = 0;
public:
	Prasa(Camera *, Light *);
	void move();
	void draw();
};

#endif