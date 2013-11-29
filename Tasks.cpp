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
#include <algorithm>
#include <vector>
#include <chrono>
#include <climits>
#include <omp.h>

using namespace std;

Tasks::Tasks(GeneralizedSuffixTree* t) {
	gst = t;
	auxGst = nullptr;
}

Tasks::~Tasks() {
	// TODO Auto-generated destructor stub
}

void Tasks::Task1() {
	cout << endl << endl;

	resultsT1T2.clear();

	auto t1 = chrono::high_resolution_clock::now();

	trimAndLengthDist();

	auto t2 = chrono::high_resolution_clock::now();
	auto elapsed = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

	cout << "Task 1: (" << elapsed.count() << " ms)" << endl;
	cout << " Length\tCount" << endl;
	for (pair<short, int> result : resultsT1T2)
		cout << " " << result.first << "\t" << result.second << endl;
}

void Tasks::trimAndLengthDist() {

	Node* currentNode = &gst->nodes[gst->rootIdx];

	for (short currentCharIdx = 0; currentCharIdx < (short) adapter.length(); currentCharIdx++) {

		Node* children = &gst->nodes[currentNode->children[adapter[currentCharIdx]]];

		if (currentNode->children.count('$') > 0 and currentNode != &gst->nodes[gst->rootIdx])
			addToResultsT1T2(&gst->nodes[currentNode->children['$']]);

		//Walk down
		short numOfMismatches = countMismatches(children->stringIdx, children->labelStartIdx, children->labelEndIdx, currentCharIdx);

		if (numOfMismatches == 0) {
			currentNode = children;
			currentCharIdx += children->getLabelLength() - 1;
			continue;

		} else if (numOfMismatches == -1) {
			addToResultsT1T2(children);
			break;
		}

		break;
	}
}

void Tasks::addToResultsT1T2(Node* n) {
	for (Node::suffix suffix : n->suffixes) {
		short trimmedLength = suffix.second;

		if (resultsT1T2.count(trimmedLength) > 0)
			resultsT1T2[trimmedLength]++;
		else
			resultsT1T2[trimmedLength] = 1;
	}
}

void Tasks::Task2() {
	cout << endl << endl;

	resultsT1T2.clear();

	//10% -> 5
	auto t1 = chrono::high_resolution_clock::now();

	searchWithMissmatches(0, 5, &gst->nodes[gst->rootIdx]);

	auto t2 = chrono::high_resolution_clock::now();
	auto elapsed = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

	cout << "Task 2a: (" << elapsed.count() << " ms)" << endl;
	cout << " Length\tCount" << endl;
	for (pair<short, int> result : resultsT1T2)
		cout << " " << result.first << "\t" << result.second << endl;
	cout << endl;

	resultsT1T2.clear();
	//25% -> 13
	t1 = chrono::high_resolution_clock::now();

	searchWithMissmatches(0, 13, &gst->nodes[gst->rootIdx]);

	t2 = chrono::high_resolution_clock::now();
	elapsed = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

	cout << "Task 2b: (" << elapsed.count() << " ms)" << endl;
	cout << " Length\tCount" << endl;
	for (pair<short, int> result : resultsT1T2)
		cout << " " << result.first << "\t" << result.second << endl;
	cout << endl;

}

void Tasks::searchWithMissmatches(short currentCharIdx, short currentErr, Node* currentNode) {

	//Deep First Visit
	if (currentCharIdx >= (short) adapter.length())
		return;

	for (pair<char, int> childEntry : currentNode->children) {

		Node* child = &gst->nodes[childEntry.second];

		if (currentNode->children.count('$') > 0 and currentNode != &gst->nodes[gst->rootIdx])
			addToResultsT1T2(&gst->nodes[currentNode->children['$']]);

		short numOfMismatches = countMismatches(child->stringIdx, child->labelStartIdx, child->labelEndIdx, currentCharIdx);

		if (numOfMismatches > currentErr or numOfMismatches == -2)
			continue;
		else if (numOfMismatches == -1 and adapter[currentCharIdx] == '$') {
			addToResultsT1T2(child);
			continue;
		}

		searchWithMissmatches(currentCharIdx + child->getLabelLength(), currentErr - numOfMismatches, child);
	}

	return;
}

