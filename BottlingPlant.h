//--------------------------------------------------------------------------------------------------------------------
// Define the interface to the Bottling task for the vending machine system.
//--------------------------------------------------------------------------------------------------------------------
#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

_Monitor Printer;
_Task NameServer;
_Task Truck;

_Task BottlingPlant {
  public:
    _Event Shutdown {};                       // shutdown plant
    BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    ~BottlingPlant();
    void getShipment( unsigned int cargo[] ); // Move the product onto the truck
  private:
  	Printer & prt;                            // Current printer
  	NameServer & nameServer;                  // Current nameserver
  	unsigned int numVendingMachines;          // Total nubmer of vending machine
  	unsigned int maxShippedPerFlavour;        // Max shipped number of per flavour
  	unsigned int maxStockPerFlavour;          // Max stocked number per flavour in vending machine
  	unsigned int timeBetweenShipments;        // The interval between each production
  	bool shutdown;                            // Flag for checking 
    int SODA_FLAVOUR;                         // Total kind of flavour
    unsigned int * product;                   // The array of production of flavours
    Truck * truck;                            // The truck for transfer between bottling plant and vending machine
    void main();                              // Main body of task
};

#endif