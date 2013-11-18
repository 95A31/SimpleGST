/*******************************************************************************
 *     Copyright (c) 2013 95A31.
 * 	
 *     This file is part of SimpleGST.
 *
 *     SimpleGST is free software: you can redistribute it and/or modify
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

#include "Tasks.h"

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

Tasks::Tasks(GeneralizedSuffixTree* t) {
	gst = t;
}

Tasks::~Tasks() {
	// TODO Auto-generated destructor stub
}

void Tasks::Task1() {
	string adapter = "TGGAATTCTCGGGTGCCAAGGAACTCCAGTCACACAGTGATCTCGTATGCCGTCTTCTGCTTG$";

	Node* currentNode = &gst->nodes[gst->rootIdx];

	for (short currentCharIdx = 0; currentCharIdx < (short) adapter.length(); currentCharIdx++) {

		Node* children = &gst->nodes[currentNode->children[adapter[currentCharIdx]]];

		if (currentNode->children.count('$') > 0 and currentNode != &gst->nodes[gst->rootIdx])
			addToResultsT1(&gst->nodes[currentNode->children['$']], currentCharIdx);

		if (gst->strings[children->stringIdx][children->labelEndIdx] == '$') {
			addToResultsT1(children, currentCharIdx);
			break;
		}

		//Walk down
		if (gst->getEdgeString(*children).compare(adapter.substr(currentCharIdx, children->getLabelLength())) == 0) {
			currentNode = children;
			currentCharIdx += children->getLabelLength() - 1;
			continue;
		}

		break;
	}

	cout << "Task 1:" << endl;
	cout << " Length\tCount" << endl;
	for (unordered_map<short, int>::iterator resIt = resultsT1.begin(); resIt != resultsT1.end(); resIt++)
		cout << " " << (*resIt).first << "\t" << (*resIt).second << endl;
}

void Tasks::addToResultsT1(Node* n, short adapterIdx) {
	for (vector<Node::suffix>::iterator suffIt = n->suffixes.begin(); suffIt != n->suffixes.end(); suffIt++) {
		short trimmedLength = (*suffIt).second;
		if (resultsT1.count(trimmedLength) > 0)
			resultsT1[trimmedLength]++;
		else
			resultsT1[trimmedLength] = 1;

	}
}

void Tasks::addToResultsT1(int nodeID, short adapterLength) {
	addToResultsT1(&gst->nodes[nodeID], adapterLength);
}
