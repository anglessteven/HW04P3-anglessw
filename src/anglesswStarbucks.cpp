#include "anglesswStarbucks.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

static const double difference = 0.00001;

anglesswStarbucks::anglesswStarbucks(void)
{
}

void anglesswStarbucks::build(Entry* c, int n)
{
	srand((unsigned) time(0));
	length = n;
	entry_arr_ = new Entry[length];
	for(int i=0; i<n; i++) {
		for(int j=0; j<i; j++) {
			if((j+1==i) && (abs(c[j].x-c[i].x) > difference) &&
				(abs(c[j].y-c[i].y) > difference)) {
				entry_arr_[i] = c[i];
			}
		}
	}
	root = new Node(entry_arr_[rand()%length]);
	for(int k=0; k<length; k++) {
		root->insert(entry_arr_[k],root,true);
	}
}

Entry* anglesswStarbucks::getNearest(double x, double y)
{
	Entry* temp = new Entry();
	temp->identifier = "temp";
	temp->x = x;
	temp->y = y;
	*temp = root->search(*temp,root,true)->entry_;
	return temp;
}

anglesswStarbucks::~anglesswStarbucks(void)
{
	delete [] entry_arr_;
	delete root;
}
