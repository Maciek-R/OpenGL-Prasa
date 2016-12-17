#include "Tasma.h"

Tasma::Tasma(Camera *cam) {
	float Z = 0;
	for (int i = 0; i < N; ++i) {
		pieceUp[i] = new Cube(cam, 5, 0.1875, Z, 0.5, 0.125, 0.5);
		pieceUp[i]->createShader();
		pieceUp[i]->setTexture("tas.png");
		pieceUp[i]->createCube();

		pieceDown[i] = new Cube(cam, 5, 0.0625, 12-Z, 0.5, 0.125, 0.5);
		pieceDown[i]->createShader();
		pieceDown[i]->setTexture("tas.png");
		pieceDown[i]->createCube();

		Z += 0.5;
	}
		
}

void Tasma::drawPieces() {
	for (int i = 0; i < N; ++i) {
		pieceUp[i]->drawCube();
		pieceDown[i]->drawCube();
	}
}
void Tasma::movePieces() {
	for (int i = 0; i < N; ++i) {
		pieceUp[i]->move(3);
		pieceDown[i]->move(2);
	}
	if (pieceUp[0]->getZ() > 0) {
		for (int i = 0; i < N; ++i) {
			pieceUp[i]->setZ(pieceUp[i]->getZ() - 5);
			pieceDown[i]->setZ(pieceDown[i]->getZ() + 5);
		}
	}
}
void Tasma::doNotMovePieces() {
	for (int i = 0; i < N; ++i) {
		pieceUp[i]->doNotMove();
		pieceDown[i]->doNotMove();
	}

}