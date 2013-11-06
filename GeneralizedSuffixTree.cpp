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
		clearStringInfo();
		addString();
	}
}

GeneralizedSuffixTree::~GeneralizedSuffixTree() {
}

void GeneralizedSuffixTree::initialize(vector<string>& ss) {
	strings = ss;

	currentNodeID = 0;
	root = addNode(0, 0, 0);

	currentStringIdx = 0;
}

void GeneralizedSuffixTree::clearStringInfo() {
	activePoint.reset();
	currentStringLength = 0;
}

void GeneralizedSuffixTree::addString() {
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
			activePoint.remainder--;
			int newLeaf = addLeaf(currentStringIdx, currentCharIdx, currentStringLength);
			nodes[activePoint.node].children[getActiveEdge()] = newLeaf;
			setSuffixLink(activePoint.node);
		} else {
			int child = nodes[activePoint.node].children[getActiveEdge()];

			if (walkDown(child))
				continue;

			if (strings[nodes[child].stringIdx][nodes[child].labelStartIdx + activePoint.idx] == c) {
				activePoint.idx++;
				setSuffixLink(activePoint.node);
				break;
			}

			int newInnerNode = addNode(nodes[child].stringIdx, nodes[child].labelStartIdx, nodes[child].labelStartIdx + activePoint.idx);
			nodes[activePoint.node].children[getActiveEdge()] = newInnerNode;
			activePoint.remainder--;
			int newLeaf = addLeaf(currentStringIdx, currentCharIdx, currentStringLength);
			nodes[newInnerNode].children[c] = newLeaf;
			nodes[child].labelStartIdx += activePoint.idx;
			nodes[newInnerNode].children[strings[nodes[child].stringIdx][nodes[child].labelStartIdx]] = child;
			setSuffixLink(newInnerNode);
		}

		if (activePoint.node == root && activePoint.idx > 0) {
			activePoint.idx--;
			activePoint.edge = currentCharIdx - activePoint.remainder + 1;
		} else {
			activePoint.node = nodes[activePoint.node].suffixLink > 0 ? nodes[activePoint.node].suffixLink : root;
		}
	}
}

char GeneralizedSuffixTree::getActiveEdge() {
	return strings[currentStringIdx][activePoint.edge];
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
	Node& n = nodes[node];
	return n.labelEndIdx- n.labelStartIdx;
}

int GeneralizedSuffixTree::addLeaf(int stringIdx, short labelStartIdx, short labelEndIn) {
	nodes[currentNodeID] = *(new Node(stringIdx, labelStartIdx, labelEndIn));
	nodes[currentNodeID].addSuffix(currentStringIdx, currentCharIdx - activePoint.remainder);
	return currentNodeID++;
}

int GeneralizedSuffixTree::addNode(int stringIdx, short labelStartIdx, short labelEndIn) {
	nodes[currentNodeID] = *(new Node(stringIdx, labelStartIdx, labelEndIn));
	return currentNodeID++;
}

void GeneralizedSuffixTree::setSuffixLink(int node) {
	if (lastInsertedNode > 0)
		nodes[lastInsertedNode].suffixLink = node;

	lastInsertedNode = node;
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

//BFS
	queue<int> currentQueue;
	queue<int> nextQueue;
	nextQueue.push(root);

//Suffix links without suffix links
	GraphVizOutput << "\t//Suffix tree without suffix links" << endl;
	GraphVizOutput << "\tedge[arrowsize=0.4, fontsize=10, weight=3]" << endl;
	while (not nextQueue.empty()) {
		currentQueue = nextQueue;
		nextQueue = queue<int>();

		while (not currentQueue.empty()) {

			int currentNode = currentQueue.front();
			currentQueue.pop();

			if (nodes[currentNode].children.size() == 0)
				continue;

			for (unordered_map<char, int>::iterator childIt = nodes[currentNode].children.begin(); childIt != nodes[currentNode].children.end(); childIt++) {
				GraphVizOutput << "\t";
				GraphVizOutput << currentNode;
				GraphVizOutput << " -> ";
				GraphVizOutput << ((*childIt).second);
				GraphVizOutput << " [label=\"";
				GraphVizOutput << getEdgeString((*childIt).second);
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
	return strings[nodes[node].stringIdx].substr(nodes[node].labelStartIdx, nodes[node].labelEndIdx - nodes[node].labelStartIdx);
}

