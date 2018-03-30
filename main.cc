#include <iostream>
#include <string.h>

#include "config.h"
#include "Bank.h"
#include "Parent.h"
#include "Printer.h"
#include "test1.cc"
#include "test2.cc"
#include "MPRNG.h"

using namespace std;

MPRNG mprng;


int main(int argc, char const *argv[]){
	
	// command line arguement handler
	ConfigParms configParms;
	string tempFile = "soda.config";
	unsigned int seed = 1000;

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

	// read the input value
	char configFile [tempFile.length() + 1]; 
	std::strcpy( configFile, tempFile.c_str() );
	processConfigFile( configFile, configParms );

	Printer printer ( configParms.numStudents, configParms.numVendingMachines, configParms.numCouriers );
	Bank bank ( configParms.numStudents );
	//Test1 test1 ( bank );
	Parent parent ( printer, bank, configParms.numStudents, configParms.parentalDelay );
	Test2 test2 ( printer, bank );

	// bank.deposit( 0, 1 );
	// bank.withdraw( 0, 3 );
	// bank.deposit( 0, 2 );
	

	// printer.print( Printer::Parent, 'c' );
	// printer.print( Printer::Student, 0, 'c', 1 );
	// printer.print( Printer::Parent, 'c' );
	// printer.print( Printer::Vending, 1, 'b', 2 );
	// printer.print( Printer::Parent, 'c' );
	

	return 0;
}