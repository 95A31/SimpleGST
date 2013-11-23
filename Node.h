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

#ifndef NODE_H_
#define NODE_H_

#include <unordered_map>
#include <vector>

using namespace std;

class Node {
public:

	typedef pair<int,short> suffix;	//<StringIdx, Offset>

	Node();
	Node(int stringIdx, short labelStartIdx, short labelEndInx);
	virtual ~Node();

	void addSuffix(int stringIdx, short suffixIdx);
	short getLabelLength();

	//Label is extracted from string in this way: [labelStartIdx,labelEndInx)
	int stringIdx = -1;
	short labelStartIdx = -1;
	short labelEndIdx = -1;

	int suffixLink = -1;
	unordered_map<char,int> children;

	vector<suffix> suffixes;
};

#endif /* NODE_H_ */
