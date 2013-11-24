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
#include <climits>
#include <set>

#include "GeneralizedSuffixTree.h"
#include "Node.h"

#define MAX_SUFFIXES 10000
#define MAX_DUPLICATES 10
#define MAX_DUPLICATES_MISSMATCH 10
#define MAX_DUPLICATES_COMM_PREFIX 10

class Tasks {
public:
	Tasks(GeneralizedSuffixTree* gst);
	virtual ~Tasks();

	GeneralizedSuffixTree* gst;
	string adapter = "TGGAATTCTCGGGTGCCAAGGAACTCCAGTCACACAGTGATCTCGTATGCCGTCTTCTGCTTG$";

	unordered_map<short, int> resultsT1T2;	//<length, multiplicity>
	map<string, int> resultsT3; //<string, multiplicity>
	map<int, set<string>> auxStructT3; //<multiplicity,string>

	unordered_map<int, set<short>> auxStruct2T3;	//<String Idex, Trimmed length>
	GeneralizedSuffixTree* auxGst;
	int counter = 0;

	void Task1();
	void trimAndLengthDist();
	void addToResultsT1T2(Node* n);

	void Task2();
	void searchWithMissmatches(short currentCharIdx, short currentErr, Node* currentNode);
	short countMismatches(int childrenStringIdx, short childrenLabelStartIdx, short childrenLabelEndIdx, short currentCharIdx);

	void Task3();
	void addToResultsT3(Node* n);
	void addToResultsT3(string label, Node* n);
	void collectMostFrequenSuffixes(string label, Node* currentNode);
	void trimAndSave();

	void Task4();
	void addToResultsT4(Node* n);
	void addToResultsT4(Node* n, short maxNumOfSeqs);
	void addToResultsT4(Node* n, short maxNumOfSeqs, string label);
	void collectDuplicates(Node* currentNode);
	void searchWithMissmatchesAndSave(short currentCharIdx, short currentErr, Node* currentNode);
	void findSharedPrefix(string label, short labelLength, Node* currentNode);


};

#endif /* TASKS_H_ */
