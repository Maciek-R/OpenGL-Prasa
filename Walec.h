#ifndef WALEC_H
#define WALEC_H

#include "Shape.h"

#define VERTEX_COUNT 30		//liczba wierzcho³ków podstawy

//class Shape;

class Walec : public Shape {

private:
	
	GLfloat VERTICES[(VERTEX_COUNT * 3)*3*2 + (VERTEX_COUNT*6*3)];
	GLfloat COLORS[(VERTEX_COUNT * 3)*3*2 + (VERTEX_COUNT * 6 * 3)];
	GLfloat NORMALS[(VERTEX_COUNT * 3) * 3 * 2 + (VERTEX_COUNT * 6 * 3)];
	GLfloat TEXTURE_COORDS[(VERTEX_COUNT * 3) * 2 * 2 + (VERTEX_COUNT * 6 * 2)];

	bool running;
	float scaleY;
	int up;
	bool * stopp;

	float scaleX;
	float scaleZ;
	Shape * walec;

	void addColors();
public:
	Walec(Camera *, Light*, bool *);
	Walec(Camera *, Light*, float, float, float, float, float, float);
	//void createShader();
	void create();
	void draw();

	void serveTime();
	void move(int);
	void doNotMove();
	void setScaleYOf(Shape *);
	void start();
	void stop();
	float getScaleY();
};


#endif