short Tasks::countMismatches(int childrenStringIdx, short childrenLabelStartIdx, short childrenLabelEndIdx, short currentCharIdx) {
	short numOfMismatches = 0;
	char* a = &gst->strings[childrenStringIdx][childrenLabelStartIdx];
	char* b = &adapter[currentCharIdx];

	for (short offset = 0; offset <= childrenLabelEndIdx - childrenLabelStartIdx; offset++) {
		if (*(a + offset) == '$')
			//Path label shorter than adapter
			return -1;

		else if (*(b + offset) == '$')
			//Adapter shorter than path label
			return -2;

		numOfMismatches += (a + offset) == (b + offset);
	}

	return numOfMismatches;
}

void Tasks::Task3() {
	cout << endl << endl;

	auto t1 = chrono::high_resolution_clock::now();

	collectMostFrequenSuffixes("", &gst->nodes[gst->rootIdx]);

	auto t2 = chrono::high_resolution_clock::now();
	auto elapsed = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

	cout << "Candidate adapter list (the strings are reversed!):" << endl;
	printStringsInfo(MAX_SUFFIXES);
	cout << endl;

	cout << "Task 3a: (" << elapsed.count() << " ms)" << endl;
	cout << "Insert the candidate adapter (just copy/paste):" << endl;
	cin >> adapter;
	adapter = string(adapter.rbegin(), adapter.rend());
	adapter.push_back('$');
	resultsT1T2.clear();

	t1 = chrono::high_resolution_clock::now();

	trimAndSave();

	t2 = chrono::high_resolution_clock::now();
	elapsed = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

	cout << endl;
	cout << "Task 3b: (" << elapsed.count() << " ms)" << endl;
	cout << " Length\tCount" << endl;
	for (pair<short, int> result : resultsT1T2)
		cout << " " << result.first << "\t" << result.second << endl;
}

void Tasks::addToResultsT3(Node* n) {
	for (vector<Node::suffix>::iterator suffIt = n->suffixes.begin(); suffIt != n->suffixes.end(); suffIt++) {

		auxStruct2T3[suffIt->first].insert(suffIt->second);

		short trimmedLength = (*suffIt).second;
		if (resultsT1T2.count(trimmedLength) > 0)
			resultsT1T2[trimmedLength]++;
		else
			resultsT1T2[trimmedLength] = 1;
	}
}

void Tasks::addToResultsT3(string label, Node* n) {

	label.pop_back();
	label = string(label.rbegin(), label.rend());

	int multiplicity = n->suffixes.size();

	auxStructT3[multiplicity].insert(label);
}

void Tasks::collectMostFrequenSuffixes(string label, Node* currentNode) {

	//Deep First Visit
	if (currentNode->children.empty()) {
		addToResultsT3(label, currentNode);
		return;
	}

	string alphabetSimbols = "$ACGT";

	for (char c : alphabetSimbols) {
		if (currentNode->children.count(c) > 0) {
			Node * child = &gst->nodes[currentNode->children[c]];
			string childLabel = label;
			childLabel.append(gst->getEdgeString(*child));
			collectMostFrequenSuffixes(childLabel, child);
		}
	}

	return;
}

void Tasks::trimAndSave() {

	Node* currentNode = &gst->nodes[gst->rootIdx];

	for (short currentCharIdx = 0; currentCharIdx < (short) adapter.length(); currentCharIdx++) {

		Node* children = &gst->nodes[currentNode->children[adapter[currentCharIdx]]];

		if (currentNode->children.count('$') > 0 and currentNode != &gst->nodes[gst->rootIdx])
			addToResultsT3(&gst->nodes[currentNode->children['$']]);

		//Walk down
		short numOfMismatches = countMismatches(children->stringIdx, children->labelStartIdx, children->labelEndIdx, currentCharIdx);

		if (numOfMismatches == 0) {
			currentNode = children;
			currentCharIdx += children->getLabelLength() - 1;
			continue;

		} else if (numOfMismatches == -1) {
			addToResultsT3(children);
			break;
		}

		break;
	}
}

