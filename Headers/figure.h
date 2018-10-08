#ifndef FIGURE_H
#define FIGURE_H

# define M_PI 3.14159265358979323846

#include "observable.h"
#include "entity.h"
#include "primitive.h"
#include <cstdlib>
#include <vector>
#include <thread>
#include <ctime>
#include <cmath>

extern bool blueprints[7][8];


class Figure : public Observable, public Entity{


	int blueprintIndex;
	int directionKey;
	float speed;

	bool collidedGround;

	float tempX, tempY;

	std::shared_ptr<Rectangle> tiles[8];


public:
	std::thread t;

public:
	Figure(float height, float width);
	~Figure();

	void boostDown();
	void moveRight();
	void moveLeft();
	void moveDown();
	void moveUp();
	void rotate();

	int getDirection();

	void init();


	void fulfilProphecy();

	bool intersects(Rectangle* rec);
	Point2D* getDimensionsOfTile(int index, float angle);
	float getAngle();

private:
	void freeFall();
	void moveTo(int key);
	void constructCarcass();

};



#endif