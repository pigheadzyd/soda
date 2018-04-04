#include "Bank.h"																					// Definition of Bank monitor

using namespace std;


//--------------------------------------------------------------------------------------------------------------------
// Starup and shutdown.
//--------------------------------------------------------------------------------------------------------------------
Bank::Bank( unsigned int numStudents ):
	numStudents( numStudents ) {
		studentBalance = new unsigned int[numStudents];
		waiting = new uCondition[numStudents];
		for ( unsigned int i = 0; i < numStudents; ++i ) {		// Init the basic account balance
			studentBalance[i] = 0;
		}	// for
}	// Bank::Bank

Bank::~Bank() {
	delete[] studentBalance;
	delete[] waiting;
}	// Bank::~Bank


//--------------------------------------------------------------------------------------------------------------------
// Deposit the amount money into the id student.
//--------------------------------------------------------------------------------------------------------------------
void Bank::deposit( unsigned int id, unsigned int amount ) {
	studentBalance[id] += amount;
	if ( !waiting[id].empty() ) {														// If withdraw are waiting
		waiting[id].signal();
	}	// if
}	// Bank::deposit


//--------------------------------------------------------------------------------------------------------------------
// Withdraw the amount money from the id student.
//--------------------------------------------------------------------------------------------------------------------
void Bank::withdraw( unsigned int id, unsigned int amount ){
	while ( studentBalance[id] < amount ) {									// Waiting until get the balance has enough money
		waiting[id].wait();
	}	// while
	studentBalance[id] -= amount;
}	// Bank::withdraw