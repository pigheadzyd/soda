#include "WATCardOffice.h"																	// Definition of WATCardOffice Task
#include "MPRNG.h"
#include "Printer.h"
#include "Bank.h"
#include "WATCard.h"

using namespace std;

/************************ WATCardOffice:Courier class ************************/

//--------------------------------------------------------------------------------------------------------------------
// Starup and shutdown.
//--------------------------------------------------------------------------------------------------------------------
WATCardOffice::Courier::Courier( Printer & prt, Bank & bank, WATCardOffice & office, unsigned int id ) :
prt( prt ), bank( bank ), office( office ), id( id ) {
}	// WATCardOffice::Courier::Courier

WATCardOffice::Courier::~Courier() {
	prt.print( Printer::Kind::Courier, id, 'F' );
}	// WATCardOffice::Courier::~Courier



//--------------------------------------------------------------------------------------------------------------------
// Starup and shutdown.
//--------------------------------------------------------------------------------------------------------------------
void WATCardOffice::Courier::main() {
	prt.print( Printer::Kind::Courier, id, 'S' );

	for ( ;; ) {
		_Accept ( ~Courier ) {
			break;
		} _Else {
			WATCardOffice::Job * job = office.requestWork();				// Here the job assigned to this courier
			if ( job == NULL ) break;																// If job is null, that means office is closed

			WATCard * card = job->card;															// Get the card within the job
			unsigned int studentId = job->studentId;
			unsigned int amount = job->amount;
			prt.print( Printer::Kind::Courier, id, 't', studentId, amount );
			bank.withdraw( studentId, amount );											// Wait until fund is sufficient
			card->deposit( amount );
			if( mprng( 5 ) == 0 ) {																	// If the card is lost
				job->result.exception( new WATCardOffice::Lost() );
				delete card;																					// Card is deleted because it is lost
				prt.print( Printer::Kind::Courier, id, 'L', studentId );
			} else {																								// Card delivered to student and ready to use
				job->result.delivery( card );
				prt.print( Printer::Kind::Courier, id, 'T', studentId, amount );
			}	// if

			delete job;
		}	// _Accept
	}	// for
}	// WATCardOffice::Courier::main

/************************ WATCardOffice class ************************/


//--------------------------------------------------------------------------------------------------------------------
// Starup and shutdown.
//--------------------------------------------------------------------------------------------------------------------
WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ) : 
prt( prt ), bank( bank ), numCouriers( numCouriers ) {
  for ( unsigned int i = 0; i < numCouriers; i++ ){						// Create the couriers
    courierPool.push_back( new Courier( prt, bank, *this, i ) );
  }	// for
}	// WATCardOffice::WATCardOffice


WATCardOffice::~WATCardOffice() {
	while( !jobs.empty() ) {																		// Remove jobs from job queue as they are no longer needed
		Job * j = jobs.front();
		jobs.pop();
		if ( j->card != NULL ) {																	// Delete the card that stored with job
			delete j->card;																					// as the card neither get to courier nor get to student
		}	// if
		delete j;
	}	// while

	for ( ;; ) {
		_Accept( requestWork ) { 																	// Wake up all blocked
		} _Else {
			break;
		}	// _Accept
	}	// for

	for ( unsigned int i = 0; i < numCouriers; i++ ) {
    delete courierPool[i];
  }	// for
	prt.print( Printer::Kind::WATCardOffice, 'F' );
}	// WATCardOffice::~WATCardOffice


//--------------------------------------------------------------------------------------------------------------------
// Create an new watcard for student and return the future.
//--------------------------------------------------------------------------------------------------------------------
WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	WATCard * newCard = new WATCard();
	Job * newJob = new Job( sid, amount, newCard );								// Create a new job of creating a new watcard
	jobs.push( newJob );
	prt.print( Printer::Kind::WATCardOffice, 'C', sid, amount );
	return newJob->result;
}	// WATCardOffice::create


//--------------------------------------------------------------------------------------------------------------------
// Transfer the money for student and return the future.
//--------------------------------------------------------------------------------------------------------------------
WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ){
	Job * newJob = new Job(sid, amount, card);
	jobs.push( newJob );																					// Create a new job of transferring money to an existing card
	prt.print( Printer::Kind::WATCardOffice, 'T', sid, amount );
	return newJob->result;
}	// WATCardOffice::transfer


//--------------------------------------------------------------------------------------------------------------------
// Called by couriers to get their work when they are available.
//--------------------------------------------------------------------------------------------------------------------
WATCardOffice::Job * WATCardOffice::requestWork(){
	if ( jobs.empty() ) return NULL;															// If null is returned that means everything is tearing down.
	Job * j = jobs.front();
	jobs.pop();

	prt.print( Printer::Kind::WATCardOffice, 'W' );
	return j;
}	// WATCardOffice::requestWork


//--------------------------------------------------------------------------------------------------------------------
// Office waiting for student create new card or transfer money or courier take their job.
//--------------------------------------------------------------------------------------------------------------------
void WATCardOffice::main() {
	prt.print( Printer::Kind::WATCardOffice, 'S' );

	for ( ;; ) {
		_Accept( ~WATCardOffice ) {													 			// Accept the destuctor to break the loop
			break;
		} or _When( !jobs.empty() ) _Accept( requestWork ) { 			// Only Accept requestWork if there is a work
		} or _Accept( create ) {																	// Accept if student need to create new card
		} or _Accept( transfer ) {																// Accept if student need transfer money
		}	// _Accept
	}	// for
}	// WATCardOffice::main
