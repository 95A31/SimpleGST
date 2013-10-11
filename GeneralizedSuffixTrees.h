/*
 * GeneralizedSuffixTrees.h
 *
 *  Created on: 11/ott/2013
 *      Author: user
 */

#ifndef GENERALIZEDSUFFIXTREES_H_
#define GENERALIZEDSUFFIXTREES_H_

#include <vector>
#include <string>

#include "Node.h"
#

class GeneralizedSuffixTrees {
public:
	GeneralizedSuffixTrees(string ss[], int numOfStrings);
	virtual ~GeneralizedSuffixTrees();

	void addString(string s);

private:
	vector<Node*> nodes;
};

#endif /* GENERALIZEDSUFFIXTREES_H_ */
