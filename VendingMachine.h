#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__
#include <map>

_Monitor Printer;
_Task NameServer;
class WATCard;

_Task VendingMachine {
  public:
    enum Flavours { lasmoi0, lasmoi1, lasmoi2, lasmoi3 };                    // flavours of soda (YOU DEFINE)
    _Event Free {};                           // free, advertisement
    _Event Funds {};                          // insufficient funds
    _Event Stock {};                          // out of stock for particular flavour
    VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    ~VendingMachine();
    void buy( Flavours flavour, WATCard & card );
    unsigned int * inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
  private:
    Printer & prt;
    NameServer & nameServer;
    unsigned int id;
    unsigned int soda;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
    int SODA_FLAVOUR;
    unsigned int * curStock;
    std::map<Flavours, unsigned int> flavourMap;
    unsigned int getFlavourId( Flavours flavour );
    void main();

};

#endif