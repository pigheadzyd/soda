#include <iostream>
#include <string.h>

#include "Printer.h"
#include "config.h"
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

	// printer.print( Printer::Parent, 'c' );
	// printer.print( Printer::Student, 0, 'c', 1 );
	// printer.print( Printer::Parent, 'c' );
	// printer.print( Printer::Vending, 1, 'b', 2 );
	// printer.print( Printer::Parent, 'c' );
	

	return 0;
}