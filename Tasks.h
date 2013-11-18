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

#include "GeneralizedSuffixTree.h"
#include "Node.h"

class Tasks {
public:
	Tasks(GeneralizedSuffixTree* gst);
	virtual ~Tasks();

	void Task1();
	void addToResultsT1(Node* n, short adapterLength);
	void addToResultsT1(int nodeID, short adapterLength);


	GeneralizedSuffixTree* gst;
	unordered_map<short, int> resultsT1;
};

#endif /* TASKS_H_ */
