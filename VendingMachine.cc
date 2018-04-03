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
	prt.print( Printer::Vending, 'F' );
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
	if ( free ) {
		_Throw Free();
	}	// if
	card.withdraw( sodaCost );
	curStock[flavourIndex]--;
	prt.print( Printer::Vending, 'B', flavourIndex, curStock[flavourIndex] );
}

void VendingMachine::main() {
	prt.print( Printer::Vending, 'S', sodaCost );
	for ( ;; ) {
		_Accept( ~VendingMachine ) {
			break;
		} or _Accept( buy ) {

		} or _Accept( inventory ) {
			prt.print( Printer::Vending, 'r' );
			_Accept ( restocked ) {
				prt.print( Printer::Vending, 'R' );
			}
		}
	}
}

unsigned int * VendingMachine::inventory(){
	return curStock;
}          

void VendingMachine::restocked() {
	// wake up the 
}

_Nomutex unsigned int VendingMachine::cost(){
	return sodaCost;
}  

_Nomutex unsigned int VendingMachine::getId(){
	return id;
}