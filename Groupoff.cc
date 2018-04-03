#include "Groupoff.h"
#include "Printer.h"
#include "WATCard.h"
#include "MPRNG.h"

using namespace std;

Groupoff::Groupoff( 
	Printer & prt, 
	unsigned int numStudents, 
	unsigned int sodaCost, 
	unsigned int groupoffDelay ):
	prt( prt ),
	numStudents( numStudents ),
	sodaCost( sodaCost ),
	groupoffDelay( groupoffDelay ) {
}

Groupoff::~Groupoff() {}

void Groupoff::main() {
	prt.print( Printer::Groupoff, 'S' );
	for ( unsigned int i = 0 ; i < numStudents ; i++ ) {
		_Accept( giftCard ) {}											// recieve the giftcard call from all students
	}
	unsigned int remainingStudents = numStudents;
	for ( ;; ) {
		_Accept( ~Groupoff ) {
			break;
		} _Else {
			assert( remainingStudents == giftcards.size() );
			int next = mprng( remainingStudents - 1 );			// get the next giftcard to be sent
			WATCard * gc = new WATCard();
			gc->deposit( sodaCost );
			yield( groupoffDelay );
			giftcards[next]->delivery( gc );
			giftcards.remove( giftcards[next] );
			remainingStudents -= 1;
			if ( remainingStudents == 0 ) break;				// all gift card is send out
		}
	}

}

WATCard::FWATCard Groupoff::giftCard(){
	WATCard::FWATCard futureCard;
	giftcards.pushback( futureCard );
	return futureCard;
};