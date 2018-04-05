//--------------------------------------------------------------------------------------------------------------------
// Define the interface to the Truck Task for the vending machine system.
//--------------------------------------------------------------------------------------------------------------------
#ifndef __TRUCK_H__
#define __TRUCK_H__

_Monitor Printer;
_Task NameServer;
_Task BottlingPlant;

_Task Truck {
  public:
    Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
    ~Truck();
  private:
  	Printer & prt;                     // Current printer
  	NameServer & nameServer;           // Current nameserver
  	BottlingPlant & plant;             // Current bottling plant
  	unsigned int numVendingMachines;   // Total number of vending machine
  	unsigned int maxStockPerFlavour;   // Max number
    int curIndex;                      // Next vending machine suspose to restock
    unsigned int total;                // Toal number of soda get from bottling plant
    int SODA_FLAVOUR;                  // Total kind of flavour
    unsigned int maxTotal;             // Max number of a ventding machine require to restock 
    unsigned int * product;            // Array of the number of flavour get from the bottling plant
    bool * emptyStatus;                // Array to indicating the flavour is empty of not
    void main();                       // Main body of task
};

#endif