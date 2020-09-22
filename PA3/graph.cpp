#include "graph.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Graph::~Graph() {
	for (unsigned int i = 0; i < adj_list.size(); ++i) {
		delete adj_list.at(i);
	}
}

void Graph::buildGraph(ifstream &input) {
	while (!input.eof()) {
		if (input.good()) {
		    string line = "";
		    getline(input, line);
			stringstream ss(line);
			int firstNode;
			ss >> firstNode;
			if (ss.eof()) {
				return;
			}
			Vertex newVert(firstNode, 0);
			node_list.push_back(newVert);
			list<int>* adjacents = new list<int>();
			int newNode;
			ss >> newNode;
			while (newNode != -1) {
				adjacents->push_back(newNode);
				ss >> newNode;
			}
			adj_list.push_back(adjacents);
		}
		else {
			cout << "File error" << endl;
			input.clear();
		}
	}
}

void Graph::displayGraph() {
	for (unsigned int i = 0; i < adj_list.size(); ++i) {
		cout << node_list.at(i).label << " : ";
		list<int> adjacent = *adj_list.at(i);
		for (const int & node : adjacent) {
			cout << node << " ";
		}
		cout << endl;
	}
}

void Graph::displayIndegree() {
	for (unsigned int i = 0; i < adj_list.size(); ++i) {
		cout << node_list.at(i).indegree << " ";
	}
	cout << endl;
}