#ifndef BACKSTAGE_H
#define BACKSTAGE_H

#include "figure.h"
#include "primitive.h"
#include <vector>


class Backstage : public Entity {
private:
	bool cellsTaken[22][10];
	std::vector<Rectangle*> map;
	int height;
	int width;
	float relativeCellSizeX;
	float relativeCellSizeY;

public:
	Backstage();
	bool collisionOccured(Figure* figureFlying);
	void consumeFigure(Figure* fig);
	void reconstructBackstage();
	void moveTo(int key);
	void removeFilledRow();


	int scaledPositionToIndex(float scale);
	void setScreenSize(int height, int width);
	void setCellSize(float relativeCellSizeX, float relativeCellSizeY);
};




#endif