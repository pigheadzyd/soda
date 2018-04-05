#include <algorithm>														// Defines std::copy

#include "BottlingPlant.h"											// Definition of Bottling Plant Task
#include "Printer.h"
#include "NameServer.h"
#include "Truck.h"
#include "MPRNG.h"


//--------------------------------------------------------------------------------------------------------------------
// Starup and shutdown.
//--------------------------------------------------------------------------------------------------------------------
BottlingPlant::BottlingPlant( 
	Printer & prt, 
	NameServer & nameServer, 
	unsigned int numVendingMachines,
  unsigned int maxShippedPerFlavour, 
  unsigned int maxStockPerFlavour,
  unsigned int timeBetweenShipments ): 
	prt( prt ), nameServer( nameServer ),
	numVendingMachines( numVendingMachines ),
	maxShippedPerFlavour( maxShippedPerFlavour ),
	maxStockPerFlavour( maxStockPerFlavour ),
	timeBetweenShipments( timeBetweenShipments ),
	shutdown( false ), SODA_FLAVOUR( 4 ) {
		product = new unsigned int [SODA_FLAVOUR];
}

BottlingPlant::~BottlingPlant() {
	delete truck;
	delete[] product;
	prt.print( Printer::Kind::BottlingPlant, 'F' );
}


//--------------------------------------------------------------------------------------------------------------------
// Loop to generate products until the destroctor is called.
//--------------------------------------------------------------------------------------------------------------------
void BottlingPlant::main() {
	prt.print( Printer::BottlingPlant, 'S' );
	// create a new truck
	truck = new Truck( prt, nameServer, *this, numVendingMachines, maxStockPerFlavour );
	
	for ( ;; ) {
		try {
			_Accept( ~BottlingPlant ) {											// Accept the destuctor to break the loop
				shutdown = true;
				break;
			} _Else {
				int total = 0;
				for ( int i = 0; i < SODA_FLAVOUR; ++i ) {		// For each kind of flavour randomly generate the product
					product[i] = mprng( maxShippedPerFlavour );
					total += product[i];
				}	// for

				prt.print( Printer::BottlingPlant, 'G', total );

				yield( timeBetweenShipments );

				_Accept( getShipment );												// Do not proceed to the next product until the truck pick up
				prt.print( Printer::BottlingPlant, 'P' );
			}	// _Accept
		} catch( uMutexFailure::RendezvousFailure ) {
		}	// try
	}	// for

	try {
		_Accept ( getShipment );													// To inform the truck the bottling plant is shutdown
	} catch( uMutexFailure::RendezvousFailure ) {				// Catch the exception
	}	// try
}	// BottlingPlant::main


//--------------------------------------------------------------------------------------------------------------------
// Move the product onto the truck.
//--------------------------------------------------------------------------------------------------------------------
void BottlingPlant::getShipment( unsigned int cargo[] ){
	if ( shutdown ) {																		// If the bottling plant is shutdown
		_Throw Shutdown();																// Throw an exception
	}	// if
	std::copy( product, product + SODA_FLAVOUR, cargo );// Copy the product into the truck
}	// BottlingPlant::getShipment

