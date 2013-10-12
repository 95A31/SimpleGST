/*
 * GeneralizedSuffixTrees.cpp
 *
 *  Created on: 11/ott/2013
 *      Author: user
 */

#include "GeneralizedSuffixTrees.h"

using namespace Utils;

GeneralizedSuffixTrees::GeneralizedSuffixTrees(string ss[], int& numOfStrings) {
	//Root
	nodes.push_back(new Node());

	for (int i = 0; i < numOfStrings; i++) {
		addString(ss[i]);
		myNumOfStrings++;
	}
}

GeneralizedSuffixTrees::~GeneralizedSuffixTrees() {
	// TODO Auto-generated destructor stub
}

void GeneralizedSuffixTrees::addString(string& s) {
	short lengthOfs = s.length();
	s.append(1, '$');

	for (suffixIndex = 0; suffixIndex < lengthOfs; suffixIndex++)
		for (int j = 1; j < suffixIndex; j++)
			addSuffix(s.substr(j, suffixIndex - j), *nodes.at(0));
}

void GeneralizedSuffixTrees::addSuffix(string s, Node& n) {

	vector<Node*> children = n.getChildren();

	//For all children
	for (vector<Node*>::iterator childrenIt = children.begin(); childrenIt != children.end(); childrenIt++) {
		Node child = *(*childrenIt);

		pair<strRapport, short> rapportInfo = stringRapport(child.getLabel(), s);

		if (rapportInfo.first == strRapport::COMMON_PREFIX) {
			handleCommonPrefixCase(child, rapportInfo.second, s);

		} else if (rapportInfo.first == strRapport::SUPERSTRING) {
			if (child.getLabel()[rapportInfo.second + 1] != s[rapportInfo.second + 1]) {
				string tmpStr = s.substr(rapportInfo.second + 1, 1);
				handleCommonPrefixCase(child, rapportInfo.second, tmpStr);
			}
		} else if (rapportInfo.first == strRapport::SUBSTRING) {
			addSuffix(s.substr(rapportInfo.second), n);
		} else if (rapportInfo.first == strRapport::EQUAL) {
			if (child.getChildren().empty()){
				child.appendToLabel(s[s.length()]);
			} else
				handleEqualCase(child,s[s.length()]);
		} else if (rapportInfo.first == strRapport::DIFFERENT) {
			handleDifferentCase(child,s);
		}
	}
}

void GeneralizedSuffixTrees::handleCommonPrefixCase(Node& n, short& index, string& suffix) {
	Node newNode = Node(&n, n.getLabel().substr(index), n.getChildren());

	if(n.getChildren().empty())
		newNode.setLeafInfo(n.getLeafInfo());

	nodes.push_back(&newNode);

	Node newLeafNode = Node(&n, suffix.substr(index), myNumOfStrings, suffixIndex);
	nodes.push_back(&newLeafNode);

	n.setLabel(n.getLabel().substr(0, index));
	n.setChildren(&newNode, &newLeafNode);
	n.resetLeaflInfo();
}

void GeneralizedSuffixTrees::handleEqualCase(Node&n, char c) {

	vector<Node*> children = n.getChildren();

	for (vector<Node*>::iterator childrenIt = children.begin(); childrenIt != children.end(); childrenIt++) {
			Node child = *(*childrenIt);

			if(child.getLabel()[0] == c)
				return;
	}

	Node newLeafNode = Node(&n, string(1,c), myNumOfStrings, suffixIndex);
	nodes.push_back(&newLeafNode);
}

void GeneralizedSuffixTrees::handleDifferentCase(Node&n, string& s) {
	Node newLeafNode = Node(&n, s, myNumOfStrings, suffixIndex);
	nodes.push_back(&newLeafNode);

	//Ordered children
	vector<Node*> children = n.getChildren();
	for (vector<Node*>::iterator childrenIt = children.begin(); childrenIt != children.end(); childrenIt++) {
				Node child = *(*childrenIt);

				if(child.getLabel() > s){
					children.insert(childrenIt - 1,&newLeafNode);
					return;
				}
		}

	children.push_back(&newLeafNode);
}



