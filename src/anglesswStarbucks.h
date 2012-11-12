#pragma once
#include "starbucks.h"
#include "Node.h"

class anglesswStarbucks : public Starbucks {
public:
	anglesswStarbucks(void);
	void build(Entry* c, int n);
	Entry* getNearest(double x, double y);
	virtual ~anglesswStarbucks(void);
private:
	Entry* entry_arr_;
	int length;
	Node* root;
};

