#include <iostream>
#include <algorithm>
#include <numeric>

#include "MPRNG.h"
#include "Truck.h"
#include "Printer.h"
#include "NameServer.h"
#include "BottlingPlant.h"
#include "VendingMachine.h"

Truck::Truck( 
	Printer & prt, 
	NameServer & nameServer, 
	BottlingPlant & plant,
  unsigned int numVendingMachines, 
  unsigned int maxStockPerFlavour ): 
	prt( prt ), nameServer( nameServer ), plant( plant ), 
	numVendingMachines ( numVendingMachines ), 
	maxStockPerFlavour ( maxStockPerFlavour ),
	SODA_FLAVOUR( 4 ) {
		product = new unsigned int[SODA_FLAVOUR];
		emptyStatus = new bool[SODA_FLAVOUR];

		for ( int i = 0; i < SODA_FLAVOUR; ++i ) {
			emptyStatus[i] = false;
		}	// for
}

Truck::~Truck() {
	delete[] product;
	delete[] emptyStatus;
}

void Truck::main() {
	// start truck
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

		// get teh vending machine
		VendingMachine ** vendingMachineList =  nameServer.getMachineList();

		for ( unsigned int i = 0; i < numVendingMachines; ++i ) {			// for loop all the vending machines

			// get the vending machine and calculte the replenished request
			prt.print( Printer::Truck, 'd', curIndex, total );

			unsigned int * curStock = vendingMachineList[curIndex]->inventory();
			maxTotal = SODA_FLAVOUR * maxStockPerFlavour - std::accumulate( curStock, curStock + SODA_FLAVOUR, 0 );

			for ( int j = 0; j < SODA_FLAVOUR; ++j ) {				// install all the flavour into the vending machine
				if ( !emptyStatus[j] ) {												// if the current flavour is not empty yet
					unsigned int rest = curStock[j];
					unsigned int restockNum = std::min( maxStockPerFlavour - rest, product[j] );
					// restore this kind flavour
					product[j] -= restockNum;
					curStock[j] += restockNum;
					// calculate the total number
					maxTotal = maxTotal - restockNum;
					total = total - restockNum;
				}	// if

				// if the current state is empty
				if ( product[j] == 0 ){
					emptyStatus[j] = true;
				}	// if
			}	// for

			// told the vending machine finish restock
			vendingMachineList[curIndex]->restocked();

			//	if it is not filled the vending machine
			if ( maxTotal > 0 ){
				prt.print( Printer::Truck, 'U', vendingMachineList[curIndex]->getId(), maxTotal );
			}	// if
			
			// if a product in the truck is empty
			if ( total == 0 ) {
				// reset the value
				for ( int j = 0; j < SODA_FLAVOUR; ++j ) {
					emptyStatus[j] = false;
				}	// for
				break;
			}	// if

			curIndex = ( curIndex + 1 ) % numVendingMachines;
		}	// for

		prt.print( Printer::Truck, 'D', curIndex, total );
		if ( total == 0 ) {
			curIndex = ( curIndex + 1 ) % numVendingMachines;
		}	// if
	}	// for
	prt.print( Printer::Truck, 'F' );
}