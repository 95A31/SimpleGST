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

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "GeneralizedSuffixTree.h"
#include "Tasks.h"

using namespace std;

int main(int argc, char *argv[]) {

	if (argc < 2) {
		cerr << "Too few arguments.\n";
		cerr << "Example of usage: SimpleGST input.txt\n";
		cerr << "Example of usage: SimpleGST input.txt output.dot\n";
		return -1;
	}
	cout << "*******************************************************************************" << endl;
	cout << "* Welcome to SimpleGST, a Simple C++ implementation of Generalized Suffix Tree" << endl;
	cout << "* Copyright (c) 95A31" << endl;
	cout << "* Source: https://github.com/95A31/SimpleGST" << endl;
	cout << "*******************************************************************************" << endl;

	ifstream readsFile(argv[1]);
	vector<string> reads;
	string read;
	while (getline(readsFile, read))
		reads.push_back(read);

	GeneralizedSuffixTree gst(reads);

	if (argc == 2) {
		Tasks t(&gst);
		t.Task1();
	} else if (argc == 3) {
		gst.exportInDotFormat(argv[2]);
	}

	return 0;
}
