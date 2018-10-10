#ifndef BACKSTAGE_H
#define BACKSTAGE_H

#include "figure.h"
#include "primitive.h"
#include <vector>


#include <set>

class Node {
	std::set<Node*> connections;
	bool value;

public:
	Node(bool value) {
		this->value = value;
	}

	void connectTo(Node* node) {
		connections.insert(node);
	}
	void disconnectFrom(Node* node) {
		connections.erase(node);
	}
	std::set<Node*>* getConnections() {
		return &connections;
	}

	bool getValue() {
		return value;
	}
};


class Graph {
	std::vector<Node*> allNodes;
	std::set<Node*> visitedStack;

private:
	bool traverseFrom(Node* node) {
		if (node->getValue()) {
			for (Node* temp : node->getConnections()->begin) {
				if (visitedStack.find(temp) == visitedStack.end())
					traverseFrom(temp);
			}

		}
		else return false;
		return true;
	}
public:
	void addEdge(int a, int b) {
		allNodes[a]->connectTo(allNodes[b]);
		allNodes[b]->connectTo(allNodes[a]);
	}
	void removeEdge(int a, int b) {
		allNodes[a]->disconnectFrom(allNodes[b]);
		allNodes[b]->disconnectFrom(allNodes[a]);
	}
	void addNode(Node* node) {
		allNodes.push_back(node);
	}
	bool traverseFrom(int index) {
		return traverseFrom(allNodes[index]);
	}

};



class Backstage : public Entity {
private: 

	bool cellsTaken[22][10];
	std::vector<Rectangle*> map;
	int height;
	int width;
	float relativeCellSizeX;
	float relativeCellSizeY;

public:	Graph g;
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