#include "BottlingPlant.h"
#include "Printer.h"
#include "NameServer.h"
#include "MPRNG.h"

extern MPRNG mprng;

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
	shutdown( false ){}


void BottlingPlant::main() {
	prt.print( Printer::BottlingPlant, 'S' );

	for ( ;; ) {
		
	}	// for
}

void getShipment( unsigned int cargo[] ){
	if ( shutdown ) {
		_Throw shutdown();
	}
}