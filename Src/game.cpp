#include "game.h"

using namespace std;
void Game::init() {
	int heightPX = 500;
	int widthPX = 500;
	relativeCellSizeX = 0.05; //0.0833;
	relativeCellSizeY = 0.05;
	notify("init", new Point2D(widthPX, heightPX));
	srand(std::time(0));
	gameField = new Backstage();
	gameField->setScreenSize(widthPX, heightPX);
	gameField->setCellSize(relativeCellSizeX, relativeCellSizeY);
	notify("updBackstage", gameField);
	createFigure();
	notify("start");

}


void Game::createFigure() {
	Figure* tmp = new Figure( relativeCellSizeY, relativeCellSizeX);
	tmp->addObserver(this);
	figureFlying = tmp;
	notify("updPlayerFigure", figureFlying);
	tmp->init();

}



void Game::induceMovement() {

	switch (figureFlying->getDirection())
	{
	case ' ':
		figureFlying->rotate();
		break;
	case 'Q':
		figureFlying->boostDown();
		break;
	case 'A':
		figureFlying->moveLeft();
		break;
	case 'D':
		figureFlying->moveRight();
		break;
	case 'S':
		figureFlying->moveDown();
		break;
	case 'W':
		figureFlying->moveUp();
		break;
	case 'E':
		figureFlying->setHitEarth();
		break;
	}

	if (!gameField->collisionOccured(figureFlying) && !figureFlying->crosses(0, -1) && !figureFlying->hitEarth())
	{
		figureFlying->fulfilProphecy();

		string tmp = "redraw";
		notify(tmp);
		/*	float tmpx;
			float tmpy;
			figureFlying->getCoordinates(tmpx, tmpy);
			std::cout << gameField->scaledPositionToIndex(tmpy) << std::endl;*/
		return;
	}
	else
	{
		figureFlying->setHitEarth();
		gameField->consumeFigure(figureFlying);
		notify("immobilized");
		//gameField->removeFilledRow();
	}

}

void Game::update(std::string msg, void* obj) {
	if (msg == "moveTo")induceMovement();
	if (msg == "immovable") {
		gameField->reconstructBackstage();
		createFigure();
	}
}
