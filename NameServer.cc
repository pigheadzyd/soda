#include "NameServer.h"
#include "VendingMachine.h"
#include "Printer.h"


NameServer::NameServer( 
	Printer & prt, 
	unsigned int numVendingMachines, 
	unsigned int numStudents ): 
	prt( prt ), 
	// curIndex( 0 ), curRegister( 0 ),
	numVendingMachines( numVendingMachines ), 
	numStudents( numStudents ) {
		vendingMachineList = new VendingMachine *[numVendingMachines];
		machineOfStudent = new unsigned int[numStudents];
		for ( int i = 0; i < numStudents; i++ ) {
			machineOfStudent[i] = i % numVendingMachines; 
		}
}

NameServer::~NameServer() {
	delete[] vendingMachineList;
	delete[] machineOfStudent;
}

void NameServer::VMregister ( VendingMachine * vendingmachine ) {
	vendingMachineList[vendingmachine->id] =vendingmachine;
}

VendingMachine * NameServer::getMachine( unsigned int id ) {
	int index = machineOfStudent[id];
	prt.print( Printer::Kind::NameServer, 'N', id, index );
	machineOfStudent[id] = ( index + 1 ) % numVendingMachines;
	return vendingMachineList[index];
}

VendingMachine ** NameServer::getMachineList() {
	return vendingMachineList;
}	// VendingMachine ** NameServer::getMachineList


void NameServer::main() {
	// print start
	prt.print( Printer::Kind::NameServer, 'S' );

	for ( int i = 0; i < numVendingMachines; ){
		_Accept( VMregister ) {
			prt.print( Printer::Kind::NameServer, 'R', i ); // which one should be printed
			i++;
		}
	} // for

	for (;;) {
		_Accept( ~NameServer ) {
			break;
		} or _Accept( getMachine ) {

		} or _Accept( getMachineList ) {

		}
	} // for
	prt.print( Printer::Kind::NameServer, 'F' );
}
