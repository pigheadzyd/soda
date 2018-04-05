#include <algorithm>						// std::min
#include <numeric>							// std::accumulate

#include "MPRNG.h"
#include "Truck.h"							// Definition of Truck Task
#include "Printer.h"
#include "NameServer.h"
#include "BottlingPlant.h"
#include "VendingMachine.h"


//--------------------------------------------------------------------------------------------------------------------
// Starup and shutdown.
//--------------------------------------------------------------------------------------------------------------------
Truck::Truck( 
	Printer & prt, 
	NameServer & nameServer, 
	BottlingPlant & plant,
  unsigned int numVendingMachines, 
  unsigned int maxStockPerFlavour ): 
	prt( prt ), nameServer( nameServer ), plant( plant ), 
	numVendingMachines ( numVendingMachines ), 
	maxStockPerFlavour ( maxStockPerFlavour ),
	curIndex( 0 ), total( 0 ), SODA_FLAVOUR( 4 ) {
		product = new unsigned int[SODA_FLAVOUR];
		emptyStatus = new bool[SODA_FLAVOUR];

		for ( int i = 0; i < SODA_FLAVOUR; ++i ) {
			emptyStatus[i] = false;
		}	// for
}	// Truck::Truck

Truck::~Truck() {
	delete[] product;
	delete[] emptyStatus;
	prt.print( Printer::Truck, 'F' );
}	// Truck::~Truck


//--------------------------------------------------------------------------------------------------------------------
// Truck collect product from bottling plant and deliver to vending machine.
//--------------------------------------------------------------------------------------------------------------------
void Truck::main() {
	prt.print( Printer::Truck, 'S' );

	for ( ;; ) {
		yield( mprng( 1, 10 ) );
		
		try {																													// Pick up shipment
			plant.getShipment( product );
			total = std::accumulate( product, product + SODA_FLAVOUR, 0 );
		} catch ( BottlingPlant::Shutdown & ) {												// If the bottling plant is shutdown
			break;
		}	// try

		prt.print( Printer::Truck, 'P', total );
	
		VendingMachine ** vendingMachineList =  nameServer.getMachineList();

		for ( unsigned int i = 0; i < numVendingMachines; ++i ) {			// Loop all the vending machines

			prt.print( Printer::Truck, 'd', curIndex, total );
			unsigned int * curStock = vendingMachineList[curIndex]->inventory();

			// Get the vending machine and calculte the replenished request
			maxTotal = SODA_FLAVOUR * maxStockPerFlavour - std::accumulate( curStock, curStock + SODA_FLAVOUR, 0 );

			for ( int j = 0; j < SODA_FLAVOUR; ++j ) {								// Install all the flavour into the vending machine
				if ( !emptyStatus[j] ) {																// If the current flavour is not empty yet
					unsigned int rest = curStock[j];
					unsigned int restockNum = std::min( maxStockPerFlavour - rest, product[j] );
					product[j] -= restockNum;															// Restore this kind flavour
					curStock[j] += restockNum;														
					maxTotal = maxTotal - restockNum;											// Calculate the total number
					total = total - restockNum;
				}	// if

				if ( product[j] == 0 ){																	// If the current flavour is empty
					emptyStatus[j] = true;
				}	// if
			}	// for

			vendingMachineList[curIndex]->restocked();								// Notify the vending machine finish restock

			if ( maxTotal > 0 ){																			// If it is not filled the vending machine 
				prt.print( Printer::Truck, 'U', vendingMachineList[curIndex]->getId(), maxTotal );
			}	// if
			
			prt.print( Printer::Truck, 'D', curIndex, total );

			if ( total == 0 ) {																				// If truck is empty
				break;
			}	// if

			curIndex = ( curIndex + 1 ) % numVendingMachines;					// Move to next vending machine
		}	// for

		
		
		for ( int j = 0; j < SODA_FLAVOUR; ++j ) {									// Reset the value
			emptyStatus[j] = false;
		}	// for

		if ( total == 0 ) {																					// If it does not loop all the vending machine
			curIndex = ( curIndex + 1 ) % numVendingMachines;
		}	// if
	}	// for
}	// Truck::main