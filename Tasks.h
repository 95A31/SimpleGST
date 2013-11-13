/*
 * Tasks.h
 *
 *  Created on: 06/nov/2013
 *      Author: void
 */

#ifndef TASKS_H_
#define TASKS_H_

#include "GeneralizedSuffixTree.h"
#include "Node.h"

class Tasks {
public:
	Tasks(GeneralizedSuffixTree* gst);
	virtual ~Tasks();

	void deepFirtVisit(Node& n, short currentMatchIdx, short allowedMissMatches, string& s);

	void Task1();
	void addToResultsT1(Node* n, short adapterLength);
	void addToResultsT1(int nodeID, short adapterLength);

	void Task2();

	GeneralizedSuffixTree* gst;
	unordered_map<short, int> resultsT1;
};

#endif /* TASKS_H_ */
