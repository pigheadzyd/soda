#include <iostream>
#include <string.h>
#include <vector>

#include "Printer.h"
#include "config.h"

using namespace std;

int main(int argc, char const *argv[]){
	
	// get the input argunment
	ConfigParms configParms;
	string tempFile = "soda.config";

	if ( argc == 2 ) {
		tempFile = argv[1];
	}
	char configFile [tempFile.length() + 1]; 


	std::strcpy( configFile, tempFile.c_str() );
	processConfigFile( configFile, configParms );

	Printer printer ( configParms.numStudents, configParms.numVendingMachines, configParms.numCouriers );
	return 0;
}