#ifndef TERRAIN_H
#define TERRAIN_H

//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
#include "Utils.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <iostream>
#include "Camera.h"
#include "GLOBALS.h"
#include <SOIL.h>

#define VERTEX_COUNT 100

class Terrain {
private:
	int SIZE = 12;
	GLfloat VERTICES[VERTEX_COUNT*VERTEX_COUNT * 3];
	GLfloat COLORS[VERTEX_COUNT*VERTEX_COUNT * 3];
	GLuint INDICES[6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1)];
	GLfloat NORMALS[VERTEX_COUNT*VERTEX_COUNT * 3];
	GLfloat TEXTURE_COORDS[VERTEX_COUNT*VERTEX_COUNT * 2];
	GLuint texture0;

	GLuint
		VertexShaderId,
		FragmentShaderId,
		ProgramId,

		mvp_location,
		vaoId,
		vboId,
		colorId,
		eboId,
		texId;
	
	float posX = 0;
	float posY = 0;
	float posZ = 0;

	Camera * cam;
	clock_t LastTime = 0;

	
	GLuint LoadMipmapTexture(GLuint texId, const char* fname);	
public:
	Terrain();
	Terrain(Camera *cam);

	void createTerrain();
	void drawTerrain();
	void createShader();
	void serveTime();
};

#endif