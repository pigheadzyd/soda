#include <iostream>

#include "Student.h"                                // Definition of Bottling Plant Task
#include "Printer.h"
#include "NameServer.h"
#include "WATCardOffice.h"
#include "Groupoff.h"
#include "VendingMachine.h"
#include "MPRNG.h"

using namespace std;


//--------------------------------------------------------------------------------------------------------------------
// Starup and shutdown.
//--------------------------------------------------------------------------------------------------------------------
Student::Student( 
	Printer & prt, 
	NameServer & nameServer, 
	WATCardOffice & cardOffice, 
	Groupoff & groupoff, 
	unsigned int id, 
	unsigned int maxPurchases ): 
	prt( prt ), nameServer( nameServer ), 
	cardOffice( cardOffice ), groupoff( groupoff ),
	id ( id ), maxPurchases( maxPurchases ){

  numOfPurchases = mprng( 1, maxPurchases );        // Determine the number will purchase
  favouriteFlavourInt = mprng( 3 );                 // Determine the favourite flavour
  favouriteFlavour = ( VendingMachine::Flavours ) favouriteFlavourInt;  // Four favourite flavours

}

Student::~Student() {
  prt.print( Printer::Kind::Student, id, 'F');
}

void  Student::main() {

  prt.print( Printer::Kind::Student, id, 'S', favouriteFlavourInt, numOfPurchases );
  watcard = cardOffice.create( id, 5 );
  groupOffCard = groupoff.giftCard();
  vendingMachine = nameServer.getMachine( id );
  prt.print( Printer::Kind::Student, id, 'V', vendingMachine->getId());
  for( unsigned int i = 0; i < numOfPurchases; ) {
    _Select( groupOffCard ) {
      try {
        curCard = groupOffCard();                         // all gift cards are deleted by group off at last
        yield(mprng(1,10));
        vendingMachine->buy( favouriteFlavour, *curCard );
        prt.print( Printer::Kind::Student, id, 'G', favouriteFlavourInt, curCard->getBalance() );
        i += 1;
        groupOffCard.reset();
        curCard = NULL;
      } catch ( VendingMachine::Free freeEvent ) {
        prt.print( Printer::Kind::Student, id, 'a', favouriteFlavourInt, curCard->getBalance() );
        yield(4);
        i += 1;                                           // +1 because one consumed
      } catch ( VendingMachine::Stock stockEvent ) {
        vendingMachine = nameServer.getMachine( id );     // get the new machine
        prt.print( Printer::Kind::Student, id, 'V', vendingMachine->getId());
      }
      // if ( curGiftCard->getBalance() == 0 ) groupOffCard.reset();
    } or _Select( watcard ) {
      try {
        curCard = watcard();                              // this card should be deleted in gift card class?
        yield( mprng(1, 10 ) );
        vendingMachine->buy( favouriteFlavour, *curCard );
        prt.print( Printer::Kind::Student, id, 'B', favouriteFlavourInt, curCard->getBalance() );
        i += 1;

      } catch ( WATCardOffice::Lost lostEvent ) {
        prt.print( Printer::Kind::Student, id, 'L');
        watcard = cardOffice.create( id, 5 );

      } catch ( VendingMachine::Free freeEvent ) {
        prt.print( Printer::Kind::Student, id, 'A', favouriteFlavourInt, curCard->getBalance() );
        yield(4);
        i += 1;  
      } catch ( VendingMachine::Stock stockEvent ) {
        vendingMachine = nameServer.getMachine( id );     // get the new machine
        prt.print( Printer::Kind::Student, id, 'V', vendingMachine->getId());

      } catch ( VendingMachine::Funds fundEvent ) {       // transfer
        watcard = cardOffice.transfer( id, 5 + vendingMachine->cost(), curCard );

      } // try
    } // select

  } // for
  try {                           // handle the case that Gifcard purchases the last bottle
    curCard = watcard();
    delete curCard;
  } catch ( WATCardOffice::Lost lostEvent ) {
  }
} // main