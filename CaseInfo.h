/*
 * CaseInfo.h
 *
 *  Created on: 11/ott/2013
 *      Author: user
 */

#ifndef CASEINFO_H_
#define CASEINFO_H_

#include <string>
#include "Node.h"

using namespace std;

class CaseInfo {
public:
	CaseInfo(string labelFromTree, string& prefixToInsert);
	CaseInfo();
	virtual ~CaseInfo();

	enum CaseType{CASE_1, CASE_2, CASE_3};

	CaseType getCaseType();
	int getIndex();

private:
	CaseType caseType;
	int index;
	//Node& node;
};

#endif /* CASEINFO_H_ */
