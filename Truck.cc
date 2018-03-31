#include <iostream>
#include <algorithm>

#include "MPRNG.h"
#include "Truck.h"
#include "Printer.h"
#include "NameServer.h"
#include "BottlingPlant.h"
#include "VendingMachine.h"

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
		for ( int i = 0; i < SODA_FLAVOUR; ++i ) {
			emptyStatus[i] = false;
		}
}

void Truck::main() {
	prt.print( Printer::Truck, 's' );
	for ( ;; ) {
		yield( mprng( 1, 10 ) );
		try {
			plant.getShipment( product );
		} catch ( BottlingPlant::Shutdown & ) {
			break;
		}	// try
		VendingMachine ** vendingMachineList =  nameServer.getMachineList();
		for ( int i = 0; i < numVendingMachines; ++i ) {
			if ( !emptyStatus[i] ) {
				unsigned int * curStock = vendingMachineList[curIndex]->inventory();
				for ( int i = 0; i < SODA_FLAVOUR; ++i ) {
					unsigned int rest = curStock[i];
					unsigned int restockNum = std::min( maxStockPerFlavour - rest, product[i] );
					product[i] -= restockNum;
					curStock[i] += restockNum;
					// if the current flavour is empty
					if ( product[i] == 0 ) {
						empty++;
						emptyStatus[i] = true;
					}	// if
				}	// for
			}	// if
			vendingMachineList[curIndex]->restock();
			curIndex = ( curIndex + 1 ) % numVendingMachines;
			// if a product in the truck is empty
			if ( empty == SODA_FLAVOUR ) {
				empty = 0;
				for ( int i = 0; i < SODA_FLAVOUR; ++i ) {
					emptyStatus = false;
				}	// for
				break;
			} // if
		}	// for
	}	// for
}