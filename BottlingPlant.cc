#include <algorithm>

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
	shutdown( false ), SODA_FLAVOUR( 4 ) {
		product = new unsigned int [SODA_FLAVOUR];
	}

BottlingPlant::~BottlingPlant() {
	delete[] product;
}

void BottlingPlant::main() {
	prt.print( Printer::BottlingPlant, 'S' );

	for ( ;; ) {
		_Accept( ~BottlingPlant ) {
			shutdown = true;
			break;
		} _Else {
			int total = 0;
			for ( int i = 0; i < SODA_FLAVOUR; ++i ) {
				product[i] = mprng( maxShippedPerFlavour );
				total += product[i];
			}	// for
			prt.print( Printer::BottlingPlant, 'G', total );

			yield( timeBetweenShipments );

			_Accept( getShipment );
			prt.print( Printer::BottlingPlant, 'P' );
			// for ( int i = 0; i < SODA_FLAVOUR; ++i ) {
			// 	product[i] = 0;
			// }	// reset the value
		}	// _Accept
	}	// for
	_Accept ( getShipment );
}

void BottlingPlant::getShipment( unsigned int cargo[] ){
	if ( shutdown ) {
		_Throw Shutdown();
	}	// if
	std::copy( product, product + SODA_FLAVOUR, cargo );
}