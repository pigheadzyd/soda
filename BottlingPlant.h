#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

class Printer, NameServer;

_Task BottlingPlant {
  public:
    _Event Shutdown {};                       // shutdown plant
    BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    ~BottlingPlant();
    void getShipment( unsigned int cargo[] );
  private:
  	Printer & prt;
  	NameServer & nameServer;
    int SODA_FLAVOUR = 4;
  	unsigned int numVendingMachines;
  	unsigned int maxShippedPerFlavour;
  	unsigned int maxStockPerFlavour;
  	unsigned int timeBetweenShipments;
    unsigned int product[SODA_FLAVOUR];
  	bool shutdown;
    void main();
};

#endif