#include "Student.h"
#include "Printer.h"
#include "NameServer.h"
#include "WATCardOffice.h"
#include "Groupoff.h"
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
  favouriteFlavour = (VendingMachine::Flavours) mprng(3);                  // four favourite flavours

}

void  Student::main() {
  prt.print( Printer::Kind::Student, id, 'S', numOfPurchases, (unsigned int)favouriteFlavour );
  watcard = WATCardOffice.create( id, 5 );
  groupOffCard = groupoff.giftCard();
  vendingMachine = nameServer.getMachine();


  for(unsigned int i = 0; i < maxPurchases; ) {
    _Select( groupOffCard ) {
      try {
        curCard = groupOffCard();           // this card should be deleted in gift card class?
        vendingMachine.buy( favouriteFlavour, *curCard );

      } catch () {

      }

    } or _Select( watcard ) {

    }

  }

}