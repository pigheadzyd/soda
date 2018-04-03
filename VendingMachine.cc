#include "VendingMachine.h"
#include "Printer.h"
#include "NameServer.h"
#include "WATCard.h"
#include "MPRNG.h"

VendingMachine::VendingMachine( 
	Printer & prt, 
	NameServer & nameServer, 
	unsigned int id, 
	unsigned int sodaCost,
	unsigned int maxStockPerFlavour ):
	prt( prt ), nameServer( nameServer ),
	id ( id ), sodaCost( sodaCost ), 
	maxStockPerFlavour( maxStockPerFlavour ) {
		curStock = new unsigned int[SODA_FLAVOUR];
		for ( int i = 0; i < SODA_FLAVOUR; ++i ) {	// init the value
			curStock[i] = 0;
		}	// for
		flavourMap[lasmoi0] = 0;
		flavourMap[lasmoi1] = 1;
		flavourMap[lasmoi2] = 2;
		flavourMap[lasmoi3] = 3;
}

VendingMachine::~VendingMachine() {

	delete[] curStock;
}

unsigned int VendingMachine::getFlavourID( Flavours flavour ) {
	return flavourMap.at( flavour );
}

void VendingMachine::buy( Flavours flavour, WATCard & card ) {
	if ( !buyFlag ) {
		restockLock.wait();
	}	// if
	// check enough balance
	if ( card.getBalance() < sodaCost ) {
		_Throw Fund();
	}	// if
	// check enough flavour
	int flavourIndex = getFlavourID( flavour );
	if ( curStock[flavourIndex] == 0 ) {
		_Throw Stock();
	}	// if 

	unsigned int free = mprng( 4 );
	if ( !free ) {
		buyLock.signal();
		mainLock.wait();
	}	// if

}

void VendingMachine::main() {
	for ( ;; ) {
		_Accept( ~VendingMachine ) {
			break;
		}_Else {

		}
	}
}

unsigned int * VendingMachine::inventory(){
	buyFlag = false;
	return curStock;
}          

void VendingMachine::restocked() {
	// wake up the 
	while ( !buyLock.empty() ) {
		buyLock.signal();
	}	// while
	buyFlag = true;
}

_Nomutex unsigned int VendingMachine::cost(){
	return sodaCost;
}  

_Nomutex unsigned int VendingMachine::getId(){
	return id;
}