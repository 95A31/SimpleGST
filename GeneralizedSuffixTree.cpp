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

// This algorithm is a revision of this one:
// http://stackoverflow.com/questions/9452701/ukkonens-suffix-tree-algorithm-in-plain-english/9513423#9513423
#include "GeneralizedSuffixTree.h"

#include <queue>
#include <fstream>
#include <iostream>

using namespace std;

GeneralizedSuffixTree::GeneralizedSuffixTree(vector<string>& strings) {

	initialize(strings);

	for (int i = 0; i < (int) strings.size(); i++) {
		cout << "Adding string " << currentStringIdx << "\r";
		clearStringInfo();
		addNextString();
	}
	cout << "Adding string " << currentStringIdx << " [OK]" << endl;
}

GeneralizedSuffixTree::GeneralizedSuffixTree(string s) {

	strings.push_back(s);

	initialize(strings);

	clearStringInfo();
	addNextString();
}

GeneralizedSuffixTree::~GeneralizedSuffixTree() {
}

void GeneralizedSuffixTree::initialize(vector<string>& ss) {
	strings = ss;

	currentNodeID = 0;
	rootIdx = addNode(0, 0, 0);

	currentStringIdx = 0;
}

void GeneralizedSuffixTree::clearStringInfo() {
	activePoint.reset();
	currentStringLength = 0;
}

int GeneralizedSuffixTree::addString(string& s) {
	strings.push_back(s);

	clearStringInfo();
	addNextString();

	return currentStringIdx - 1;
}

void GeneralizedSuffixTree::addNextString() {
	strings[currentStringIdx].push_back('$');
	currentStringLength = (short) strings[currentStringIdx].length();

	for (currentCharIdx = 0; currentCharIdx < currentStringLength; currentCharIdx++)
		extend();

	currentStringIdx++;
}

void GeneralizedSuffixTree::extend() {

	char c = strings[currentStringIdx][currentCharIdx];

	lastInsertedNode = 0;
	activePoint.remainder++;

	while (activePoint.remainder > 0) {

		if (activePoint.idx == 0)
			activePoint.edge = currentCharIdx;

		if (nodes[activePoint.node].children.count(getActiveEdge()) == 0) {
			int newLeaf = addLeaf(currentStringIdx, currentCharIdx, currentStringLength - 1);
			nodes[activePoint.node].children[getActiveEdge()] = newLeaf;
			setSuffixLink(activePoint.node);
		} else {

			if (activePoint.node == rootIdx){
					activePoint.edge = currentCharIdx - activePoint.remainder + 1;
					activePoint.idx = activePoint.remainder - 1;
			}

			int childID = nodes[activePoint.node].children[getActiveEdge()];
			Node& child = nodes[childID];

			if (walkDown(childID))
				continue;


			if (strings[child.stringIdx][child.labelStartIdx + activePoint.idx] == c) {
				if (c != '$') {
					activePoint.idx++;
					setSuffixLink(activePoint.node);
					break;
				} else
					child.addSuffix(currentStringIdx, currentCharIdx - (activePoint.remainder - 1));

			} else {
				int newInnerNode = addNode(child.stringIdx, child.labelStartIdx, child.labelStartIdx + activePoint.idx - 1);
				nodes[activePoint.node].children[getActiveEdge()] = newInnerNode;
				int newLeaf = addLeaf(currentStringIdx, currentCharIdx, currentStringLength - 1);
				nodes[newInnerNode].children[c] = newLeaf;
				child.labelStartIdx += activePoint.idx;
				nodes[newInnerNode].children[strings[child.stringIdx][child.labelStartIdx]] = childID;
				setSuffixLink(newInnerNode);
			}
		}

		activePoint.remainder--;

		if (activePoint.node == rootIdx && activePoint.idx > 0) {
			activePoint.idx--;
			activePoint.edge = currentCharIdx - activePoint.remainder + 1;
		} else {
			activePoint.node = nodes[activePoint.node].suffixLink > 0 ? nodes[activePoint.node].suffixLink : rootIdx;

		}
	}
}

char GeneralizedSuffixTree::getActiveEdge() {
	return strings[currentStringIdx][activePoint.edge];
}

Node GeneralizedSuffixTree::getActiveNode() {
	return nodes[activePoint.node];
}

bool GeneralizedSuffixTree::walkDown(int node) {
	if (activePoint.idx >= getlabelLength(node)) {
		activePoint.edge += getlabelLength(node);
		activePoint.idx -= getlabelLength(node);
		activePoint.node = node;
		return true;
	}
	return false;
}

short GeneralizedSuffixTree::getlabelLength(int node) {
	return nodes[node].getLabelLength();
}

int GeneralizedSuffixTree::addLeaf(int stringIdx, short labelStartIdx, short labelEndIdx) {
	nodes[currentNodeID] = *(new Node(stringIdx, labelStartIdx, labelEndIdx));
	nodes[currentNodeID].addSuffix(stringIdx, currentCharIdx - (activePoint.remainder - 1));
	return currentNodeID++;
}

