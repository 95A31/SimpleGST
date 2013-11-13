/*******************************************************************************
 *     Copyright (c) 2013 95A31.
 * 	
 *     This file is part of SimpleGST.
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

#include "Node.h"

using namespace std;

Node::Node() {
}


Node::Node(int si, short lsi, short lei) {
	stringIdx = si;
	labelStartIdx = lsi;
	labelEndIdx = lei;
}

Node::~Node() {
}

void Node::addSuffix(int stringIdx, short charIdx){
	suffixes.push_back(make_pair(stringIdx, charIdx));
}

short Node::getLabelLength(){
	return labelEndIdx - labelStartIdx + 1;
}
