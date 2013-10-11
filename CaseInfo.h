/*
 * CaseInfo.h
 *
 *  Created on: 11/ott/2013
 *      Author: user
 */

#ifndef CASEINFO_H_
#define CASEINFO_H_

#include <string>

using namespace std;

class CaseInfo {
public:
	CaseInfo(string labelFromTree, string& prefixToInsert);
	CaseInfo();
	virtual ~CaseInfo();

	enum CaseType{CONTAINS,NOT_CONTAINS, EQUAL, IS_SUBSTRING_OF, DIFFERENT};

	CaseType getCaseType();
	int getIndex();

private:
	CaseType caseType;
	int index;
};

#endif /* CASEINFO_H_ */
