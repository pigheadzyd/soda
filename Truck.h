#ifndef __TRUCK_H__
#define __TRUCK_H__
#include <string>
_Monitor Printer;
_Task NameServer;
_Task BottlingPlant;

_Task Truck {
  public:
    Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
    ~Truck();
  private:
  	Printer & prt;
  	NameServer & nameServer;
  	BottlingPlant & plant;
    int curIndex = 0;
    unsigned int total = 0;
    unsigned int maxTotal;
  	unsigned int numVendingMachines;
  	unsigned int maxStockPerFlavour;
    int SODA_FLAVOUR;
    unsigned int * product;
    bool * emptyStatus;
    void main();
    void print( std::string kind, int value1, int value2, int value3, int value4 );
    void print( std::string kind, unsigned int id, int value1, int value2, int value3, int value4 );
};

#endif