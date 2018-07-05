#include "figure.h"

bool blueprints[7][8] = {   /* sorry for this :C */
		{ 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 1, 1, 1, 0, 0, 0, 1, 0 },
		{ 1, 1, 1, 0, 1, 0, 0, 0 },
		{ 1, 1, 0, 0, 1, 1, 0, 0 },
		{ 0, 1, 1, 0, 1, 1, 0, 0 },
		//{ 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 0, 0, 1, 0, 0 },
		{ 1, 1, 0, 0, 0, 1, 1, 0 },
};



Figure::Figure(){
	cellSize = 0.05f;
	srand(std::time(0));
	tempX = cellSize*(rand() % 40 - 20);
	tempY = 1;
	speed = 1;//0.75;

	collidedGround = false;
	srand(std::time(0));
	blueprintIndex = rand() % 7;
	constructCarcass();

	for (int a = 0; a < 8; ++a)
	{
		if (blueprints[blueprintIndex][a])  //this should be the one and only use of blueprints by a single figure object
		{
			points[a] = std::make_shared<Point2D>(0, 0);
		}
		else points[a] = nullptr;
	}

}

Figure::~Figure(){
	
	std::cout << "destroy fig" << std::endl;
}

void Figure::init(){
	t = std::thread(&Figure::freeFall, this);
}

void Figure::freeFall(){
	while (!collidedGround)
	{
		moveTo((int)'S');
		clock_t now = clock() / CLOCKS_PER_SEC;
		while (clock() / CLOCKS_PER_SEC - now < speed);

	}

}
float Figure::getCellSize(){
	return cellSize;
}

void Figure::moveTo(int key){
	if (collidedGround && key != 'S'){ notify("immovable"); } //always called from main thread
	if (collidedGround && key == 'S')return;
	directionKey = key;
	notify("moveTo");
}

void Figure::moveRight(){
	tempX += cellSize;
	reconstruct();
}

void Figure::moveLeft(){
	tempX -= cellSize;
	reconstruct();
}

void Figure::moveDown(){
	tempY -= cellSize;
	reconstruct();
}

void Figure::moveUp(){
	tempY += cellSize;
	reconstruct();
}

void Figure::boostDown(){
	speed = 0;
}

void Figure::rotate(){
	if (angle == 0)
	{
		angle = M_PI / 2;
	}
	else
	{
		angle = 0.0;
	}

	reconstruct();

}

void Figure::reconstruct(){
	for (int a = 0; a < 8; ++a)
	{
		if (points[a])
		{

			if (angle == 0)
			{
				points[a]->setX(tempX + a*cellSize - cellSize * 4 * (a / 4));
				points[a]->setY(tempY - (a / 4)*cellSize);

				if (points[a]->getY() < lowestPoint)
					lowestPoint = points[a]->getY();
				if (points[a]->getY() > highestPoint)
					highestPoint = points[a]->getY();

			}
			else
			{
				points[a]->setX(tempX + (a / 4)*cellSize);
				points[a]->setY(tempY + a*cellSize - cellSize * 4 * (a / 4));

				if (points[a]->getY() < lowestPoint)
					lowestPoint = points[a]->getY();
				if (points[a]->getY() > highestPoint)
					highestPoint = points[a]->getY();
			}

		}

	}

}

int Figure::getDirection(){
	return directionKey;
}

float Figure::getLowestPoint(){
	return lowestPoint;
}

float Figure::getHighestPoint(){
	return highestPoint;
}

void Figure::constructCarcass(){
	std::vector<Primitive*> carcass;  //possibly huge overhead along with some voulnrabilities 
	for (int a = 0; a < 8; ++a)
	{
		if (blueprints[blueprintIndex][a])
		{
			float tmpX = a*cellSize - cellSize * 4 * (a / 4);
			float tmpY = -(a / 4)*cellSize;
			carcass.push_back(new Square(tmpX, tmpY, cellSize));
		}


	}
	assemble(carcass, 4);



}
bool Figure::intersects(Figure* f){
	for (int a = 0; a < 8; ++a)
	{

		if (this->getConstructAt(a))
			for (int b = 0; b < 8; ++b)
			{
			if (f->getConstructAt(b))
				if (*f->getConstructAt(b) == *this->getConstructAt(a))return true;

			}

	}
	return false;
}

bool Figure::intersects(Point2D* point){
	for (int a = 0; a < 8; ++a)
	{

		if (this->getConstructAt(a))
		{
			if (*this->getConstructAt(a) == *point)return true;
		}

	}
	return false;
}

Point2D* Figure::getConstructAt(int index){
	return points[index].get();
}

Point2D* Figure::getPredictedConstruct(int index){
	Point2D* temp;
	if (angle == 0){
		temp = new Point2D(tempX + index*cellSize - cellSize * 4 * (index / 4), tempY - (index / 4)*cellSize);
	}
	else {
		temp = new Point2D(tempX + (index / 4)*cellSize, tempY + index*cellSize - cellSize * 4 * (index / 4));

	}
	return temp;
}

 
bool Figure::crosses(float pX, float pY){
	// TO REDO
	// Only one parameter is used! 
	// Add selective x or y, or both x and y
	for (int a = 0; a < 8; ++a)
	{

		if (this->getConstructAt(a))
		{
			if (this->getConstructAt(a)->getY() < pY)return true;
		}

	}
	return false;
}

void Figure::setHitEarth(){
	collidedGround = true;
	tempX = mX;
	tempY = mY;
	reconstruct();
}

void Figure::getCoordinates(float& x, float& y){
	x = mX;
	y = mY;

}

void Figure::getPredictedCoordinates(float& x, float& y){
	x = tempX;
	y = tempY;

}


bool Figure::hitEarth(){
	return collidedGround;
}

void Figure::fulfilProphecy(){
	mX = tempX;
	mY = tempY;
	reconstruct();
}
