//--------------------------------------------------------------------------------------------------------------------
// Define the interface to the WATCard class for the vending machine system.
//--------------------------------------------------------------------------------------------------------------------
#ifndef __WATCARD_H__
#define __WATCARD_H__
#include <uFuture.h>

class WATCard {
  public:
    typedef Future_ISM<WATCard *> FWATCard;   // future watcard pointer
    WATCard();
    void deposit( unsigned int amount );      // Deposit the money into WATCard
    void withdraw( unsigned int amount );     // Withdraw the money from WATCard
    unsigned int getBalance();                // Get the current balance
  private:
  	unsigned int balance;                     // The balance for a WATCard
    WATCard( const WATCard & ) = delete;      // prevent copying
    WATCard & operator=( const WATCard & ) = delete;
};

#endif