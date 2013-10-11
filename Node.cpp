/*
 * Node.cpp
 *
 *  Created on: 11/ott/2013
 *      Author: user
 */
#include <cstdlib>

#include "Node.h"

Node::Node() {
	father = nullptr;
	label = string();
	children = vector<Node*>();
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

