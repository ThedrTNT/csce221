#ifndef CPUJOBS_H
#define CPUJOBS_H

#include <iostream>

using namespace std;

struct CPU_Job {
	int ID;
	int length;
	int prior;
	CPU_Job(int a=0, int b=0, int c=0) : ID(a), length(b), prior(c) {};
	bool operator<(const CPU_Job& job);
};

bool CPU_Job::operator<(const CPU_Job& job) {
	if (this->prior < job.prior) {
		return true;
	}
	if (this->prior == job.prior && this->ID < job.ID) {
		return true;
	}
	return false;

}

ostream& operator<<(ostream& out, const CPU_Job& job) {
	out << "Job " << job.ID << " with length " << job.length << " and priority " << job.prior;
	return out;
}

#endif