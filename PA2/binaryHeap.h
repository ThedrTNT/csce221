#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <iostream>
#include <vector>

template<typename T>
class binaryHeap {
private:
	std::vector<T> contents;
	bool sorted;
public:
	binaryHeap();
	bool is_empty() const {return contents.size() == 0;}
	T remove_min();
	void insert(T obj);
	void sortHeap();
	void walkDown(unsigned int i);
};

template<typename T>
binaryHeap<T>::binaryHeap() {
	sorted = false;
}

template<typename T>
T binaryHeap<T>::remove_min() {
	if (!sorted) {
		sortHeap();
	}
	if (is_empty()) {
		//throw EmptyHeap("MPQ is empty");
		return T();
	}
	T retObj = contents.front();
	if (contents.size() == 1) {
		contents.pop_back();
		return retObj;
	}
	contents.at(0) = contents.at(contents.size()-1);
	contents.pop_back();
	walkDown(0);
	return retObj;
}

template<typename T>
void binaryHeap<T>::insert(T obj) {
	if (!sorted) {
		contents.push_back(obj);
		if (obj < contents.at((contents.size()-1)/2)) {
			sorted = false;
		}
		return;
	}
	contents.push_back(obj);
	unsigned int i = contents.size() - 1;
	for (; i > 0 && obj < contents.at((i-1)/2); i = (i-1)/2) {
		contents.at(i) = contents.at((i-1)/2);
	}
	contents.at(i) = obj;
}

template<typename T>
void binaryHeap<T>::walkDown(unsigned int i) {
	T objToMove = contents.front();
	unsigned int child;
	for (; 2*i+1 < contents.size(); i = child) {
		child = 2 * i + 1;
		if (child != contents.size()-1 && contents.at(child + 1) < contents.at(child)) {
			child++;
		}
		if (contents.at(child) < objToMove) {
			contents.at(i) = contents.at(child);
		} else {
			break;
		}
	} 
	contents.at(i) = objToMove;
}

template<typename T>
void binaryHeap<T>::sortHeap() {
	for (int i = (contents.size()-2) / 2; i >= 0; --i) {
		walkDown(i);
	}
	sorted = true;
}

#endif