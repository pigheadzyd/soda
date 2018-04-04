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

} // Student::Student

Student::~Student() {
  prt.print( Printer::Kind::Student, id, 'F');
} // Student::~Student


//--------------------------------------------------------------------------------------------------------------------
// Handle the student to buy the amount of soda with their favourite flavour.
// With the situation using giftcard or WATCard to buy
//--------------------------------------------------------------------------------------------------------------------
void Student::main() {

  prt.print( Printer::Kind::Student, id, 'S', favouriteFlavourInt, numOfPurchases );
  watcard = cardOffice.create( id, 5 );                  // Create a new WATCard
  groupOffCard = groupoff.giftCard();                    // Require for a giftcard

  vendingMachine = nameServer.getMachine( id );     
  prt.print( Printer::Kind::Student, id, 'V', vendingMachine->getId() );

  for( unsigned int i = 0; i < numOfPurchases; ) {
    _Select( groupOffCard ) {                             // Case of using giftcard to purchase???
      try {
        curCard = groupOffCard();                         // Set the purchase cardtype
        yield( mprng( 1,10 ) );

        vendingMachine->buy( favouriteFlavour, *curCard );
        prt.print( Printer::Kind::Student, id, 'G', favouriteFlavourInt, curCard->getBalance() );

        i += 1;                                           // Successfully purchase without special case
        groupOffCard.reset();
        curCard = NULL;
      } catch ( VendingMachine::Free freeEvent ) {        // If this purchase is free
        prt.print( Printer::Kind::Student, id, 'a', favouriteFlavourInt, curCard->getBalance() );
        yield( 4 );
        i += 1;                                           
      } catch ( VendingMachine::Stock stockEvent ) {      // If this flavour in this vending machine is out of stock
        vendingMachine = nameServer.getMachine( id );     // Get the new machine
        prt.print( Printer::Kind::Student, id, 'V', vendingMachine->getId() );
      } // try
      // ??? if no bug then delete (next line)
      // if ( curGiftCard->getBalance() == 0 ) groupOffCard.reset();
    } or _Select( watcard ) {                             // Case of using WATCard to purchase??? 
      try {
        curCard = watcard();                              // Set the purchase cardtype
        yield( mprng( 1, 10 ) );
        vendingMachine->buy( favouriteFlavour, *curCard );
        prt.print( Printer::Kind::Student, id, 'B', favouriteFlavourInt, curCard->getBalance() );
        i += 1;

      } catch ( WATCardOffice::Lost lostEvent ) {         // If the WATCarad is lost
        prt.print( Printer::Kind::Student, id, 'L' );
        watcard = cardOffice.create( id, 5 );             // Get a new one

      } catch ( VendingMachine::Free freeEvent ) {        // If this purchase is free
        prt.print( Printer::Kind::Student, id, 'A', favouriteFlavourInt, curCard->getBalance() );
        yield(4);
        i += 1;  
      } catch ( VendingMachine::Stock stockEvent ) {      // If this flavour in this vending machine is out of stock
        vendingMachine = nameServer.getMachine( id );     // Get the new machine
        prt.print( Printer::Kind::Student, id, 'V', vendingMachine->getId() );

      } catch ( VendingMachine::Funds fundEvent ) {       // If there is not enough money in this WATCard
        watcard = cardOffice.transfer( id, 5 + vendingMachine->cost(), curCard );
      } // try
    } // _Select

  } // for
  try {                                                   // Handle the case that Gifcard purchases the last bottle
    curCard = watcard();
    delete curCard;
  } catch ( WATCardOffice::Lost lostEvent ) {
  } // try

} // Student::main