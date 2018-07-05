#include "game.h"

using namespace std;
void Game::init() {
	gameField = new Backstage();
	notify("updBackstage", gameField);
	createFigure();
	notify("init");

}


void Game::createFigure() {
	Figure* tmp = new Figure();
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
		gameField->removeFilledRow();
	}

}

void Game::update(std::string msg, void* obj) {
	if (msg == "moveTo")induceMovement();
	if (msg == "immovable") {
		gameField->reconstructBackstage();
		createFigure();
	}
}
