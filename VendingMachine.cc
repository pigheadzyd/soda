#include "VendingMachine.h"										// Definition of Vending Machine Task
#include "Printer.h"
#include "NameServer.h"
#include "WATCard.h"
#include "MPRNG.h"


//--------------------------------------------------------------------------------------------------------------------
// Starup and shutdown.
//--------------------------------------------------------------------------------------------------------------------
VendingMachine::VendingMachine( 
	Printer & prt, 
	NameServer & nameServer, 
	unsigned int id, 
	unsigned int sodaCost,
	unsigned int maxStockPerFlavour ):
	prt( prt ), nameServer( nameServer ),
	id ( id ), sodaCost( sodaCost ), 
	maxStockPerFlavour( maxStockPerFlavour ),
	SODA_FLAVOUR( 4 ) {
		curStock = new unsigned int[SODA_FLAVOUR];
		for ( int i = 0; i < SODA_FLAVOUR; ++i ) {	// Init the value
			curStock[i] = 0;
		}	// for
		// Map the flavour with index
		flavourMap[lasmoi0] = 0;
		flavourMap[lasmoi1] = 1;
		flavourMap[lasmoi2] = 2;
		flavourMap[lasmoi3] = 3;

		nameServer.VMregister( this );							// Register itself in nameserver
}	// VendingMachine::VendingMachine

VendingMachine::~VendingMachine() {
	prt.print( Printer::Vending, id, 'F' );
	delete[] curStock;
}	// VendingMachine::~VendingMachine


//--------------------------------------------------------------------------------------------------------------------
// Get the flavour index by spcific flavour.
//--------------------------------------------------------------------------------------------------------------------
unsigned int VendingMachine::getFlavourId( Flavours flavour ) {
	return flavourMap.at( flavour );
}	// VendingMachine::getFlavourId


//--------------------------------------------------------------------------------------------------------------------
// Student buy the soda using WATCard.
//--------------------------------------------------------------------------------------------------------------------
void VendingMachine::buy( Flavours flavour, WATCard & card ) {
	if ( card.getBalance() < sodaCost ) {			// Check enough balance
		_Throw Funds();
	}	// if

	int flavourIndex = getFlavourId( flavour );
	if ( curStock[flavourIndex] == 0 ) {		 // Check enough flavour
		_Throw Stock();
	}	// if 

	unsigned int free = mprng( 4 );
	if ( free == 0 ) {											 // If this purchase is free
		curStock[flavourIndex]--;
		_Throw Free();
	}	// if

	card.withdraw( sodaCost );							 // If it is a normal purchase
	curStock[flavourIndex]--;
	prt.print( Printer::Vending, id, 'B', flavourIndex, curStock[flavourIndex] );
}	// VendingMachine::buy


//--------------------------------------------------------------------------------------------------------------------
// Waiting student to buy soda or truck to restock.
//--------------------------------------------------------------------------------------------------------------------
void VendingMachine::main() {
	prt.print( Printer::Vending, id, 'S', sodaCost );

	for ( ;; ) {
		try {
			_Accept( ~VendingMachine ) {				// Accept the destuctor to break the loop
				break;
			} or _Accept( buy ) {								// If student come to buy soda

			} or _Accept( inventory ) {					// If truck begins to restock

				prt.print( Printer::Vending, id, 'r' );

				_Accept ( restocked ) {						// Waiting until truck finish restock
					prt.print( Printer::Vending, id, 'R' );
				}	// _Accept

			}	// _Accept
		} catch ( uMutexFailure::RendezvousFailure ) {			// Catch exception raise in buy
		}	// try
	}	// for
}	// VendingMachine::main


//--------------------------------------------------------------------------------------------------------------------
// Give the current stock infomation to truck.
//--------------------------------------------------------------------------------------------------------------------
unsigned int * VendingMachine::inventory(){
	return curStock;
} // VendingMachine::inventory


//--------------------------------------------------------------------------------------------------------------------
// Truck will notify vending machine by restocked when the restock is completed.
//--------------------------------------------------------------------------------------------------------------------
void VendingMachine::restocked() {
}	// VendingMachine::restocked


//--------------------------------------------------------------------------------------------------------------------
// Return the soda price.
//--------------------------------------------------------------------------------------------------------------------
_Nomutex unsigned int VendingMachine::cost(){
	return sodaCost;
}	// VendingMachine::cost


//--------------------------------------------------------------------------------------------------------------------
// Return the current vending machine id.
//--------------------------------------------------------------------------------------------------------------------
_Nomutex unsigned int VendingMachine::getId(){
	return id;
}	// VendingMachine::getId