//--------------------------------------------------------------------------------------------------------------------
// Define the interface to the Groupoff Task for the vending machine system.
//--------------------------------------------------------------------------------------------------------------------

#ifndef __GROUPOFF_H__
#define __GROUPOFF_H__
#include "WATCard.h"
#include <vector>

_Monitor Printer;

_Task Groupoff {
	public:
		Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    ~Groupoff();
		WATCard::FWATCard giftCard();											// To give a future giftcard		
	private:
		Printer & prt;																		// Current printer
		unsigned int numStudents;													// Total number of student  
		unsigned int sodaCost;														// Price of each soda 
		unsigned int groupoffDelay;												// Interval between sending giftcard
    std::vector<WATCard::FWATCard> giftcards;					// Array of the all the future giftcard
    std::vector<WATCard *> cardList;									// Array of the giftcard that has been sent
    void main();
};

#endif