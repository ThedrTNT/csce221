#ifndef LINKEDLISTMPQ_H
#define LINKEDLISTMPQ_H

#include <iostream>
#include <list>

template<typename T>
class linkedListMPQ {
private:
	std::list<T> contents;
	bool sorted;
public:
	linkedListMPQ();
	bool is_empty() const {return contents.size() == 0;}
	T remove_min();
	void insert(T obj);
};

template<typename T>
linkedListMPQ<T>::linkedListMPQ() {
	
}

template<typename T>
T linkedListMPQ<T>::remove_min() {
	if (is_empty()) {
		return T();
	}
	if (!sorted) {
		contents.sort();
		sorted = true;
	}
	T minimum = contents.front();
	contents.pop_front();	
	return minimum;
}

template<typename T>
void linkedListMPQ<T>::insert(T obj) {
	contents.push_back(obj);
	sorted = false;

}

#endif