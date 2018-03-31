#include <iostream>
#include <algorithm>
#include <numeric>

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
	prt.print( Printer::Truck, 'S' );
	for ( ;; ) {
		yield( mprng( 1, 10 ) );
		// pick up shipment
		try {
			plant.getShipment( product );
			total = std::accumulate( product, product + SODA_FLAVOUR, 0 );
		} catch ( BottlingPlant::Shutdown & ) {
			break;
		}	// try
		prt.print( Printer::Truck, 'P', total );
		VendingMachine ** vendingMachineList =  nameServer.getMachineList();
		for ( int i = 0; i < numVendingMachines; ++i ) {			// for loop all the vending machines
			// get the vending machine and calculte the replenished request

			prt.print( Printer::Truck, 'd', i, total );
			unsigned int * curStock = vendingMachineList[curIndex]->inventory();
			maxTotal = SODA_FLAVOUR * maxStockPerFlavour - std::accumulate( curStock, curStock + SODA_FLAVOUR, 0 );

			for ( int j = 0; j < SODA_FLAVOUR; ++j ) {				// install all the flavour into the vending machine
				if ( !emptyStatus[j] ) {												// if the current flavour is not empty yet
					unsigned int rest = curStock[j];
					unsigned int restockNum = std::min( maxStockPerFlavour - rest, product[i] );
					// restore this kind flavour
					product[i] -= restockNum;
					curStock[i] += restockNum;
					// calculate the total number
					maxTotal -= restockNum;
					total -= restockNum;
				}	// if
				// if the current state is empty
				if ( product[i] == 0 ){
					emptyStatus[i] = true;
				}	// if
			}	// for
			vendingMachineList[curIndex]->restock();
			prt.print( Printer::Truck, 'U', id, maxTotal );
			curIndex = ( curIndex + 1 ) % numVendingMachines;
			// if a product in the truck is empty
			if ( total == 0 ) {
				// reset the value
				for ( int i = 0; i < SODA_FLAVOUR; ++i ) {
					emptyStatus = false;
				}	// for
				break;
			}	// if
		}	// for
		prt.print( Printer::Truck, 'D', curIndex, total );
	}	// for
}