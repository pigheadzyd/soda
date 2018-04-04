#include <iostream>

#include "Printer.h"																		// Definition of Bottling Plant Task

using namespace std;


//--------------------------------------------------------------------------------------------------------------------
// Starup and shutdown.
//--------------------------------------------------------------------------------------------------------------------
Printer::Printer( 
	unsigned int numStudents, 
	unsigned int numVendingMachines, 
	unsigned int numCouriers ):
numStudents( numStudents ), 
numVendingMachines( numVendingMachines ), 
numCouriers( numCouriers ), total( 0 ) {
	// Adding the mapping info between State and index
	cout << "Parent";
	indexMap[Parent] = total++;

	cout << '\t' << "Gropoff";
	indexMap[Groupoff] = total++;

	cout << '\t' << "WATOff";
	indexMap[WATCardOffice] = total++;

	cout << '\t' << "Names";
	indexMap[NameServer] = total++;

	cout << '\t' << "Truck";
	indexMap[Truck] = total++;

	cout << '\t' << "Plant";
	indexMap[BottlingPlant] = total++;

	for ( unsigned int i = 0; i < numStudents; ++i ) {					// init Students
		cout << '\t' << "Stud" << i;
	}	// for
	indexMap[Student] = total;
	total += numStudents;

	for ( unsigned int i = 0; i < numVendingMachines; ++i ) {		// init Vending Machines
		cout << '\t' << "Mach" << i;
	}	// for
	indexMap[Vending] = total;
	total += numVendingMachines;

	for ( unsigned int i = 0; i < numCouriers; ++i ) {					// init Coureiers
		cout << '\t' << "Cour" << i;
	}	// for

	indexMap[Courier] = total;
	total += numCouriers;
	cout << endl;

	printInfo = new PrintInfo[total];

	for ( unsigned int i = 0; i < total; ++i ) {
		if ( i ) {
			cout << '\t';
		}	// if
		cout << "*******";
	}	// for
	cout << endl;

}	// Printer::Printer

Printer::~Printer() {
	flush();
	delete[] printInfo;
	cout << "***********************" << endl;
}	// Printer::~Printer()


//--------------------------------------------------------------------------------------------------------------------
// Print the info in the printInfo immediately and reset the data back in the prinInfo.
//--------------------------------------------------------------------------------------------------------------------
void Printer::flush() {
	for ( unsigned int i = 0; i < total; ++i ) {
		if ( i ) {
			cout << '\t';
		}	// if

		if ( printInfo[i].update ) {							// If multiple of value has beed set
			cout << printInfo[i].state;
		}	// if
		if ( printInfo[i].updateValue1 ) {
			cout << printInfo[i].value1;
		}	// if
		if ( printInfo[i].updateValue2 ) {
			cout << "," << printInfo[i].value2;
		}	// if

		// reset the value
		printInfo[i].update = false;
		printInfo[i].updateValue1 = false;
		printInfo[i].updateValue2 = false;
	}	// for

	cout << endl;
}	// Printer::flush


//--------------------------------------------------------------------------------------------------------------------
// Different methods of getIndex by given Kind with or without id option.
//--------------------------------------------------------------------------------------------------------------------
unsigned int Printer::getIndex( Kind kind ) {
	return indexMap.at( kind );
}	// Printer::getIndex

unsigned int Printer::getIndex( Kind kind, unsigned int lid ) {
	return indexMap.at( kind ) + lid;
}	// Printer::getIndex


//--------------------------------------------------------------------------------------------------------------------
// Setting the corresponding state in printInfo, 
// Difference amoung with or without value option and the number of values.
//--------------------------------------------------------------------------------------------------------------------
void Printer::setState( unsigned int index, char state ) {
	if ( printInfo[index].update ) {		// check if the setState has buffer or not
		flush();
	}	// if

	printInfo[index].update = true;
	printInfo[index].state = state;
}	// Printer::setState

void Printer::setState( unsigned int index, char state, int value1 ) {
	setState( index, state );
	printInfo[index].updateValue1 = true;
	printInfo[index].value1 = value1;
}	// Printer::setState

void Printer::setState( unsigned int index, char state, int value1, int value2 ) {
	setState( index, state, value1 );
	printInfo[index].updateValue2 = true;
	printInfo[index].value2 = value2;
}	// Printer::setState


//--------------------------------------------------------------------------------------------------------------------
// Put the state and value into printInfo buffer and waiting for print
// Difference amoung different input numver
//--------------------------------------------------------------------------------------------------------------------
void Printer::print( Kind kind, char state ) {
	unsigned int index = getIndex( kind );
	setState( index, state );
}	// Printer::print

void Printer::print( Kind kind, char state, int value1 ) {
	unsigned int index = getIndex( kind );
	setState( index, state, value1 );
}	// Printer::print

void Printer::print( Kind kind, char state, int value1, int value2 ) {
	unsigned int index = getIndex( kind );
	setState( index, state, value1, value2 );
}	// void Printer::print

void Printer::print( Kind kind, unsigned int lid, char state ) {
	unsigned int index = getIndex( kind, lid );
	setState( index, state );
}	// Printer::print

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
	unsigned int index = getIndex( kind, lid );
	setState( index, state, value1 );
}	// Printer::print

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
	unsigned int index = getIndex( kind, lid );
	setState( index, state, value1, value2 );
}	// Printer::print


