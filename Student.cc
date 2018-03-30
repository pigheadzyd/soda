#include "Student.h"
#include "Printer.h"
#include "NameServer.h"
#include "WATCardOffice.h"
#include "Groupoff.h"
#include "MPRNG.h"

extern MPRNG mprng;

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

}

void  Student::main() {

}