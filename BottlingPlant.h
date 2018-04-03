#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

_Monitor Printer;
_Task NameServer;

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
  	unsigned int numVendingMachines;
  	unsigned int maxShippedPerFlavour;
  	unsigned int maxStockPerFlavour;
  	unsigned int timeBetweenShipments;
  	bool shutdown;
    int SODA_FLAVOUR;
    unsigned int * product;
    void main();
};

#endif