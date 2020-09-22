#include <iostream>
#include <vector>
#include <list>
#include <forward_list>

using namespace std;

list<int> intersect(list<int> l1, list<int> l2) {
	list<int> retList;
	for (list<int>::iterator i = l1.begin(); i != l1.end(); ++i) {
		for (list<int>::iterator j = l2.begin(); j != l2.end(); ++j) {
			if (*i == *j) {

				retList.push_back(*i);
			}
		}
	}
	retList.unique();
	return retList;
}

int nodeCounter(forward_list<int> linkedList) {
	if (linkedList.empty()) {
		return 0;
	}
	linkedList.pop_front();
	return 1 + nodeCounter(linkedList);
}

int maxVal(vector<int> values) {
	if(values.size() == 1) {
		return values.at(0);
	}
	vector<int> newVec(values.begin(), values.end()-1);
	int temp = maxVal(newVec);
	if (temp > values.back()) {
		return temp;
	}
	return values.back();
}

struct treeNode {
	int obj;
	treeNode* left;
	treeNode* right;
	treeNode(int o=0, treeNode* l=nullptr, treeNode* r=nullptr) : obj(o), left(l), right(r) {};
};

int countParents(treeNode* head) {
	if (head->left == nullptr || head->right == nullptr) {
		if (head->left == nullptr) {
			return 0 + countParents(head->right); 
		}
		if (head->right == nullptr) {
			return 0 + countParents(head->left); 
		}
		return 0;
	}
	return 1 + countParents(head->left) + countParents(head->right);
}

int main() {
	//int comparisons = 0;
	vector<int> a;
	for (int i = 1; i < 11; ++i) {
		a.push_back(i);
	}
	a.insert(a.begin(), 160);

	cout << maxVal(a) << endl;
	
}