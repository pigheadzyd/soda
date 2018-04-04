#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>

#include "MPRNG.h"
#include "Truck.h"
#include "Printer.h"
#include "NameServer.h"
#include "BottlingPlant.h"
#include "VendingMachine.h"

using namespace std;

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

void Truck::print( string kind, int value1, int value2, int value3, int value4 ) {
	cout << '\t' << '\t' << '\t' << '\t' ;
	cout << kind << value1 << ',' << value2 << ',' << value3 << ',' << value4 << endl;
}


void Truck::print( string kind, unsigned int id, int value1, int value2, int value3, int value4 ) {
	cout << '\t' << '\t' << '\t' << '\t' ;
	cout << kind << ' ' << id << ' ' << value1 << ',' << value2 << ',' << value3 << ',' << value4 << endl;
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
		print( "product", product[0], product[1], product[2], product[3] );
		// get teh vending machine
		VendingMachine ** vendingMachineList =  nameServer.getMachineList();

		for ( unsigned int i = 0; i < numVendingMachines; ++i ) {			// for loop all the vending machines

			// get the vending machine and calculte the replenished request
			prt.print( Printer::Truck, 'd', curIndex, total );

			unsigned int * curStock = vendingMachineList[curIndex]->inventory();

			print( "Origin", curIndex, curStock[0], curStock[1], curStock[2], curStock[3] );
			maxTotal = SODA_FLAVOUR * maxStockPerFlavour - std::accumulate( curStock, curStock + SODA_FLAVOUR, 0 );

			for ( int j = 0; j < SODA_FLAVOUR; ++j ) {				// install all the flavour into the vending machine
				if ( !emptyStatus[j] ) {												// if the current flavour is not empty yet
					unsigned int rest = curStock[j];
					//cout << "flavour " << j << " stock " << curStock[j] << endl;
					//cout << "remain " << maxStockPerFlavour - rest << endl;
					//cout << "flavour " << j << " product " << product[j] << endl;
					unsigned int restockNum = std::min( maxStockPerFlavour - rest, product[j] );
					//cout << "restock " << restockNum << endl;
					// restore this kind flavour
					product[j] -= restockNum;
					curStock[j] += restockNum;
					// calculate the total number
					maxTotal = maxTotal - restockNum;
					total = total - restockNum;
				}	// if

				// if the current flavour is empty
				if ( product[j] == 0 ){
					emptyStatus[j] = true;
				}	// if
			}	// for

			// told the vending machine finish restock
			vendingMachineList[curIndex]->restocked();

			print( "After", curIndex, curStock[0], curStock[1], curStock[2], curStock[3] );
			print( "T after", product[0], product[1], product[2], product[3] );
			//	if it is not filled the vending machine
			if ( maxTotal > 0 ){
				prt.print( Printer::Truck, 'U', vendingMachineList[curIndex]->getId(), maxTotal );
			}	// if
			
			// if a product in the truck is empty
			if ( total == 0 ) {
				break;
			}	// if

			curIndex = ( curIndex + 1 ) % numVendingMachines;
		}	// for

		prt.print( Printer::Truck, 'D', curIndex, total );
		print( "Final", product[0], product[1], product[2], product[3] );
		// reset the value
		for ( int j = 0; j < SODA_FLAVOUR; ++j ) {
			emptyStatus[j] = false;
		}	// for
		if ( total == 0 ) {
			curIndex = ( curIndex + 1 ) % numVendingMachines;
		}	// if
	}	// for
	prt.print( Printer::Truck, 'F' );
}