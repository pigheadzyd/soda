#include "Groupoff.h"																				// Definition of Groupoff Task
#include "Printer.h"
#include "WATCard.h"
#include "MPRNG.h"

using namespace std;


//--------------------------------------------------------------------------------------------------------------------
// Starup and shutdown.
//--------------------------------------------------------------------------------------------------------------------
Groupoff::Groupoff( 
	Printer & prt, 
	unsigned int numStudents, 
	unsigned int sodaCost, 
	unsigned int groupoffDelay ):
	prt( prt ),
	numStudents( numStudents ),
	sodaCost( sodaCost ),
	groupoffDelay( groupoffDelay ) {
}	// Groupoff::Groupoff

Groupoff::~Groupoff() {
	for( unsigned int i = 0; i < cardList.size() ; i++ ) {			// Delete all the giftcards that have been send out
		delete cardList[i];
	}	// for
	prt.print( Printer::Groupoff, 'F' );
}	// Groupoff::~Groupoff


//--------------------------------------------------------------------------------------------------------------------
// Accept the student to require a future giftcard first, then randomly
// distributes a giftcard to a student.
//--------------------------------------------------------------------------------------------------------------------
void Groupoff::main() {
	prt.print( Printer::Groupoff, 'S' );

	for ( unsigned int i = 0 ; i < numStudents ; i++ ) {
		_Accept( giftCard ) {}																		// Recieve the giftcard call from all students
	}	// for

	unsigned int remainingStudents = numStudents;
	for ( ;; ) {
		_Accept( ~Groupoff ) {																		// Accept the call of destructor
			break;
		} _Else {
			assert( remainingStudents == giftcards.size() );
			int next = mprng( remainingStudents - 1 );							// Get the next giftcard to be sent

			WATCard * gc = new WATCard();														// Create a real WATCard and deposit the money
			cardList.push_back( gc );
			gc->deposit( sodaCost );

			yield( groupoffDelay );
			giftcards[next].delivery( gc );													// Send the WATCard out
			prt.print( Printer::Groupoff, 'D', sodaCost );

			giftcards.erase( giftcards.begin() + next );						// ???
			remainingStudents -= 1;
			if ( remainingStudents == 0 ) break;										// If all gift card is send out
		}	// _Accept
	}	// for
}	// Groupoff::main


//--------------------------------------------------------------------------------------------------------------------
// Create and return a new future WATCard when a student requires.
//--------------------------------------------------------------------------------------------------------------------
WATCard::FWATCard Groupoff::giftCard() {
	WATCard::FWATCard futureCard;
	giftcards.push_back( futureCard );
	return futureCard;
}	// Groupoff::giftCard