int GeneralizedSuffixTree::addNode(int stringIdx, short labelStartIdx, short labelEndIdx) {
	nodes[currentNodeID] = *(new Node(stringIdx, labelStartIdx, labelEndIdx));
	return currentNodeID++;
}

void GeneralizedSuffixTree::setSuffixLink(int node) {
	if (lastInsertedNode > 0)
		nodes[lastInsertedNode].suffixLink = node;

	lastInsertedNode = node;
}

char GeneralizedSuffixTree::getLastChar(int nodeID) {
	return getLastChar(nodes[nodeID]);
}
char GeneralizedSuffixTree::getLastChar(Node& n) {
	return strings[n.stringIdx][n.labelEndIdx];
}

void GeneralizedSuffixTree::exportInDotFormat(char* filename) {
	ofstream GraphVizOutput;
	GraphVizOutput.open(filename);

	GraphVizOutput << "/***********************************************************************************" << endl;
	GraphVizOutput << " * This file was generated by SimpleGST, a Simple C++ implementation of Generalized " << endl;
	GraphVizOutput << " * Suffix Tree using Ukonnen'filename algorithm." << endl;
	GraphVizOutput << " *" << endl;
	GraphVizOutput << " * Copyright (c) 2013 95A31" << endl;
	GraphVizOutput << " *" << endl;
	GraphVizOutput << " * Source: https://github.com/95A31/SimpleGST" << endl;
	GraphVizOutput << " **********************************************************************************/" << endl;
	GraphVizOutput << endl;
	GraphVizOutput << endl;

	GraphVizOutput << "digraph G {" << endl;
	GraphVizOutput << "\trankdir=LR;" << endl;
	GraphVizOutput << "\tnode[shape=circle, style=filled, fillcolor=white, width=0.05, fixedsize=true, label=\"\"]" << endl;
	GraphVizOutput << endl;
	GraphVizOutput << endl;

	//BFV
	queue<int> currentQueue;
	queue<int> nextQueue;
	nextQueue.push(rootIdx);

	//Suffix links without suffix links
	GraphVizOutput << "\t//Suffix tree without suffix links" << endl;
	GraphVizOutput << "\tedge[arrowsize=0.4, fontsize=10, weight=3]" << endl;
	while (not nextQueue.empty()) {
		currentQueue = nextQueue;
		nextQueue = queue<int>();

		while (not currentQueue.empty()) {

			int currentNode = currentQueue.front();
			currentQueue.pop();

			for (unordered_map<char, int>::iterator childIt = nodes[currentNode].children.begin(); childIt != nodes[currentNode].children.end(); childIt++) {
				GraphVizOutput << "\t";
				GraphVizOutput << currentNode;
				GraphVizOutput << " -> ";
				GraphVizOutput << ((*childIt).second);
				GraphVizOutput << " [label=\"";
				GraphVizOutput << getEdgeStringWithTerm((*childIt).second, nodes[(*childIt).second].children.empty());
				GraphVizOutput << "\"]" << endl;
				nextQueue.push((*childIt).second);
			}
		}
	}
	GraphVizOutput << endl;
	GraphVizOutput << endl;

//Suffix links
	GraphVizOutput << "\t//Suffix  links" << endl;
	GraphVizOutput << "\tedge[arrowsize=0.4,fontsize=10, style=dashed, weight=1]" << endl;

	for (unordered_map<int, Node>::iterator nodeIt = nodes.begin(); nodeIt != nodes.end(); nodeIt++) {
		if ((*nodeIt).second.suffixLink > 0) {
			GraphVizOutput << "\t";
			GraphVizOutput << (*nodeIt).first;
			GraphVizOutput << " -> ";
			GraphVizOutput << (*nodeIt).second.suffixLink << endl;
		}
	}

	GraphVizOutput << "}";
	GraphVizOutput.close();
}

string GeneralizedSuffixTree::getEdgeString(int node) {
	return getEdgeStringWithTerm(nodes[node], true);
}

string GeneralizedSuffixTree::getEdgeString(Node& node) {
	return getEdgeStringWithTerm(node, true);
}

string GeneralizedSuffixTree::getEdgeStringWithTerm(int node, bool withTerm) {
	return getEdgeStringWithTerm(nodes[node], true);
}

string GeneralizedSuffixTree::getEdgeStringWithTerm(Node& node, bool withTerm) {
	if (node.labelStartIdx == node.labelEndIdx)
		return strings[node.stringIdx].substr(node.labelStartIdx, (withTerm ? 1 : 0));
	else
		return strings[node.stringIdx].substr(node.labelStartIdx, (node.labelEndIdx - node.labelStartIdx) + (withTerm ? 1 : 0));
}

