/*
 * GeneralizedSuffixTrees.cpp
 *
 *  Created on: 11/ott/2013
 *      Author: user
 */

#include "GeneralizedSuffixTrees.h"

GeneralizedSuffixTrees::GeneralizedSuffixTrees(string ss[], int& numOfStrings) {
	//Root
	nodes.push_back(new Node());

	for (int i = 0; i < numOfStrings; i++) {
		addString(ss[i]);
	}
}

GeneralizedSuffixTrees::~GeneralizedSuffixTrees() {
	// TODO Auto-generated destructor stub
}

void GeneralizedSuffixTrees::addString(string& s) {
	short lengthOfs = s.length();
	s.append(1, '$');

	for (int i = 0; i < lengthOfs; i++)
		for (int j = 1; j < i + 1; j++){
			CaseInfo ci = findCase(s.substr(j,lengthOfs - j), *nodes.at(0));
		}
}

CaseInfo GeneralizedSuffixTrees::findCase(string s, Node& n) {

	vector<Node*> children = n.getChildren();

	//For all children
	for(vector<Node*>::iterator childrenIt = children.begin(); childrenIt != children.end(); childrenIt++){
		Node child = *(*childrenIt);
		CaseInfo ci = CaseInfo(child.getLabel(),s);
		if(ci.getCaseType() == CaseInfo::IS_SUBSTRING_OF)
			return findCase(s.substr(ci.getIndex()), child);
		else return ci;
	}

	return CaseInfo();
}

