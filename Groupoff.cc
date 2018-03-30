#include "Groupoff.h"
#include "WATCard.h"

Groupoff::Groupoff( 
	Printer & prt, 
	unsigned int numStudents, 
	unsigned int sodaCost, 
	unsigned int groupoffDelay ):
	prt( prt ),
	numStudents( numStudents ),
	sodaCost( sodaCost ),
	groupoffDelay( groupoffDelay ): {

}

void Groupoff::main() {
	prt.print( Print::Groupoff, 'S' );
}

WATCard::FWATCard giftCard(){
	return null;
};