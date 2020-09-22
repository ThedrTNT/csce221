#include "vector-mpq.h"
#include "linkedlist-mpq.h"
#include "binaryheap-mpq.h"
#include "cpu-job.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

void loadJobs(vectorMPQ<CPU_Job>& queue, string filename) {
	ifstream inFile(filename);
	if (!inFile.is_open()) {
		cout << "rip" << endl;
	}
	//cout << "Loading jobs..." << endl;
	while(!inFile.eof()) {
		if(inFile.good()) {
			CPU_Job newJob;
			//cout << "Getting ID" << endl;
			inFile >> newJob.ID;
			//cout << "Getting length" << endl;
			inFile >> newJob.length;
			//cout << "Getting priority" << endl;
			inFile >> newJob.prior;
			queue.insert(newJob);
		}
		else {
			cout << "File error" << endl;
			inFile.clear();
		}
	}
	//cout << "Jobs loaded." << endl;
}

void loadJobs(linkedListMPQ<CPU_Job>& queue, string filename) {
	ifstream inFile(filename);
	if (!inFile.is_open()) {
		cout << "rip" << endl;
	}
	//cout << "Loading jobs..." << endl;
	while(!inFile.eof()) {
		if(inFile.good()) {
			CPU_Job newJob;
			//cout << "Getting ID" << endl;
			inFile >> newJob.ID;
			//cout << "Getting length" << endl;
			inFile >> newJob.length;
			//cout << "Getting priority" << endl;
			inFile >> newJob.prior;
			queue.insert(newJob);
		}
		else {
			cout << "File error" << endl;
			inFile.clear();
		}
	}
	//cout << "Jobs loaded." << endl;
}

void loadJobs(binaryHeapMPQ<CPU_Job>& queue, string filename) {
	ifstream inFile(filename);
	if (!inFile.is_open()) {
		cout << "rip" << endl;
	}
	//cout << "Loading jobs..." << endl;
	while(!inFile.eof()) {
		if(inFile.good()) {
			CPU_Job newJob;
			//cout << "Getting ID" << endl;
			inFile >> newJob.ID;
			//cout << "Getting length" << endl;
			inFile >> newJob.length;
			//cout << "Getting priority" << endl;
			inFile >> newJob.prior;
			queue.insert(newJob);
		}
		else {
			cout << "File error" << endl;
			inFile.clear();
		}
	}
	//cout << "Jobs loaded." << endl;
}

void runJob(CPU_Job job) {
	//cout << "Running job..." << endl;
	for (int i = job.length; i > 0; --i) {
		cout << job << endl;
		job.length--;
	}
}

void outputJobs(vectorMPQ<CPU_Job> queue, string filename) {
	ofstream outFile(filename);
	//cout << "Outputting..." << endl;
	while (!queue.is_empty()) {
		//cout << queue.is_empty() << endl;
		CPU_Job job = queue.remove_min();
		for (int i = job.length; i > 0; --i) {
			outFile << job << endl;
			job.length--;
		}
	}
	outFile << "No more jobs to run" << endl;
	cout << "No more jobs to run" << endl;
}

void outputJobs(linkedListMPQ<CPU_Job> queue, string filename) {
	ofstream outFile(filename);
	//cout << "Outputting..." << endl;
	while (!queue.is_empty()) {
		//cout << queue.is_empty() << endl;
		CPU_Job job = queue.remove_min();
		for (int i = job.length; i > 0; --i) {
			outFile << job << endl;
			job.length--;
		}
	}
	outFile << "No more jobs to run" << endl;
	cout << "No more jobs to run" << endl;
}

void outputJobs(binaryHeapMPQ<CPU_Job> queue, string filename) {
	ofstream outFile(filename);
	//cout << "Outputting..." << endl;
	while (!queue.is_empty()) {
		//cout << queue.is_empty() << endl;
		CPU_Job job = queue.remove_min();
		for (int i = job.length; i > 0; --i) {
			outFile << job << endl;
			job.length--;
		}
	}
	outFile << "No more jobs to run" << endl;
	cout << "No more jobs to run" << endl;
}

