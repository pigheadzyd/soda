#include "WATCardOffice.h"
#include "MPRNG.h"
#include "Printer.h"
#include "Bank.h"
#include "WATCard.h"

using namespace std;

/************************ WATCardOffice:Courier class ************************/
WATCardOffice::Courier::Courier( Printer & prt, Bank & bank, WATCardOffice & office, unsigned int id ) :
prt( prt ), bank( bank ), office( office ), id( id ) {

}

WATCardOffice::Courier::~Courier() {
}

void WATCardOffice::Courier::main() {
	prt.print( Printer::Kind::Courier, id, 'S' );
	for (;;) {
		_Accept (~Courier) {
			break;
		} _Else {
			WATCardOffice::Job * job = office.requestWork();				// here the job is always asking for money
			if( job == NULL ) break;															// if job is null, that means office is closed
			WATCard * card = job->card;
			unsigned int studentId = job->studentId;
			unsigned int amount = job->amount;
			prt.print( Printer::Kind::Courier, id, 't', studentId, amount );
			bank.withdraw( studentId, amount );											// should wait until fund is sufficient
			card->deposit(amount);
			if( mprng(5) == 0 ) {																		// card lost
				// print message here?
				job->result.exception( new WATCardOffice::Lost() );
				delete card;
				prt.print( Printer::Kind::Courier, id, 'L', studentId );
			} else {																								// card delivered
				job->result.delivery( card );
				prt.print( Printer::Kind::Courier, id, 'T', studentId, amount );
			}
			delete job;
		}
		
	}
	prt.print( Printer::Kind::Courier, id, 'F' );
}

/************************ WATCardOffice class ************************/
WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ) : 
prt( prt ), bank( bank ), numCouriers( numCouriers ) {
  courierPool = new Courier*[numCouriers]; 
  for ( unsigned int i = 0; i < numCouriers; i++ ){
    courierPool[i] = new Courier( prt, bank, *this, i );
  }
}

WATCardOffice::~WATCardOffice() {
	while( !jobs.empty() ) {
		Job * j = jobs.front();
		jobs.pop();
		// if ( j->card != NULL ) delete j->card;
		delete j;
	}
	for ( ; ; ) {
		_Accept( requestWork ) { 									// wake up all blocked
		} _Else {
			break;
		}
	}
	for ( unsigned int i = 0; i < numCouriers; i++ ) {
    delete courierPool[i];
  }
	delete courierPool;
	prt.print( Printer::Kind::WATCardOffice, 'F' );
}

/**  
  * Create an new watcard for student and return the future
  */
WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	WATCard * newCard = new WATCard();
	Job * newJob = new Job(sid, amount, newCard);
	jobs.push(newJob);
	prt.print( Printer::Kind::WATCardOffice, 'C', sid, amount );
	return newJob->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ){
	Job * newJob = new Job(sid, amount, card);
	jobs.push(newJob);
	prt.print( Printer::Kind::WATCardOffice, 'T', sid, amount );
	return newJob->result;
}

WATCardOffice::Job * WATCardOffice::requestWork(){
	if ( jobs.empty() ) return NULL;											// if null is returned that means everything is tearing down.
	Job * j = jobs.front();
	jobs.pop();

	prt.print( Printer::Kind::WATCardOffice, 'W' );
	return j;
}

void WATCardOffice::main() {
	prt.print( Printer::Kind::WATCardOffice, 'S' );
	for (;;) {
		_Accept( ~WATCardOffice ) {

			break;
		} or _When( !jobs.empty() ) _Accept( requestWork ) {

		} or _Accept( create ) {

		} or _Accept( transfer ) {

		}
	}
}
