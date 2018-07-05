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



public:
	void init();
	void createFigure();
	void induceMovement();


private:
	void update(std::string msg, void* obj);







};






#endif 