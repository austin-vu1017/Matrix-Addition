//Author: Austin Vu
//Assignment: Homework 3
//IDE: Visual Studio 2017

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct element {
	int row;
	int col;
	double value;
};

int main() {
	fstream inFile1, inFile2;	//input files
	ofstream outFile;	//output file
	element *inMatrix1 = new element[10000];
	element *inMatrix2 = new element[10000];
	element *outMatrix = new element[10000];
	element temp;	//used for sorting
	string fileDir;		//get file name
	string line;
	stringstream ss;
	bool match = false;		//used to determine if the dimensions matches
	int dimRow1, dimCol1, dimRow2, dimCol2,
		numOfElem1 = 0, numOfElem2 = 0, numOfElem3 = 0;		//dimRows and Cols check and numOfElem gets # of elements in matrixes 

	while (!inFile1.is_open()) {
		cout << "Enter Matrix File 1: ";
		cin >> fileDir;
		inFile1.open(fileDir);

		if (!inFile1.is_open()) {
			cerr << "-----ERROR OPENING FILE 1 TRY AGAIN-----" << endl;
		}
	}
	
	while (!inFile2.is_open()) {
		cout << "Enter Matrix File 2: ";
		cin >> fileDir;
		inFile2.open(fileDir);

		if (!inFile2.is_open()) {
			cerr << "-----ERROR OPENING FILE 2 TRY AGAIN-----" << endl;
		}
	}

	cout << "Name of Matrix Output File: ";
	cin >> fileDir;
	outFile.open(fileDir); //creates file

	if (!outFile.is_open()) {	//double check
		cerr << "-----ERROR CREATING OUTPUT FILE-----" << endl;
		exit(1);
	}

	do {
		getline(inFile1, line);
	} while (line[0] == '#');

	ss.str(line);
	ss >> dimRow1 >> dimCol1; //double check
	ss.clear(); //erases to reuse ss

	do {
		getline(inFile2, line);
	} while (line[0] == '#');

	ss.str(line);
	ss >> dimRow2 >> dimCol2;
	ss.clear();

	if ((dimRow1 != dimRow2) || (dimCol1 != dimCol2)) {
		cout << "COLUMNS OR ROWS DON'T MATCH IN DIMENSION" << endl;
	}
	else {
		while (getline(inFile1, line)) {
			if (line[0] != '#') {
				ss.str(line);
				ss >> inMatrix1[numOfElem1].row >> inMatrix1[numOfElem1].col >> inMatrix1[numOfElem1].value;
				ss.clear();

				numOfElem1++;
			}
		}

		while (getline(inFile2, line)) {
			if (line[0] != '#') {
				ss.str(line);
				ss >> inMatrix2[numOfElem2].row >> inMatrix2[numOfElem2].col >> inMatrix2[numOfElem2].value;
				ss.clear();

				numOfElem2++;
			}
		}

		for (int i = 0; i < numOfElem1; i++) {
			match = false;
			for (int j = 0; j < numOfElem2; j++) {
				if ((inMatrix1[i].row == inMatrix2[j].row) && (inMatrix1[i].col == inMatrix2[j].col)) {
					outMatrix[numOfElem3].row = inMatrix1[i].row;
					outMatrix[numOfElem3].col = inMatrix1[i].col;
					outMatrix[numOfElem3].value = inMatrix1[i].value + inMatrix2[j].value;

					numOfElem3++;
					match = true;
				}
			}

			if (match == false) {
				outMatrix[numOfElem3].row = inMatrix1[i].row;
				outMatrix[numOfElem3].col = inMatrix1[i].col;
				outMatrix[numOfElem3].value = inMatrix1[i].value;

				numOfElem3++;
			}
		}

		for (int i = 0; i < numOfElem2; i++) {
			match = false;
			for (int j = 0; j < numOfElem2; j++) {
				if ((inMatrix2[i].row == outMatrix[j].row) && (inMatrix2[i].col == outMatrix[j].col)) {
					match = true;
				}
			}
			if (match == false) {
				outMatrix[numOfElem3].row = inMatrix2[i].row;
				outMatrix[numOfElem3].col = inMatrix2[i].col;
				outMatrix[numOfElem3].value = inMatrix2[i].value;

				numOfElem3++;
			}
		}

		if (numOfElem3 > 1) {
			for (int i = 0; i < numOfElem3 - 1; i++) {
				for (int j = 0; j < numOfElem3 - i - 1; j++) {
					if (outMatrix[j].col > outMatrix[j + 1].col) {
						temp = outMatrix[j];
						outMatrix[j] = outMatrix[j + 1];
						outMatrix[j + 1] = temp;
					}
				}
			}

			for (int i = 0; i < numOfElem3 - 1; i++) {
				for (int j = 0; j < numOfElem3 - i - 1; j++) {
					if (outMatrix[j].row > outMatrix[j + 1].row) {
						temp = outMatrix[j];
						outMatrix[j] = outMatrix[j + 1];
						outMatrix[j + 1] = temp;
					}
				}
			}

		}

		outFile << "#Matrix C" << endl;
		outFile << dimRow1 << ' ' << dimCol1 << endl;

		for (int i = 0; i < numOfElem3; i++) {
			outFile << outMatrix[i].row << ' ' << outMatrix[i].col << ' ' << outMatrix[i].value << ' ' << endl;
		}

		cout << "SUCCESSFULLY CREATED OUTPUT FILE" << endl;
	}

	delete[] inMatrix1;
	delete[] inMatrix2;
	delete[] outMatrix;

	inFile1.close();
	inFile2.close();
	outFile.close();
	system("pause");
	return 0;
}