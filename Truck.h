#ifndef __TRUCK_H__
#define __TRUCK_H__

class Printer;
class NameServer;
class BottlingPlant;

_Task Truck {
  public:
    Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
  private:
  	Printer & prt;
  	NameServer & nameServer;
  	BottlingPlant & plant;
    int currentIndex = 0;
    int SODA_FLAVOUR = 4;
    unsigned int total = 0;
    unsigned int maxTotal;
    unsigned int currentIndex;
  	unsigned int numVendingMachines;
  	unsigned int maxStockPerFlavour;
    unsigned int product[SODA_FLAVOUR];
    bool emptyStatus[SODA_FLAVOUR];
    void main();
};

#endif