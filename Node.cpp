/*
 * Node.cpp

 *
 *  Created on: 11/ott/2013
 *      Author: user
 */

#include "Node.h"

Node::Node() {
	myFather = nullptr;
	myLabel = string();
	myChildren = vector<Node*>();
	vector<suffixInfo> myLeafInfo= vector<suffixInfo>();
}

Node::Node(Node* father, string label, vector<Node*> children) {
	myFather = father;
	myLabel = label;
	myChildren = children;
	vector<suffixInfo> myLeafInfo = vector<suffixInfo>();
}

Node::Node(Node* father, string label, int indexOfString, short indexInString) {
	myFather = father;
	myLabel = string();
	myChildren = vector<Node*>();
	vector<suffixInfo> leafInfo = vector<suffixInfo>();
	leafInfo.push_back(suffixInfo(indexOfString, indexInString));
}


Node::~Node() {
	// TODO Auto-generated destructor stub
}

vector<Node*> Node::getChildren(){
	return myChildren;
}

void Node::setChildren(Node* c1, Node* c2){
	myChildren.clear();
	if(c1->myLabel < c2->myLabel){
		myChildren.push_back(c1);
		myChildren.push_back(c2);
	} else {
		myChildren.push_back(c2);
		myChildren.push_back(c1);
	}
}

string Node::getLabel(){
	return myLabel;
}

void Node::setLabel(string label){
	myLabel = label;
}

Node* Node::getFather(){
	return myFather;
}

vector<Node::suffixInfo> Node::getLeafInfo(){
	return myLeaflInfo;
}
void Node::setLeafInfo(vector<suffixInfo> leafInfo){
	myLeaflInfo = leafInfo;
}
void Node::resetLeaflInfo(){
	myLeaflInfo.clear();
}

void Node::appendToLabel(char c){
	myLabel.append(1, c);
}


