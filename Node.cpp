/*
 * Node.cpp

 *
 *  Created on: 11/ott/2013
 *      Author: user
 */

#include "Node.h"

Node::Node() {
	father = nullptr;
	label = string();
	children = vector<Node*>();
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

vector<Node*> Node::getChildren(){
	return children;
}

string Node::getLabel(){
	return label;
}


