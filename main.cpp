#include "game.h"
#include "engine.h"




int main(){

	Engine engine;
	Game game;
	game.addObserver(&engine);
	game.init();
}