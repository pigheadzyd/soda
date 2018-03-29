#include "Bank.h"

using namespace std;

Bank::Bank( unsigned int numStudents ):
	numStudents( numStudents ) {
		studentBalance = new unsigned int[numStudents];
		waiting = new uCondition[numStudents];
		// init the basic account balance
		for ( unsigned int i = 0; i < numStudents; ++i ) {
			studentBalance[i] = 0;
		}	// for
}	// Bank::Bank

Bank::~Bank() {
	delete[] studentBalance;
	delete[] waiting;
}	// Bank::~Bank()

void Bank::deposit( unsigned int id, unsigned int amount ) {
	studentBalance[id] += amount;
	if ( !waiting[id].empty() ) {
		waiting[id].signal();
	}	// if
}

void Bank::withdraw( unsigned int id, unsigned int amount ){
	while ( studentBalance[id] < amount ) {
		waiting[id].wait();
	}	// while
	studentBalance[id] -= amount;
}