void Tasks::Task4() {
	cout << endl << endl;

	vector<string> ss;

	for (pair<int, set<short>> entry : auxStruct2T3)
		for (short length : entry.second)
			ss.push_back(gst->strings[entry.first].substr(0, length));

	auxGst = new GeneralizedSuffixTree(ss);
	cout << endl;

	auxStructT3.clear();

	auto t1 = chrono::high_resolution_clock::now();

	collectDuplicates(&auxGst->nodes[gst->rootIdx]);

	auto t2 = chrono::high_resolution_clock::now();
	auto elapsed = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

	cout << "Task 4a: (" << elapsed.count() << " ms)" << endl;
	printStringsInfo(MAX_DUPLICATES);

	bool skipSearchWithMissmatches = true;

	while (true) {
		cout << endl;
		cin.clear() ;
		cout << "Do you want skip search with mismatches? [y]" << endl;
		string a;
		cin >> a;
		if (a.empty() or a.compare("y") == 0)
			break;

		if (a.compare("n") == 0) {
			skipSearchWithMissmatches = false;
			break;
		}
	}

	if (not skipSearchWithMissmatches) {

		auxStructT3.clear();

		t1 = chrono::high_resolution_clock::now();

		//10% => 5
		int numOfStrings = auxGst->strings.size();
		int numOfSearchedStrings = 0;
#pragma omp parallel for
		for (int i = 0; i < numOfStrings; i++) {
			searchWithMissmatchesAndSave(0, 5, &auxGst->nodes[auxGst->rootIdx], auxGst->strings[i]);
#pragma omp atomic
			numOfSearchedStrings++;

			if (numOfSearchedStrings % 1000 == 0) {
				cout << "Task 4b: " << floor(((float) numOfSearchedStrings / (float) numOfStrings) * 100) << "%\t\r";
				cout.flush();
			}

		}

		t2 = chrono::high_resolution_clock::now();
		elapsed = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

		cout << "Task 4b: (" << elapsed.count() << " ms)" << endl;
		printStringsInfo(MAX_DUPLICATES_MISSMATCH);

		auxStructT3.clear();

		t1 = chrono::high_resolution_clock::now();

		//20% => 10
		numOfSearchedStrings = 0;
#pragma omp parallel for
		for (int i = 0; i < numOfStrings; i++) {
			searchWithMissmatchesAndSave(0, 10, &auxGst->nodes[auxGst->rootIdx], auxGst->strings[i]);
#pragma omp atomic
			numOfSearchedStrings++;

			if (numOfSearchedStrings % 1000 == 0) {
				cout << "Task 4c: " << floor(((float) numOfSearchedStrings / (float) numOfStrings) * 100) << "%\t\r";
				cout.flush();
			}

		}

		t2 = chrono::high_resolution_clock::now();
		elapsed = chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

		cout << "Task 4c: (" << elapsed.count() << " ms)" << endl;
		printStringsInfo(MAX_DUPLICATES_MISSMATCH);

	}

	auxStructT3.clear();

	t1 = chrono::high_resolution_clock::now();

	findSharedPrefix("", 10, &auxGst->nodes[auxGst->rootIdx]);

	cout << "Task 4d: (" << elapsed.count() << " ms)" << endl;
	printStringsInfo(MAX_DUPLICATES_COMM_PREFIX);

	auxStructT3.clear();

	t1 = chrono::high_resolution_clock::now();

	findSharedPrefix("", 15, &auxGst->nodes[auxGst->rootIdx]);

	cout << "Task 4e: (" << elapsed.count() << " ms)" << endl;
	printStringsInfo(MAX_DUPLICATES_COMM_PREFIX);

	auxStructT3.clear();

	t1 = chrono::high_resolution_clock::now();

	findSharedPrefix("", 20, &auxGst->nodes[auxGst->rootIdx]);

	cout << "Task 4f: (" << elapsed.count() << " ms)" << endl;
	printStringsInfo(MAX_DUPLICATES_COMM_PREFIX);
}

