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
	private:
		Printer & prt;
		NameServer nameServer;
		WATCardOffice cardOffice;
		Groupoff groupoff;
		unsigned int id;
		unsigned int maxPurchases;
    void main();

    unsigned int numOfPurchases;
    VendingMachine::Flavours favouriteFlavour;
    unsigned int favouriteFlavourInt;
    VendingMachine * vendingMachine;

    WATCard::FWATCard watcard;
    WATCard::FWATCard groupOffCard;
    WATCard * curCard;

};

#endif