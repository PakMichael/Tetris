#ifndef BACKSTAGE_H
#define BACKSTAGE_H

#include "figure.h"
#include "primitive.h"
#include <vector>


class Backstage: public Entity {
private:
	std::vector<Primitive*> map;


public:
	Backstage();
	bool collisionOccured(Figure* figureFlying);
	void consumeFigure(Figure* fig);
	void reconstructBackstage();
	void moveTo(int key);
	void removeFilledRow();


	int scaledPositionToIndex(float scale);

};




#endif