void Tasks::addToResultsT4(Node* n) {
	int multiplicity = n->suffixes.size();

	int stringIdx = -1;

	for (auto suffix : n->suffixes) {
		if (suffix.second > 0)
			multiplicity--;
		else
			stringIdx = suffix.first;
	}
	if (multiplicity > 1) {

		string label = auxGst->strings[stringIdx];
		label.pop_back();

#pragma omp critical (results3)
		{
			auxStructT3[multiplicity].insert(label);
		}
	}
}

void Tasks::addToResultsT4(Node* n, string label) {
	int multiplicity = n->suffixes.size();

	for (auto suffix : n->suffixes)
		if (suffix.second > 0)
			multiplicity--;

	if (multiplicity > 1) {

		label.pop_back();

#pragma omp critical (results3)
		{
			auxStructT3[multiplicity].insert(label);
		}
	}
}

void Tasks::collectDuplicates(Node* currentNode) {

	//Deep First Visit
	if (currentNode->children.empty()) {
		addToResultsT4(currentNode);
		return;
	}

	string alphabetSimbols = "$ACGT";

	for (char c : alphabetSimbols) {
		if (currentNode->children.count(c) > 0) {
			Node * child = &auxGst->nodes[currentNode->children[c]];
			collectDuplicates(child);
		}
	}

	return;
}

void Tasks::searchWithMissmatchesAndSave(short currentCharIdx, short currentErr, Node* currentNode, string& label) {

	//Deep First Visit
	if (currentCharIdx >= (short) label.length())
		return;

	string alphabetSimbols = "$ACGT";

	for (char c : alphabetSimbols) {
		if (currentNode->children.count(c) > 0) {
			Node* child = &auxGst->nodes[currentNode->children[c]];

			if (currentNode->children.count('$') > 0)
				addToResultsT4(&auxGst->nodes[currentNode->children['$']], label);

			short numOfMismatches = countMismatches(child->stringIdx, child->labelStartIdx, child->labelEndIdx, currentCharIdx);

			if (numOfMismatches > currentErr or numOfMismatches == -2)
				continue;
			else if (numOfMismatches == -1 and label[currentCharIdx] == '$') {
				addToResultsT4(child, label);
				continue;
			}

			searchWithMissmatchesAndSave(currentCharIdx + child->getLabelLength(), currentErr - numOfMismatches, child, label);
		}
	}

	return;
}

void Tasks::findSharedPrefix(string label, short labelLength, Node* currentNode) {

//Deep First Visit
	if (currentNode->children.empty()) {
		addToResultsT4(currentNode, label);
		return;
	}

	string alphabetSimbols = "$ACGT";

#pragma omp parallel for
	for (short i = 0; i < (short) alphabetSimbols.length(); i++) {

		char c = alphabetSimbols[i];
		if (currentNode->children.count(c) > 0) {
			Node* child = &auxGst->nodes[currentNode->children[c]];

			string childLabel = label;
			if ((short) childLabel.length() < labelLength) {
				childLabel.append(auxGst->getEdgeString(*child));
				childLabel = childLabel.substr(0, labelLength);
			}
			findSharedPrefix(childLabel, labelLength, child);
		}
	}
}

void Tasks::printStringsInfo(const int& maxNumOfSeqs) {
	cout << "Multiplicity String" << endl;
	int count = 0;

	orderedByFrequencyAuxStructT3 = new map<int, set<string>>(auxStructT3.begin(), auxStructT3.end());

	for (map<int, set<string>>::reverse_iterator entryIt = orderedByFrequencyAuxStructT3->rbegin(); entryIt != orderedByFrequencyAuxStructT3->rend(); entryIt++)
		if (count < maxNumOfSeqs)
			for (set<string>::iterator stringIt = (*entryIt).second.begin(); stringIt != (*entryIt).second.end(); stringIt++)
				if (count < maxNumOfSeqs) {
					printf("%12d %s\n", (*entryIt).first, (*stringIt).c_str());
					count++;
				}
	cout << endl;

	orderedByFrequencyAuxStructT3->clear();
}
