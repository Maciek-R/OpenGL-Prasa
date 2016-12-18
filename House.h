#ifndef HOUSE_H
#define HOUSE_H
#include"Shape.h"
#include <SOIL.h>
#include <vector>
#include "Wall.h"
using namespace std;
class House : public Shape{
private:

	GLfloat VERTICES[144] = {
		-1.0f, 0.0f, 1.0f,//przednia sciana
		-0.5f, 0.0f, 1.0f,
		-1.0f, 1.6f, 1.0f,
		-1.0f, 1.6f, 1.0f,
		-0.5f, 0.0f, 1.0f,
		-0.5f, 1.6f, 1.0f,

		0.5f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		0.5f, 1.6f, 1.0f,
		0.5f, 1.6f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.6f, 1.0f,

		-0.5f, 1.6f, 1.0f,
		0.5f, 0.8f, 1.0f,
		0.5f, 1.6f, 1.0f,
		-0.5f, 1.6f, 1.0f,
		-0.5f, 0.8f, 1.0f,
		0.5f, 0.8f, 1.0f,	//

		-1.0f, 0.0f, -1.0f,//tylna sciana
		 1.0f, 0.0f, -1.0f,
		-1.0f, 1.6f, -1.0f,
		-1.0f, 1.6f, -1.0f,
		 1.0f, 0.0f, -1.0f,
		 1.0f, 1.6f, -1.0f,//

		 -1.0f, 0.0f, -1.0f,//bocznaL sciana
		 -1.0f, 0.0f, 1.0f,
		-1.0f, 1.6f, -1.0f,
		-1.0f, 1.6f, -1.0f,
		-1.0f, 0.0f, 1.0f,
		-1.0f, 1.6f, 1.0f,//

		1.0f, 0.0f, -1.0f,//bocznaP sciana
		1.0f, 0.0f, 1.0f,
		1.0f, 1.6f, -1.0f,
		1.0f, 1.6f, -1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.6f, 1.0f,//

		-1.0f, 0.0f, 1.0f,//podloga
		1.0f, 0.0f, 1.0f,
		-1.0f, 0.0f, -1.0f,
		-1.0f, 0.0f, -1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, -1.0f,

							//gora
		-1.0f, 1.6f, 1.0f,
		1.0f, 1.6f, 1.0f,
		-1.0f, 1.6f, -1.0f,
		-1.0f, 1.6f, -1.0f,
		1.0f, 1.6f, 1.0f,
		1.0f, 1.6f, -1.0f
	
	};
	GLfloat COLORS[144] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f

	};


	GLfloat TEXTURE_COORDS[96] = {
		0.0f, 0.0f,//
		0.25f, 0.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.25f, 0.0f,
		0.25f, 1.0f,

		0.75f, 0.0f,
		1.0f, 0.0f,
		0.75f, 1.0f,
		0.75f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		0.25f, 1.0f,
		0.75f, 0.5f,
		0.75f, 1.0f,
		0.25f, 1.0f,
		0.25f, 0.5f,
		0.75f, 0.5f,//

		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 1.0f, 
		1.0f, 0.0f,
		1.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	GLuint texture0;
	GLuint texId;
	GLuint LoadMipmapTexture(GLuint texId, const char* fname);
	float Rotation;

	vector<Wall*> walls;
public:
	House(Camera*);
	House(Camera*, float, float, float, float);
	void createHouse(float, float, float);
	void createHouse180(float, float, float);
	void drawHouse();


};

#endif