#include "Parent.h"
#include "Printer.h"
#include "Bank.h"
#include "MPRNG.h"

extern MPRNG mprng;

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


void Parent::main() {
	prt.print( Printer::Parent, 'S' );
	for ( ;; ) {
		_Accept ( ~Parent ) {		// allow to break the loop
			break;
		} _Else {
			yield( parentalDelay );
			unsigned int id = mprng( numStudents - 1 );
			unsigned int amount = mprng ( 1, 3 );
			bank.deposit( id, amount );
			prt.print( Printer::Parent, 'D', id, amount );
		}	// _Accept
	}	// for
}	// void Parent::main