#ifndef VECTORMPQ_H
#define VECTORMPQ_H

#include <iostream>
#include <vector>

template<typename T>
class vectorMPQ {
private:
	std::vector<T> contents;
public:
	vectorMPQ();
	bool is_empty() const {return contents.size() == 0;}
	T remove_min();
	void insert(T obj);
};

template<typename T>
vectorMPQ<T>::vectorMPQ() {
	
}

template<typename T>
T vectorMPQ<T>::remove_min() {
	if (is_empty()) {
		return T();
	}
	T minimum = contents.at(0);
	int minIndex = 0;
	for (unsigned int i = 1; i < contents.size(); ++i) {
		if (contents.at(i) < minimum) {
			minimum = contents.at(i);
			minIndex = i;
		}
	}
	contents.erase(contents.begin() + minIndex);
	return minimum;
}

template<typename T>
void vectorMPQ<T>::insert(T obj) {
	contents.push_back(obj);
}

#endif