#include "Node.h"
#include <iostream>

Node::Node(Entry e)
{
	right_ = left_ = NULL; 
	entry_ = e;
}

Node* Node::insert(Entry e, Node* r, bool x_level)
{
	if(r == NULL) return new Node(e);
	if(e.x == r->entry_.x && e.y == r->entry_.y) return r;
	if(x_level) {
		if(e.x < r->entry_.x) 
			r->left_ = insert(e, r->left_, !x_level);
		else 
			r->right_ = insert(e, r->right_, !x_level);
	} else {
		if(e.y < r->entry_.y) 
			r->left_ = insert(e, r->left_, !x_level);
		else 
			r->right_ = insert(e, r->right_, !x_level);
	}
	return r;
}

Node* Node::search(Entry e, Node* r, bool x_level)
{
	if(r == NULL) return NULL;
	if(e.x == r->entry_.x && e.y == r->entry_.y) return r;
	Node* candidate;
	if(x_level) {
		if(e.x < r->entry_.x)
			candidate = search(e,r->left_,!x_level);
		else
			candidate = search(e,r->right_,!x_level);
	} else {
		if(e.y < r->entry_.y)
			candidate = search(e,r->left_,!x_level);
		else
			candidate = search(e,r->right_,!x_level);
	}
	if(candidate == NULL)
		return r;
	else {
		if(distance(e.x,candidate->entry_.x,e.y,candidate->entry_.y) < 
			distance(e.x,r->entry_.x,e.y,r->entry_.y)) {
				if(x_level) {
					if(abs(e.x-r->entry_.x) < distance(e.x,candidate->entry_.x,e.y,candidate->entry_.y))
						candidate = search(e,r->right_,!x_level);
				} else {
					if(abs(e.y-r->entry_.y) < distance(e.x,candidate->entry_.x,e.y,candidate->entry_.y))
						candidate = search(e,r->left_,!x_level);
				}
				return candidate;
		}
		else
			return r;
	}
}

double Node::distance(double x1, double x2, double y1, double y2)
{
	return ((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2));
}

/*
void Node::printInOrder(Node* r) 
{
	if(r == NULL) return;
	printInOrder(r->left_);
	cout << r->entry_.identifier << endl;
	printInOrder(r->right_);
}*/

Node::~Node(void)
{
	delete left_;
	delete right_;
}
