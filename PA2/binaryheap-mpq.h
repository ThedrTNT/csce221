#ifndef BINARYHEAPMPQ_H
#define BINARYHEAPMPQ_H

#include <iostream>
#include "binaryHeap.h"

template<typename T>
class binaryHeapMPQ {
private:
	binaryHeap<T> contents;
public:
	binaryHeapMPQ();
	bool is_empty() const {return contents.is_empty();}
	T remove_min();
	void insert(T obj);
};

template<typename T>
binaryHeapMPQ<T>::binaryHeapMPQ() {

}

template<typename T>
T binaryHeapMPQ<T>::remove_min() {
	return contents.remove_min();
}

template<typename T>
void binaryHeapMPQ<T>::insert(T obj) {
	contents.insert(obj);
}

#endif