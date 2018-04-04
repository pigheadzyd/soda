//--------------------------------------------------------------------------------------------------------------------
// Define the interface to the VendingMachine Task for the vending machine system.
//--------------------------------------------------------------------------------------------------------------------
#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__
#include <map>

_Monitor Printer;
_Task NameServer;
class WATCard;

_Task VendingMachine {
  public:
    enum Flavours { lasmoi0, lasmoi1, lasmoi2, lasmoi3 };       // flavours of soda 
    _Event Free {};                                             // free, advertisement
    _Event Funds {};                                            // insufficient funds
    _Event Stock {};                                            // out of stock for particular flavour
    VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    ~VendingMachine();
    void buy( Flavours flavour, WATCard & card );               // Buy the flavour using WATCard
    unsigned int * inventory();                                 // Get the current stock condition of each falvour
    void restocked();                                           // Notify the restock has finished
    _Nomutex unsigned int cost();                               // Get the price of each soda
    _Nomutex unsigned int getId();                              // Get the vending machine id
  private:
    Printer & prt;                                              // Current printer
    NameServer & nameServer;                                    // Current nameserver
    unsigned int id;                                            // Identity of vending machine
    unsigned int sodaCost;                                      // Price of soda
    unsigned int maxStockPerFlavour;                            // Max stock of each flavour
    int SODA_FLAVOUR;                                           // Total kind of flavour
    unsigned int * curStock;                                    // Current stock of each flavour
    std::map<Flavours, unsigned int> flavourMap;                // Map between flavours and index
    unsigned int getFlavourId( Flavours flavour );              // Get the flavour index by the flavour           
    void main();                                                // Main body of task
};

#endif