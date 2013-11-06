/*******************************************************************************
 *     Copyright (c) 2013 95A31.
 * 	
 *     This file is part of GeneralizedSuffixTree.
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

#ifndef ACTIVEPOINT_H_
#define ACTIVEPOINT_H_

class ActivePoint {
public:
	ActivePoint();
	virtual ~ActivePoint();

	int node = -1;
	short edge = -1;
	short idx = -1;
	short remainder = -1;

	void set(int n , short e, short p);
	void reset();
};

#endif /* ACTIVEPOINT_H_ */
