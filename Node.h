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
	Node();
	virtual ~Node();

	vector<Node*> getChildren();
	string getLabel();

private:
	Node* father;
	string label;
	vector<Node*> children;
};

#endif /* NODE_H_ */
