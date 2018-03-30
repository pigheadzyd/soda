#ifndef __TRUCK_H__
#define __TRUCK_H__

class Printer, NameServer, BottlingPlant;

_Task Truck {
  public:
    Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
  private:
  	Printer & prt;
  	NameServer & nameServer;
  	BottlingPlant & plant;
  	unsigned int numVendingMachines;
  	unsigned int maxStockPerFlavour;
    void main();
};

#endif