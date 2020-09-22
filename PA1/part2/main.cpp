#include "Record.h"
#include "TemplatedDLList.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void sort(DLList<Record>& linkedList) {
	if (linkedList.is_empty()) {
		return;
	}

	bool swap;
	DLListNode<Record>* curr = linkedList.first_node();
	DLListNode<Record>* endNode = linkedList.after_last_node()->prev->next;
	do {
		swap = 0;
		curr = linkedList.first_node();
		while (curr->next != endNode) {
			Record r1 = curr->obj;
			Record r2 = curr->next->obj;
			if (r2 < r1) {
				//cout << curr->next->obj << " < " << curr->obj << endl;
				curr->obj = r2;
				curr->next->obj = r1;
				swap = 1;
			}
			curr = curr->next;
		}
		endNode = curr;
	} while (swap);
}

// Determines which DLList to access based on what the title begins with
int letterIndex(char firstLetter) {
	int index = -1;
	switch(toupper(firstLetter)) {
		case 'A':
			index = 0;
			break;
		case 'B':
			index = 1;
			break;
		case 'C':
			index = 2;
			break;
		case 'D':
			index = 3;
			break;
		case 'E':
			index = 4;
			break;
		case 'F':
			index = 5;
			break;
		case 'G':
			index = 6;
			break;
		case 'H':
			index = 7;
			break;
		case 'I':
			index = 8;
			break;
		case 'J':
			index = 9;
			break;
		case 'K':
			index = 10;
			break;
		case 'L':
			index = 11;
			break;
		case 'M':
			index = 12;
			break;
		case 'N':
			index = 13;
			break;
		case 'O':
			index = 14;
			break;
		case 'P':
			index = 15;
			break;
		case 'Q':
			index = 16;
			break;
		case 'R':
			index = 17;
			break;
		case 'S':
			index = 18;
			break;
		case 'T':
			index = 19;
			break;
		case 'U':
			index = 20;
			break;
		case 'V':
			index = 21;
			break;
		case 'W':
			index = 22;
			break;
		case 'X':
			index = 23;
			break;
		case 'Y':
			index = 24;
			break;
		case 'Z':
			index = 25;
			break;
	};
	//cout << index << endl;
	return index;
}

void addRecordToDLL(Record recToAdd, vector<DLList<Record>>& library) {
	char firstLetter = recToAdd.getTitle().at(0);
	int index = letterIndex(firstLetter);
	if (index == -1) {
		return;
	}
	library.at(index).insert_first(recToAdd);
	sort(library.at(index));
}

//used to load from a file. Mostly used during testing
void loadLibrary(vector<DLList<Record>>& library, string filename) {
	cout << "Loading library:" << endl;
	vector<Record> bookList;
	ifstream inFile(filename);
	cout << "Acquiring records..." << endl;
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

	cout << "Alphabatizing records..." << endl;
	while (bookList.size() > 0) {
		Record recToAdd = bookList.at(bookList.size()-1);

		addRecordToDLL(recToAdd, library);	
		bookList.pop_back();
	}

	cout << "Library loaded." << endl;
}

void searchLibrary(vector<DLList<Record>>& library) {
	string title;
	string authorName;
	string idNum;
	string editionNum;
	string publishYear;
	cout << "Input record title to start searching: ";
	cin.ignore();
	getline(cin, title);
	//cout << "title: " << title << endl;
	char firstLetter = title.at(0);
	DLList<Record> listToSearch = library.at(letterIndex(firstLetter));
	//cout << "List to search: " << listToSearch;
	if (!listToSearch.containsTitle(title)) {
		cout << "The title could not be found, please add the following information to add to the library:" << endl;
		cout << "Input the author's name: ";
		getline(cin, authorName);
		cout << "Input the ISBN: ";
		getline(cin, idNum);
		cout << "Input the publishing year: ";
		getline(cin, publishYear);
		cout << "Input the edition number: ";
		getline(cin, editionNum);
		Record recToAdd(title, authorName, idNum, publishYear, editionNum);
		addRecordToDLL(recToAdd, library);
		cout << recToAdd;
	} else {
		vector<Record> recordList;
		DLListNode<Record>* curr = listToSearch.first_node();
		while (curr != listToSearch.after_last_node()->prev->next) {
			if (curr->obj.getTitle() == title) {
				recordList.push_back(curr->obj);
			}
			curr = curr->next;
 		}
 		if (recordList.size() > 1) {
 			for (unsigned int i = 0; i < recordList.size(); ++i) {
 				cout << "Choice " << i+1 << endl << recordList.at(i);
 			}
 			cout << "Please select which edition you would like." << endl;
 			int index;
 			cin >> index;
 			cout << recordList.at(index - 1); 
 		} else {
 			cout << recordList.at(0);
 		}
	}
}

void printMenu() {
	cout << "--------------------------" << endl;
  	cout << " 'L': Load records from a file" << endl;
  	cout << " 'S': Search library" << endl;
  	cout << " 'A': Add record" << endl;
  	cout << " 'Q': Quit" << endl;
  	cout << "--------------------------" << endl;
  	cout << endl << "Please enter your choice: ";
}

void createNewRecord(vector<DLList<Record>>& library) {
	string title = "";
	string authorName = "";
	string idNum = "";
	string editionNum = "";
	string publishYear = "";
	cout << "Input the title: ";
	cin.ignore();
	getline(cin, title);
	cout << "Input the author's name: ";
	getline(cin, authorName);
	cout << "Input the ISBN: ";
	getline(cin, idNum);
	cout << "Input the publishing year: ";
	getline(cin, publishYear);
	cout << "Input the edition number: ";
	getline(cin, editionNum);
	Record recToAdd(title, authorName, idNum, publishYear, editionNum);
	addRecordToDLL(recToAdd, library);
	cout << recToAdd;
}

int main () {
	vector<DLList<Record>> library;
	for (int i = 0; i < 26; ++i) {
		DLList<Record> newLetter;
		library.push_back(newLetter);
	}

	//loadLibrary(library, "Book.txt");

	string filename;
	char menuChoice = ' ';
	do {
		printMenu();
		cin >> menuChoice;
		switch(toupper(menuChoice)) {
			case 'L':
				cout << "Input file to load from: ";
				cin >> filename;
				loadLibrary(library, filename);
				break;
			case 'S':
				searchLibrary(library);
				break;
			case 'A':
				createNewRecord(library);
				break;
			case 'Q':
				break;
			default:
				cout << "'" << menuChoice << "' is an invalid choice" << endl; 

		};
	} while(toupper(menuChoice) != 'Q');
}