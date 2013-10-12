/*
 * GeneralizedSuffixTrees.h
 *
 *  Created on: 11/ott/2013
 *      Author: user
 */

#ifndef GENERALIZEDSUFFIXTREES_H_
#define GENERALIZEDSUFFIXTREES_H_

#include <vector>

#include "Node.h"
#include "CaseInfo.h"
#include "Utils.h"

using namespace std;

class GeneralizedSuffixTrees {
public:
	GeneralizedSuffixTrees(string ss[], int& numOfStrings);
	virtual ~GeneralizedSuffixTrees();

	void addString(string& s);
	void addSuffix(string s, Node& n);

	void handleCommonPrefixCase(Node&n, short& index, string& suffix);
	void handleEqualCase(Node&n, char c);
	void handleDifferentCase(Node&n, string& s);
private:
	short suffixIndex;
	unsigned int myNumOfStrings;
	vector<Node*> nodes;
};

#endif /* GENERALIZEDSUFFIXTREES_H_ */
