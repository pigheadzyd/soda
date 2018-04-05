#include "Parent.h"										// Definition of Bottling Plant Task
#include "Printer.h"
#include "Bank.h"
#include "MPRNG.h"


//--------------------------------------------------------------------------------------------------------------------
// Starup and shutdown.
//--------------------------------------------------------------------------------------------------------------------
Parent::Parent( 
	Printer & prt, 
	Bank & bank, 
	unsigned int numStudents, 
	unsigned int parentalDelay ): 
	prt( prt ), bank( bank ),
	numStudents( numStudents ), 
	parentalDelay( parentalDelay ) {
}	// Parent::Parent

Parent::~Parent() {
	prt.print( Printer::Parent, 'F' );
}	// Parent::~Parent

//--------------------------------------------------------------------------------------------------------------------
// Continue sending money to random student by random amount
//--------------------------------------------------------------------------------------------------------------------
void Parent::main() {
	prt.print( Printer::Parent, 'S' );

	for ( ;; ) {
		_Accept ( ~Parent ) {									// Accept the destuctor to break the loop
			break;
		} _Else {
			yield( parentalDelay );
			unsigned int id = mprng( numStudents - 1 );
			unsigned int amount = mprng ( 1, 3 );

			bank.deposit( id, amount );					// Deposit the amount to the student's balance
			prt.print( Printer::Parent, 'D', id, amount );
		}	// _Accept
	}	// for
}	// Parent::main