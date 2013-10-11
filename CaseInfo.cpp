/*
 * CaseInfo.cpp
 *
 *  Created on: 11/ott/2013
 *      Author: user
 */

#include "CaseInfo.h"

CaseInfo::CaseInfo(string labelFromTree, string& prefixToInsert) {

	int labelFromTreeLength = labelFromTree.length();

	for (int i = 0; i < labelFromTreeLength; i++) {

		if (labelFromTree[i] != prefixToInsert[i]) {
			if (i > 0) {
				caseType = CONTAINS;
				index = i;
			} else {
				caseType = NOT_CONTAINS;
				index = -1;
			}
			return;
		}
	}

	int prefixToInsertLength = prefixToInsert.length();

	if (prefixToInsertLength == labelFromTreeLength) {
		caseType = EQUAL;
		index = prefixToInsertLength;
	} else {
		caseType = IS_SUBSTRING_OF;
		index = prefixToInsertLength;
	}
}

CaseInfo::CaseInfo() {
	caseType = DIFFERENT;
	index = -1;
}

CaseInfo::~CaseInfo() {
// TODO Auto-generated destructor stub
}

CaseInfo::CaseType CaseInfo::getCaseType() {
	return caseType;
}

int CaseInfo::getIndex() {
	return index;
}
