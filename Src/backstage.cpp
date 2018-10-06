#include "backstage.h"


Backstage::Backstage() {

}



void Backstage::consumeFigure(Figure* fig) {
	for (int a = 0; a < 8; ++a) {
		if (fig->getConstructAt(a) != 0) {
			Primitive* tmp = fig->getConstructAt(a);
			map.push_back(tmp);
		}

	}

}

void Backstage::reconstructBackstage() {
	std::vector<Primitive*> carcass;  //possibly huge overhead along with some voulnrabilities 
	for (Primitive* m : map)
	{
		if (m != NULL)
			carcass.push_back(new Rectangle(m->getX(), m->getY(), relativeCellSizeX,relativeCellSizeY));



	}
	assemble(carcass, 4);
}


bool Backstage::collisionOccured(Figure* figureFlying) {
	for (Primitive* m : map)
		for (int b = 0; b < 8; ++b) {
			if (m != NULL)
				if (figureFlying->getConstructAt(b) != 0)
					if ((*(Point2D*)m) == *figureFlying->getPredictedConstruct(b))return true;
		}
	return false;
}




void Backstage::removeFilledRow() {/*
	for (int a = 0; a < rows.size(); ++a){
		if (rows[a] > 5)
		{
			for (int b = 0; b < map.size(); ++b){
				if (map[b]!=NULL)
				if (scaledPositionToIndex(map[b]->getY())==a){
					//map.erase(map.begin() + b);
					map[b] = NULL;
				}
			}
		}
	}*/
}

void Backstage::moveTo(int key) {

}


int Backstage::scaledPositionToIndex(float scale) {
	int res = ((scale + 1)*100.0f + 0.05) / 100.0f / 0.05f;

	return res;
}

void Backstage::setScreenSize(int height, int width) {
	this->height = height;
	this->width = width;
}

void Backstage::setCellSize(float relativeCellSizeX, float relativeCellSizeY) {
	this->relativeCellSizeX = relativeCellSizeX;
	this->relativeCellSizeY = relativeCellSizeY;

}