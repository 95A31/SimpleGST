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

using namespace std;

class GeneralizedSuffixTrees {
public:
	GeneralizedSuffixTrees(string ss[], int& numOfStrings);
	virtual ~GeneralizedSuffixTrees();

	void addString(string& s);
	CaseInfo findCase(string s, Node& n);

private:
	vector<Node*> nodes;
};

#endif /* GENERALIZEDSUFFIXTREES_H_ */
