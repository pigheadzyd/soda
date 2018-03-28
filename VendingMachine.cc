#include "VendingMachine.h"

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );

void VendingMachine::buy( Flavours flavour, WATCard & card ){}

unsigned int * VendingMachine::inventory(){
	return 0;
}          

void VendingMachine::restocked() {}

_Nomutex unsigned int VendingMachine::cost(){
	return 0;
}  

_Nomutex unsigned int VendingMachine::getId(){
	return 0;
}