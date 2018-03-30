#include <iostream>

#include "MPRNG.h"
#include "Truck.h"
#include "Printer.h"
#include "NameServer.h"
#include "BottlingPlant.h"

extern MPRNG mprng;

Truck::Truck( 
	Printer & prt, 
	NameServer & nameServer, 
	BottlingPlant & plant,
  unsigned int numVendingMachines, 
  unsigned int maxStockPerFlavour ): 
	prt( prt ), nameServer( nameServer ), plant( plant ), 
	numVendingMachines ( numVendingMachines ), 
	maxStockPerFlavour ( maxStockPerFlavour ) {
		std::cout << "create truck" << std::endl;
	}

void Truck:: main() {
	prt.print( Printer::Truck, 's' );
	for ( ;; ) {
		yield( mprng( 10 ) );
	}	// 
}