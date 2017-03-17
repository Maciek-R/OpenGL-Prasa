#ifndef CUBE_H
#define CUBE_H
#include "Shape.h"
//#include "Walec.h"
class Cube : public Shape {
private:

	float scaleX;
	float scaleY;
	float scaleZ;
	float RotateZ;
	Shape * walec;
public:
	Cube(Camera *, Light*);
	Cube(Camera *, Light*,  float, float, float);
	Cube(Camera *, Light*,  float, float, float, float, float, float);
	void init(Camera *, Light*);
	//void createShader();
	void draw();
	void create();
	
	void move(int);
	void doNotMove();
	void setScaleYOf(Shape *);
	void setRotateZ(float Z);

};

#endif