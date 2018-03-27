#include <iostream>
#include "Printer.h"

using name space std;

Printer::Printer( 
	unsigned int numStudents, 
	unsigned int numVendingMachines, 
	unsigned int numCouriers ):
numStudents( numStudents ), 
numVendingMachines( numVendingMachines ), 
numCouriers( numCouriers ){
	total = numStudents + numVendingMachines + numCouriers + 6;
	cout << "Parent";
	cout << '\t' << "Groupoff";
	cout << '\t' << "WATOff";
	cout << '\t' << "Names";
	cout << '\t' << "Truck";
	cout << '\t' << "Plant";
	for ( int i = 0; i < numStudents; ++i ){
		cout << '\t' << "Stud" << i;
	}	// for
	for ( int i = 0; i < numVendingMachines; ++i ){
		cout << '\t' << "Mach" << i;
	}	// for
	for ( int i = 0; i < numCouriers; ++i ){
		cout << '\t' << "Cour" << i;
	}	// for

	for ( int i = 0; i < 6; ++i ) {
		if ( i ) {
			cout << '\t';
		}	// if
		cout << "*******";
	}	// for
}

Printer::~Printer() {
	cout << "***********************" << endl;
}

void Printer::print( Kind kind, char state ){};

void Printer::print( Kind kind, char state, int value1 ){};

void Printer::print( Kind kind, char state, int value1, int value2 ){};

void Printer::print( Kind kind, unsigned int lid, char state ){};

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ){};

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ){};


