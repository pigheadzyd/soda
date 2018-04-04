//--------------------------------------------------------------------------------------------------------------------
// Define the interface to the WATCardOffice Task for the vending machine system.
//--------------------------------------------------------------------------------------------------------------------
#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__
#include <queue>
#include <vector>
#include "WATCard.h"

_Monitor Printer;
_Monitor Bank;

_Task WATCardOffice {
	struct Job {                              // marshalled arguments and return future
		unsigned int studentId;
		unsigned int amount;
		WATCard * card;
		WATCard::FWATCard result;             	// return future
		Job( unsigned int studentId, unsigned int amount, WATCard * card ) 
		: studentId( studentId ), amount( amount ), card( card ) {}
	};																				// ???												

	_Task Courier { 
		Printer & prt;
		Bank & bank;
		WATCardOffice & office;
		unsigned int id;
		void main();
	public:
		Courier(Printer & prt, Bank & bank, WATCardOffice & office, unsigned int id);
		~Courier();
	};                    										// communicates with bank

	Printer & prt;														// Current printer
	Bank & bank;															// Current bank
	std::vector< Courier *> courierPool;			// ???
	std::queue<Job *> jobs;										// ???
	unsigned int numCouriers;									// Total number of couriers
	void main();												  		// Main body of task
public:
	_Event Lost {};                           // lost WATCard
	WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
	~WATCardOffice();
	WATCard::FWATCard create( unsigned int sid, unsigned int amount );		// For creating a new WATCard
	WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card );	// For transfer the money into WATCard
	Job * requestWork();											// ???
};

#endif