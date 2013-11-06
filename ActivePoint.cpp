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

#include "ActivePoint.h"

ActivePoint::ActivePoint() {
}

ActivePoint::~ActivePoint() {
}

void ActivePoint::set(int n, short e, short p) {
	node = n;
	idx = p;
	edge = e;
}

void ActivePoint::reset() {
	node = 0;
	idx = 0;
	edge = 0;
	remainder = 0;
}
