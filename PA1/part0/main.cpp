#include "Record.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
	vector<Record> bookList;

	ifstream inFile("Book.txt");
	while (!inFile.eof()) {
		if (inFile.good()) {
			Record newRecord;
			inFile >> newRecord;
			if(newRecord.getEdition().length() <= 1) {
				continue;
			}
			bookList.push_back(newRecord);
		}
		else {
			inFile.clear();
		}
	}

	for(unsigned int i = 0; i < bookList.size(); ++i) {
		cout << bookList.at(i) << endl;
	}

	cout << "Comparison check: " << endl;
	cout << "r0 == r1" << endl;
	cout << (bookList.at(0) == bookList.at(1)) << endl;
	cout << "r0 == r0" << endl;
	cout << (bookList.at(0) == bookList.at(0)) << endl;
}