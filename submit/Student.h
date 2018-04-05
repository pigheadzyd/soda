//--------------------------------------------------------------------------------------------------------------------
// Define the interface to the Student Task for the vending machine system.
//--------------------------------------------------------------------------------------------------------------------
#ifndef __STUDENT_H__
#define __STUDENT_H__
#include "VendingMachine.h"
#include "WATCard.h"

_Monitor Printer;
_Task NameServer;
_Task WATCardOffice;
_Task Groupoff;

_Task Student {
	public:
		Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
             unsigned int id, unsigned int maxPurchases );
		~Student();
	private:
		Printer & prt;															// Current printer
		NameServer & nameServer;										// Current nameServer
		WATCardOffice & cardOffice;									// Current cardOffice
		Groupoff & groupoff;												// Current groupoff
		unsigned int id;														// Identity of student
		unsigned int maxPurchases;									// Max number of a purchase
    void main();																// Main body of task

    unsigned int numOfPurchases;								// Number of soda that the  student purchase 
    VendingMachine::Flavours favouriteFlavour;	// Favourite flavour of the 
    unsigned int favouriteFlavourInt;						// Int value of favourite flavour
    VendingMachine * vendingMachine;						// Student current using vending machine

    WATCard::FWATCard watcard;									// Student current watcard
    WATCard::FWATCard groupOffCard;							// Student groupoff card
    WATCard * curCard;													// Card that student will use to purchase, either giftcard or watcard

};

#endif