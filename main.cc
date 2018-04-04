#include <iostream>
#include <string.h>
#include <unistd.h>         // getpid

#include "config.h"
#include "Bank.h"
#include "Parent.h"
#include "Printer.h"
#include "BottlingPlant.h"
#include "Groupoff.h"
#include "WATCard.h"
#include "WATCardOffice.h"
#include "NameServer.h"
#include "Truck.h"
#include "Student.h"
#include "VendingMachine.h"
#include "MPRNG.h"

using namespace std;

MPRNG mprng;


int main(int argc, char const *argv[]){
	
	// command line arguement handler
	ConfigParms configParms;
	string tempFile = "soda.config";
	unsigned int seed = getpid();

	try {
		switch ( argc ){
			case 3: seed = stoi ( argv[2] ); if ( seed < 1 ) throw 1; 
			case 2: tempFile = argv[1];
			case 1: break;
			default: throw 1;
		}	// switch
	}	catch ( ... ) {
			cout << "Usage: " << argv[0] << " [ config-file [ random-seed (> 0) ] ]" << endl;
			exit ( 1 );
	}	// try

	// debug only
  cout << "seed for this run is " << seed << endl;
  
	mprng.set_seed( seed );

	// read the input value
	char configFile [tempFile.length() + 1]; 
	std::strcpy( configFile, tempFile.c_str() );
	processConfigFile( configFile, configParms );

	Printer printer( configParms.numStudents, configParms.numVendingMachines, configParms.numCouriers );
	Bank bank ( configParms.numStudents );
	Parent parent( printer, bank, configParms.numStudents, configParms.parentalDelay );
	Groupoff groupoff( printer, configParms.numStudents, configParms.sodaCost, configParms.groupoffDelay );
	WATCardOffice office( printer, bank, configParms.numCouriers );
	NameServer nameServer( printer, configParms.numVendingMachines, configParms.numStudents );

	VendingMachine * vendingMachineList[configParms.numVendingMachines];
	for ( unsigned int i = 0; i < configParms.numVendingMachines; ++i ) {
		vendingMachineList[i] = new VendingMachine( printer, nameServer, i, configParms.sodaCost, configParms.maxStockPerFlavour );
	} // for

	BottlingPlant * bottlingPlant = new BottlingPlant( printer, nameServer, configParms.numVendingMachines, 
		configParms.maxShippedPerFlavour, configParms.maxStockPerFlavour, configParms.timeBetweenShipments );

	Student * studentList[configParms.numStudents];
	for ( unsigned int i = 0; i < configParms.numStudents; ++i ) {
		studentList[i] = new Student( printer, nameServer, office, groupoff, i, configParms.maxPurchases );
	} // for


	
	for ( unsigned int i = 0; i < configParms.numStudents; ++i ) {
		delete studentList[i];
	} // for	

	delete bottlingPlant;

	for ( unsigned int i = 0; i < configParms.numVendingMachines; ++i ) {
		delete vendingMachineList[i];
	} // for		
// cout << "returning deleting" << endl;
	return 0;
}