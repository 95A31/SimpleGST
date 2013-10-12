/*
 * Utils.h
 *
 *  Created on: 12/ott/2013
 *      Author: user
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>

using namespace std;

namespace Utils {

enum strRapport {
	EQUAL, DIFFERENT, SUBSTRING, SUPERSTRING, COMMON_PREFIX
};

static pair<strRapport, short> stringRapport(string nodeLabel, string prefix) {
	short nodeLabelLength = nodeLabel.length();
	short prefixLength = prefix.length();

	for (int i = 0; i < (nodeLabelLength > prefixLength) ? prefixLength : nodeLabelLength; i++) {
		if (nodeLabel[i] != prefix[i]) {
			if (i > 0)
				return pair<strRapport, short>(strRapport::COMMON_PREFIX, i);
			else
				return pair<strRapport, short>(strRapport::DIFFERENT, i);
		}
	}

	if (prefixLength > nodeLabelLength)
		return pair<strRapport, short>(strRapport::SUBSTRING, nodeLabelLength);
	else if ((prefixLength < nodeLabelLength))
		return pair<strRapport, short>(strRapport::SUPERSTRING, prefixLength);
	else
		return pair<strRapport, short>(strRapport::EQUAL, prefixLength);
}
}

#endif /* UTILS_H_ */
