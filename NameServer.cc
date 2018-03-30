#include "NameServer.h"
#include "VendingMachine.h"


NameServer::NameServer( 
	Printer & prt, 
	unsigned int numVendingMachines, 
	unsigned int numStudents ): 
	prt( prt ), curIndex( 0 ), curRegister( 0 ),
	numVendingMachines( numVendingMachines ), 
	numStudents( numStudents ){
		vendingMachineList = new VendingMachine *[numVendingMachines];
}

NameServer::~NameServer() {
	delete[] vendingMachineList;
}

void NameServer::main() {}

void NameServer::VMregister ( VendingMachine * vendingmachine ) {
	vendingMachineList[curRegister] =vendingmachine;
	curRegister++;
}

VendingMachine * NameServer::getMachine( unsigned int id ) {
	int index = curIndex % curRegister;
	curIndex++;
	return vendingMachineList[index];
}

VendingMachine ** NameServer::getMachineList() {
	return vendingMachineList;
}	// VendingMachine ** NameServer::getMachineList

