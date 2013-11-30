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

#ifndef TASKS_H_
#define TASKS_H_

#include <map>
#include <set>

#include "GeneralizedSuffixTree.h"
#include "Node.h"

class Tasks {

public:
	Tasks(GeneralizedSuffixTree* gst);
	virtual ~Tasks();

	GeneralizedSuffixTree* gst;
	string adapter = "TGGAATTCTCGGGTGCCAAGGAACTCCAGTCACACAGTGATCTCGTATGCCGTCTTCTGCTTG$";

	unordered_map<short, int> resultsT1T2;	//<length, multiplicity>
	unordered_map<int, set<string>> auxStructT3; //<multiplicity,string>
	map<int, set<string>>* orderedByFrequencyAuxStructT3;

	unordered_map<int, set<short>> auxStruct2T3;	//<String Idex, Trimmed length>
	GeneralizedSuffixTree* auxGst;

	const int MAX_SUFFIXES = 400;
	const int MAX_DUPLICATES = 10;
	const int MAX_DUPLICATES_MISSMATCH = 10;
	const int MAX_DUPLICATES_COMM_PREFIX  = 10;

	void Task1();
	void trimAndLengthDist();
	void addToResultsT1T2(Node* n);

	void Task2();
	void searchWithMissmatches(short currentCharIdx, short currentErr, Node* currentNode);
	short countMismatches(GeneralizedSuffixTree* t, Node* n, short currentCharIdx);

	void Task3();
	void addToResultsT3(Node* n);
	void addToResultsT3(string label, Node* n);
	void collectMostFrequenSuffixes(string label, Node* currentNode);
	void trimAndSave();

	void Task4();
	void addToResultsT4(Node* n);
	void addToResultsT4(Node* n, string label);
	void collectDuplicates(Node* currentNode);
	void searchWithMissmatchesAndSave(short currentCharIdx, short currentErr, Node* currentNode, string& label);
	void findSharedPrefix(string label, short labelLength, Node* currentNode);

	void printStringsInfo(const int& maxNumOfSeqs);


};

#endif /* TASKS_H_ */