int main() {
	//This block tests the running times of each implementation and each of the 3 large input files

	string filename = "SetSize1000.txt"; //Change here to test different file
	cout << "Testing for " << filename << endl << endl;

	clock_t t1, t2, t3, t4, t5, t6;
	vectorMPQ<CPU_Job> vectorJobQueue;
	string outFilename = "OutputVector1000.txt";
	t1 = clock(); //start
	loadJobs(vectorJobQueue, filename);
	outputJobs(vectorJobQueue, outFilename);
	t2 = clock(); //stop
	double diff = (double) (t2 - t1) * 1000 / CLOCKS_PER_SEC;
	cout << "Vector timing: " << diff << " millisec" << endl << endl;

	linkedListMPQ<CPU_Job> listJobQueue;
	outFilename = "OutputList1000.txt";
	t3 = clock(); //start
	loadJobs(listJobQueue, filename);
	outputJobs(listJobQueue, outFilename);
	t4 = clock(); //stop
	double listDiff = (double) (t4 - t3) * 1000 / CLOCKS_PER_SEC;
	cout << "Linked list timing: " << listDiff << " millisec" << endl << endl;

	binaryHeapMPQ<CPU_Job> heapJobQueue;
	outFilename = "OutputHeap1000.txt";
	t5 = clock(); //start
	loadJobs(heapJobQueue, filename);
	outputJobs(heapJobQueue, outFilename);
	t6 = clock(); //stop
	double heapDiff = (double) (t6 - t5) * 1000 / CLOCKS_PER_SEC;
	cout << "Binary heap timing: " << heapDiff << " millisec" << endl << endl;

	

	filename = "SetSize10000.txt"; //Change here to test different file
	cout << "Testing for " << filename << endl << endl;

	vectorMPQ<CPU_Job> vectorJobQueue2;
	outFilename = "OutputVector10000.txt";
	t1 = clock(); //start
	loadJobs(vectorJobQueue2, filename);
	outputJobs(vectorJobQueue2, outFilename);
	t2 = clock(); //stop
	diff = (double) (t2 - t1) * 1000 / CLOCKS_PER_SEC;
	cout << "Vector timing: " << diff << " millisec" << endl << endl;

	linkedListMPQ<CPU_Job> listJobQueue2;
	outFilename = "OutputList10000.txt";
	t3 = clock(); //start
	loadJobs(listJobQueue2, filename);
	outputJobs(listJobQueue2, outFilename);
	t4 = clock(); //stop
	listDiff = (double) (t4 - t3) * 1000 / CLOCKS_PER_SEC;
	cout << "Linked list timing: " << listDiff << " millisec" << endl << endl;

	binaryHeapMPQ<CPU_Job> heapJobQueue2;
	outFilename = "OutputHeap10000.txt";
	t5 = clock(); //start
	loadJobs(heapJobQueue2, filename);
	outputJobs(heapJobQueue2, outFilename);
	t6 = clock(); //stop
	heapDiff = (double) (t6 - t5) * 1000 / CLOCKS_PER_SEC;
	cout << "Binary heap timing: " << heapDiff << " millisec" << endl << endl;


	filename = "SetSize100000.txt"; //Change here to test different file
	cout << "Testing for " << filename << endl << endl;

	vectorMPQ<CPU_Job> vectorJobQueue3;
	outFilename = "OutputVector100000.txt";
	t1 = clock(); //start
	loadJobs(vectorJobQueue3, filename);
	outputJobs(vectorJobQueue3, outFilename);
	t2 = clock(); //stop
	diff = (double) (t2 - t1) * 1000 / CLOCKS_PER_SEC;
	cout << "Vector timing: " << diff << " millisec" << endl << endl;

	linkedListMPQ<CPU_Job> listJobQueue3;
	outFilename = "OutputList100000.txt";
	t3 = clock(); //start
	loadJobs(listJobQueue3, filename);
	outputJobs(listJobQueue3, outFilename);
	t4 = clock(); //stop
	listDiff = (double) (t4 - t3) * 1000 / CLOCKS_PER_SEC;
	cout << "Linked list timing: " << listDiff << " millisec" << endl << endl;

	binaryHeapMPQ<CPU_Job> heapJobQueue3;
	outFilename = "OutputHeap100000.txt";
	t5 = clock(); //start
	loadJobs(heapJobQueue3, filename);
	outputJobs(heapJobQueue3, outFilename);
	t6 = clock(); //stop
	heapDiff = (double) (t6 - t5) * 1000 / CLOCKS_PER_SEC;
	cout << "Binary heap timing: " << heapDiff << " millisec" << endl << endl;

	/*

	//This block tests the functions of each implementation with ints
	vectorMPQ<int> vectorInt;
	vectorInt.insert(10);
	vectorInt.insert(15);
	vectorInt.insert(20);
	vectorInt.insert(1);
	vectorInt.insert(100);
	vectorInt.insert(-5);
	linkedListMPQ<int> listInt;
	listInt.insert(10);
	listInt.insert(15);
	listInt.insert(20);
	listInt.insert(1);
	listInt.insert(100);
	listInt.insert(-5);
	binaryHeapMPQ<int> heapInt;
	heapInt.insert(10);
	heapInt.insert(15);
	heapInt.insert(20);
	heapInt.insert(1);
	heapInt.insert(100);
	heapInt.insert(-5);

	cout << "testing vector with ints(starting as (10,15,20,1,100,-5): " << endl;
	cout << "Min: " << vectorInt.remove_min() << endl;
	cout << "Min: " << vectorInt.remove_min() << endl;
	cout << "Inserting 5: " << endl;
	vectorInt.insert(5);
	cout << "Min: " << vectorInt.remove_min() << endl;

	cout << "testing linked list with ints(starting as (10,15,20,1,100,-5): " << endl;
	cout << "Min: " << listInt.remove_min() << endl;
	cout << "Min: " << listInt.remove_min() << endl;
	cout << "Inserting 3: " << endl;
	listInt.insert(3);
	cout << "Min: " << listInt.remove_min() << endl;

	cout << "testing heap with ints(starting as (10,15,20,1,100,-5): " << endl;
	cout << "Min: " << heapInt.remove_min() << endl;
	cout << "Min: " << heapInt.remove_min() << endl;
	cout << "Inserting 7: " << endl;
	heapInt.insert(7);
	cout << "Min: " << heapInt.remove_min() << endl;*/

}