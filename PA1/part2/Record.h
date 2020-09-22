#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <iostream>

class Record {
	std::string title;
	std::string authName;
	std::string idNum;
	std::string publishYear;
	std::string editionNum;
public:
	Record();
	Record(std::string, std::string, std::string, std::string, std::string);
	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getISBN() const;
	std::string getPublishYear() const;
	std::string getEdition() const;
	void setTitle(std::string);
	void setAuthor(std::string);
	void setISBN(std::string);
	void setPublishYear(std::string);
	void setEdition(std::string);

};

//O(1)
Record::Record() {
	title = "";
	authName = "";
	idNum = "";
	publishYear = "";
	editionNum = "";
}

//O(1)
Record::Record(std::string title, std::string author, std::string idNum, std::string publishYear, std::string edition) : title(title), authName(author), idNum(idNum), publishYear(publishYear), editionNum(edition) {

}

//O(1)
std::string Record::getTitle() const {
	return title;
}

//O(1)
std::string Record::getAuthor() const {
	return authName;
}

//O(1)
std::string Record::getISBN() const {
	return idNum;
}

//O(1)
std::string Record::getPublishYear() const {
	return publishYear;
}

//O(1)
std::string Record::getEdition() const{
	return editionNum;
}

//O(1)
void Record::setTitle(std::string newTitle) {
	title = newTitle;
}

void Record::setAuthor(std::string newAuthor) {
	authName = newAuthor;
}

//O(1)
void Record::setISBN(std::string newISBN) {
	idNum = newISBN;
}

//O(1)
void Record::setPublishYear(std::string newPubYear) {
	publishYear = newPubYear;
}

//O(1)
void Record::setEdition(std::string newEdition) {
	editionNum = newEdition;
}

//O(n)
std::istream& operator>>(std::istream& is, Record& book) {
	std::string title;
	getline(is, title);
	if(title.length() <= 1 && !is.eof()) {
		getline(is, title);

	}
	book.setTitle(title);
	std::string authName;
	if(title.length() <=1 || is.eof()) {
		return is;
	}
	getline(is, authName);
	book.setAuthor(authName);
	std::string idNum;
	if(authName.length() <= 1 || is.eof()) {
		return is;
	}
	getline(is, idNum);
	book.setISBN(idNum);
	std::string pubYear;
	if(is.eof()) {
		return is;
	}
	getline(is, pubYear);
	book.setPublishYear(pubYear);
	std::string edition;
	if(is.eof()) {
		return is;
	}
	getline(is, edition);
	book.setEdition(edition);

	return is;
}

//O(1)
std::ostream& operator<<(std::ostream& os, const Record& book) {
	os << book.getTitle() << "\n" << book.getAuthor() << "\n" << book.getISBN() << "\n" << book.getPublishYear() << "\n" << book.getEdition() << "\n";
	return os;
}

//O(1)
bool operator==(const Record& r1, const Record& r2) {
	if (r1.getTitle() != r2.getTitle()) {
		//std::cout << "Diff titles" << std::endl;
		return false;
	}
	if (r1.getAuthor() != r2.getAuthor()) {
		return false;
	}
	if (r1.getISBN() != r2.getISBN()) {
		return false;
	}
	return true;
}

bool operator<(const Record& r1, const Record& r2) {
	if (r1.getTitle() < r2.getTitle()) {
		//std::cout << "Diff titles" << std::endl;
		//std::cout << r1.getTitle() << " < " << r2.getTitle() << std::endl;
		return true;
	}
	if (r1.getTitle() == r2.getTitle() && r1.getAuthor() < r2.getAuthor()) {
		return true;
	}
	if (r1.getTitle() == r2.getTitle() && r1.getAuthor() == r2.getAuthor() && r1.getISBN() < r2.getISBN()) {
		return true;
	}
	return false;
}
  
#endif