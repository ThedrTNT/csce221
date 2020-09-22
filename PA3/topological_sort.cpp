// topological sort

#include <iostream>
#include <queue>
#include <exception>
#include "graph.h"

class CycleFoundException: public exception {
	virtual const char* what() const throw()
  	{
    	return "Error: Cyclic Graph Found";
  	}
};

void Graph::compute_indegree()
{
  // to be implemented
	/*for (unsigned int i = 0; i < node_list.size(); ++i) {
		node_list.at(i).indegree = 0;
	}*/

	for (unsigned int i = 0; i < adj_list.size(); ++i) {
		list<int> adjacent = *adj_list.at(i);
		for (const int & adj : adjacent) {
			node_list.at(adj - 1).indegree++;
		}
	}
}

void Graph::topological_sort()
{
  // to be implemented
	queue<Vertex> topSortQueue;
	int counter = 0;

	for (const Vertex & node : node_list) {
		if (node.indegree == 0) {
			//cout << "test" << endl;
			topSortQueue.push(node);
		}
	}

	//cout << topSortQueue.size() << endl;

	while (!topSortQueue.empty()) {
		//cout << "test" << endl;
		Vertex v = topSortQueue.front();
		topSortQueue.pop();
		v.top_num = ++counter;

		for (unsigned int i = 0; i < node_list.size(); ++i) {
			if (node_list.at(i).label == v.label) {
				node_list.at(i).top_num = v.top_num;
			}
		}

		list<int> adjacent = *adj_list.at(v.label - 1);
		for (int & node : adjacent) {		
			if (--node_list.at(node - 1).indegree == 0) {
				topSortQueue.push(node_list.at(node - 1));
			}
		}
	}

	if (counter != node_list.size()) {
		throw CycleFoundException();
	}
}

void Graph::print_top_sort()
{
  // to be implemented
	for (unsigned int i = 0; i < node_list.size(); ++i) {
		for (unsigned int j = 0; j < node_list.size(); ++j) {
			if (node_list.at(j).top_num == i + 1) {
				cout << node_list.at(j).label << " ";
			}
		}
	}
	cout << endl;
}
