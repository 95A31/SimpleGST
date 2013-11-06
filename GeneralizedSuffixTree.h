/*******************************************************************************
 *     Copyright (c) 2013 95A31.
 * 	
 *     This file is part of GeneralizedSuffixTree.
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
	virtual ~GeneralizedSuffixTree();
	void exportInDotFormat(char* fileName);

	int lastInsertedNode = -1;
	int currentStringIdx = -1;
	short currentCharIdx = -1;

private:

	void initialize(vector<string>& strings);
	void clearStringInfo();

	void addString();
	void extend();

	char getTreeActiveEdge();
	char getActiveEdge();
	short getlabelLength(int node);

	bool walkDown(int node);

	int addNode(int stringIdx, short labelStartIdx, short labelEndInx);
	int addLeaf(int stringIdx, short labelStartIdx, short labelEndInx);

	void setSuffixLink(int node);

	Node getNode(int node);

	string getEdgeString(int node);

	vector<string> strings;
	unordered_map<int, Node> nodes;

	int root;
	int currentNodeID = -1;

	ActivePoint activePoint;
	short currentStringLength = -1;
	short iterationIdx = -1;

};

#endif /* GENERALIZEDSUFFIXTREE_H_ */
