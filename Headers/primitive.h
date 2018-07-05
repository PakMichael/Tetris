#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <iostream>

class Primitive{
protected:
	float x, y;
	int vertices;
public:
	virtual float getX() = 0;
	virtual float getY() = 0;
	virtual float getVertexAt(int index) = 0;
	virtual int getVertices() = 0;
};


class Point2D : public Primitive{


public:
	Point2D(float x, float y);
	int getVertices();
	float getX();
	float getY();
	void setX(float pX);
	void setY(float pY);
	float getVertexAt(int index){ return 0.0; }
	bool operator==(Point2D& b);
};


class Square : public Primitive{
private:
	float sidesSize;
	float matrix[12]; // {x, y ,z=0} * 4

public:
	Square();
	Square(float x, float y, float sidesSize);
	~Square();
	float getVertexAt(int index);
	float getX();
	float getY();
	void setX(float pX);
	void setY(float pY);
	int getVertices();
	float getSize();
	bool operator==(Square& b);
private:
	void build();
};



#endif 