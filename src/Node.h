#pragma once
#include "Starbucks.h"
class Node {
public:
	Node* left_;
	Node* right_;
	Entry entry_;
	Node(Entry e);
	Node* insert(Entry e, Node* r, bool x_level);
	Node* search(Entry e, Node* r, bool x_level);
	double distance(double x1, double x2, double y1, double y2);
	//void printInOrder(Node* r);
	virtual ~Node(void);
};

