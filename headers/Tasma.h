#ifndef TASMA_H
#define TASMA_H

#include "Cube.h"
#include <vector>
using namespace std;

#define N 35

class Tasma {
private:
	Cube* pieceDown[N];
	Cube* pieceUp[N];
	
public:
	Tasma(Camera*, Light *);
	void movePieces();
	void doNotMovePieces();
	void drawPieces();
};

#endif