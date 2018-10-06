#ifndef GAME_H
#define GAME_H

#include "observer.h"
#include "observable.h"
#include "figure.h"
#include "backstage.h"
#include <vector>
#include <string>



class Game : public Observer, public Observable {
	Figure* figureFlying;
	Backstage* gameField;
	float relativeCellSizeX = 0.05f;
	float relativeCellSizeY = 0.05f;

public:
	void init();
	void createFigure();
	void induceMovement();


private:
	void update(std::string msg, void* obj);







};






#endif 