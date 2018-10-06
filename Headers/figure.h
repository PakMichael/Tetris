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


	int directionKey;
	float speed;

	float lowestPoint;
	float highestPoint;
	bool collidedGround;
	float tempX, tempY;
	std::shared_ptr<Point2D> points[8];
	int blueprintIndex;
public:
	std::thread t;

public:
	Figure(float height, float width);
	~Figure();
	void getCoordinates(float& x, float& y);
	bool hitEarth();

	void moveRight();
	void moveLeft();
	void moveDown();
	void moveUp();
	int getDirection();
	void init();
	void setHitEarth();
	void boostDown();
	void getPredictedCoordinates(float& x, float& y);
	void fulfilProphecy();
	void rotate();
	bool intersects(Figure* f);
	bool intersects(Point2D* point);
	bool crosses(float x, float y);
	void reconstruct();
	Point2D getCellSize();
	Point2D* getConstructAt(int index);
	Point2D* getPredictedConstruct(int index);
	float getLowestPoint();
	float getHighestPoint();


private:
	void freeFall();
	void moveTo(int key);
	void constructCarcass();
	void immobalize();

};



#endif