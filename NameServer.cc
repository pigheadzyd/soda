#include "NameServer.h"																	// Definition of NameServer Monitor
#include "VendingMachine.h"
#include "Printer.h"


//--------------------------------------------------------------------------------------------------------------------
// Starup and shutdown.
//--------------------------------------------------------------------------------------------------------------------
NameServer::NameServer( 
	Printer & prt, 
	unsigned int numVendingMachines, 
	unsigned int numStudents ): 
	prt( prt ), 
	numVendingMachines( numVendingMachines ), 
	numStudents( numStudents ) {
		vendingMachineList = new VendingMachine *[numVendingMachines];
		machineOfStudent = new unsigned int[numStudents];
		for ( unsigned int i = 0; i < numStudents; i++ ) {		// Assign the default machine for student
			machineOfStudent[i] = i % numVendingMachines; 
		}	// for
}

NameServer::~NameServer() {
	delete[] vendingMachineList;
	delete[] machineOfStudent;
	prt.print( Printer::Kind::NameServer, 'F' );
}


//--------------------------------------------------------------------------------------------------------------------
// Register the vending machine into nameserver by there id.
//--------------------------------------------------------------------------------------------------------------------
void NameServer::VMregister( VendingMachine * vendingmachine ) {
	vendingMachineList[vendingmachine->getId()] = vendingmachine;
	prt.print( Printer::Kind::NameServer, 'R', vendingmachine->getId() );
}	// NameServer::VMregister


//--------------------------------------------------------------------------------------------------------------------
// Student ask to find a vending machine to buy soda.
//--------------------------------------------------------------------------------------------------------------------
VendingMachine * NameServer::getMachine( unsigned int id ) {
	int index = machineOfStudent[id];
	prt.print( Printer::Kind::NameServer, 'N', id, index );
	machineOfStudent[id] = ( index + 1 ) % numVendingMachines;	// Determine the next vending machine when the student call next time
	return vendingMachineList[index];
}


//--------------------------------------------------------------------------------------------------------------------
// Register the vending machine into nameserver by there id.
//--------------------------------------------------------------------------------------------------------------------
VendingMachine ** NameServer::getMachineList() {
	return vendingMachineList;
}	// NameServer::getMachineList


//--------------------------------------------------------------------------------------------------------------------
// Register the vending machine into nameserver by there id.
//--------------------------------------------------------------------------------------------------------------------
void NameServer::main() {
	prt.print( Printer::Kind::NameServer, 'S' );

	for ( unsigned int i = 0; i < numVendingMachines; ){				// Waiting for all vending machine have registered
		_Accept( VMregister ) {
			i++;
		}	// _Accept
	} // for

	for ( ;; ) {
		_Accept( ~NameServer ) {																	// Accept the destuctor to break the loop
			break;
		} or _Accept( getMachine ) {															// Accept the getMachine case

		} or _Accept( getMachineList ) {													// Accept the getMachineList case

		}	// _Accept
	} // for
}
