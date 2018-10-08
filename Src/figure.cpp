#include "figure.h"

bool blueprints[7][8] = {   /* sorry for this :C */
		//{ 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 1, 1, 1, 0, 0, 0, 1, 0 },
		{ 1, 1, 1, 0, 1, 0, 0, 0 },
		{ 1, 1, 0, 0, 1, 1, 0, 0 },
		{ 0, 1, 1, 0, 1, 1, 0, 0 },
		{ 1, 1, 1, 0, 0, 1, 0, 0 },
		{ 1, 1, 0, 0, 0, 1, 1, 0 },
};



Figure::Figure(float height, float width) {
	this->relativeHeight = height;
	this->relativeWidth = width;
	tempX = relativeWidth * (rand() % 40 - 20);
	tempY = 1;

	speed = 1;
	collidedGround = false;
	blueprintIndex = rand() % 7;
	constructCarcass();

}

Figure::~Figure() {

	std::cout << "destroy fig" << std::endl;
}

void Figure::init() {
	t = std::thread(&Figure::freeFall, this);
}

void Figure::freeFall() {
	while (!collidedGround)
	{
		notify("drop");
		clock_t now = clock() / CLOCKS_PER_SEC;
		while (clock() / CLOCKS_PER_SEC - now < speed);

	}

}


void Figure::moveTo(int key) {
	if (key == 'E') { collidedGround = true; notify("immovable"); } //always called from main thread
	directionKey = key;
	notify("moveTo");
}

void Figure::moveRight() {
	tempX += relativeWidth;
}

void Figure::moveLeft() {
	tempX -= relativeWidth;
}

void Figure::moveDown() {
	tempY -= relativeHeight;
}

void Figure::moveUp() {
	tempY += relativeHeight;
}

void Figure::boostDown() {
	speed = 0;
}

void Figure::rotate() {
	if (angle == 0)
	{
		angle = M_PI / 2;
	}
	else
	{
		angle = 0.0;
	}

}


int Figure::getDirection() {
	return directionKey;
}


void Figure::constructCarcass() {
	//runs once at the beginning 
	//later only visually translates image without any change in model
	std::vector<Primitive*> carcass;  //possibly huge overhead along with some voulnrabilities 
	for (int a = 0; a < 8; ++a)
	{
		if (blueprints[blueprintIndex][a])
		{
			float tmpX = a * relativeWidth - relativeWidth * 4 * (a / 4);
			float tmpY = -(a / 4)*relativeHeight;
			if (!Arithmetics::floatEquals(angle, 0))
			{
				float temp = tmpX;
				tmpX = -tmpY;
				tmpY = temp;
			}
			tiles[a] = std::make_shared<Rectangle>(tmpX,tmpY, relativeWidth, relativeHeight);
			carcass.push_back(&*tiles[a]);
		}


	}
	assemble(carcass, 4);

}

Point2D* Figure::getDimensionsOfTile(int index, float angle) {
	if (!blueprints[blueprintIndex][index])return 0;
	float tmpX = index * relativeWidth - relativeWidth * 4 * (index / 4);
	float tmpY = -(index / 4)*relativeHeight;
	if (!Arithmetics::floatEquals(angle, 0))
	{
		float temp = tmpX - relativeHeight;
		tmpX = -tmpY;
		tmpY = temp;
	}
	return new Point2D(tmpX + mX, tmpY + mY);
}
bool Figure::intersects(Rectangle* rec) {

	for (int a = 0; a < 8; ++a)
	{
		float tmpX = a * relativeWidth - relativeWidth * 4 * (a / 4);
		float tmpY = -(a / 4)*relativeHeight;
		Rectangle* recTemp = new Rectangle(tmpX + tempX, tmpY + tempY, relativeWidth, relativeHeight);
		if (blueprints[blueprintIndex][a] && rec)
		{
			if (*recTemp == *rec)
			{
				return true;
			}

		}
	}
	return false;
}



void Figure::fulfilProphecy() {
	mX = tempX;
	mY = tempY;
	constructCarcass();
}


float Figure::getAngle() {
	return angle;
}