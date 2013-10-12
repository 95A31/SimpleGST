/*
 * Node.h
 *
 *  Created on: 11/ott/2013
 *      Author: user
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <string>

using namespace std;

class Node {
public:
	typedef pair<int,short> suffixInfo;

	Node();
	Node(Node* father, string label,vector<Node*> children);
	Node(Node* father, string label, int indexOfString, short indexInString);
	virtual ~Node();

	vector<Node*> getChildren();
	void setChildren(Node* c1, Node* c2);

	string getLabel();
	void setLabel(string label);

	vector<suffixInfo> getLeafInfo();
	void setLeafInfo(vector<suffixInfo> leafInfo);
	void resetLeaflInfo();

	Node* getFather();
	void appendToLabel(char c);

private:
	Node* myFather;
	string myLabel;
	vector<suffixInfo> myLeaflInfo;
	vector<Node*> myChildren;
};

#endif /* NODE_H_ */
