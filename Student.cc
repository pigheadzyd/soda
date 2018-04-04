#include "Student.h"
#include "Printer.h"
#include "NameServer.h"
#include "WATCardOffice.h"
#include "Groupoff.h"
#include "VendingMachine.h"
#include "MPRNG.h"

// extern MPRNG mprng;

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

  numOfPurchases = mprng(1, maxPurchases);
  favouriteFlavourInt = mprng(3);
  favouriteFlavour = (VendingMachine::Flavours) favouriteFlavourInt;  // four favourite flavours

}

void  Student::main() {
  prt.print( Printer::Kind::Student, id, 'S', favouriteFlavourInt, numOfPurchases );
  watcard = cardOffice.create( id, 5 );
  groupOffCard = groupoff.giftCard();
  vendingMachine = nameServer.getMachine( id );
  prt.print( Printer::Kind::Student, id, 'V', vendingMachine->getId());
  for(unsigned int i = 0; i < numOfPurchases; ) {
    prt.print( Printer::Kind::Student, id, '?');
    _Select( groupOffCard ) {
      try {
        prt.print( Printer::Kind::Student, id, '1');
        curGiftCard = groupOffCard();                         // all gift cards are deleted by group off at last
        prt.print( Printer::Kind::Student, id, '2');
        yield(mprng(1,10));
        vendingMachine->buy( favouriteFlavour, *curGiftCard );
        prt.print( Printer::Kind::Student, id, '3');
        groupOffCard.reset();
        prt.print( Printer::Kind::Student, id, 'G', favouriteFlavourInt, curGiftCard->getBalance() );
        i += 1;
        if ( watcard.available() ) { 
          try {                           // handle the case that Gifcard purchases the last bottle
            curCard = watcard();
          } catch ( WATCardOffice::Lost lostEvent ) {
            // curCard = NULL;
          }
        }
      } catch ( VendingMachine::Free freeEvent ) {
        prt.print( Printer::Kind::Student, id, '4');
        prt.print( Printer::Kind::Student, id, 'a', favouriteFlavourInt, curGiftCard->getBalance() );
        yield(4);
        i += 1;                                           // +1 because one consumed
      } catch ( VendingMachine::Stock stockEvent ) {
        vendingMachine = nameServer.getMachine( id );     // get the new machine
        prt.print( Printer::Kind::Student, id, 'V', vendingMachine->getId());
      }

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
  if ( curCard != NULL ) {
    delete curCard;
    prt.print( Printer::Kind::Student, id, 'f');
  }
  curCard = NULL;
  prt.print( Printer::Kind::Student, id, 'F');
} // main