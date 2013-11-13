/*******************************************************************************
 *     Copyright (c) 2013 95A31.
 * 	
 *     This file is part of SimpleGST.
 *
 *     GeneralizedSuffixTree is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     GeneralizedSuffixTree is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with GeneralizedSuffixTree.  If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************/

#ifndef GENERALIZEDSUFFIXTREE_H_
#define GENERALIZEDSUFFIXTREE_H_

#include <vector>
#include <string>
#include <unordered_map>

#include "ActivePoint.h"
#include "Node.h"

using namespace std;

class GeneralizedSuffixTree {

public:
	GeneralizedSuffixTree(vector<string>& strings);
	GeneralizedSuffixTree(string s);
	virtual ~GeneralizedSuffixTree();
	void exportInDotFormat(char* fileName);
	int addString(string& s);

	int lastInsertedNode = -1;
	int currentStringIdx = -1;
	short currentCharIdx = -1;
	int rootIdx;
	vector<string> strings;
	unordered_map<int, Node> nodes;
	string getEdgeString(int node);
	string getEdgeString(Node& node);
	string getEdgeStringWithTerm(Node& node, bool withTerm);
	char getLastChar(int node);
	char getLastChar(Node& n);
	string getEdgeStringWithTerm(int node, bool withTerm);

private:

	void initialize(vector<string>& strings);
	void clearStringInfo();

	void addNextString();
	void extend();

	char getTreeActiveEdge();
	char getActiveEdge();
	Node getActiveNode();
	short getlabelLength(int node);

	bool walkDown(int node);

	int addNode(int stringIdx, short labelStartIdx, short labelEndInx);
	int addLeaf(int stringIdx, short labelStartIdx, short labelEndInx);

	void setSuffixLink(int node);

	int currentNodeID = -1;

	ActivePoint activePoint;
	short currentStringLength = -1;

};

#endif /* GENERALIZEDSUFFIXTREE_H_ */
