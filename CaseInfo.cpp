/*
 * CaseInfo.cpp
 *
 *  Created on: 11/ott/2013
 *      Author: user
 */

#include "CaseInfo.h"

CaseInfo::CaseInfo(string labelFromTree, string& prefixToInsert) {

}

CaseInfo::CaseInfo() {

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
