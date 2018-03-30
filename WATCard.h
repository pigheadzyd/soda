#ifndef __WATCARD_H__
#define __WATCARD_H__

class WATCard {
  public:
    typedef Future_ISM<WATCard *> FWATCard;   // future watcard pointer
    WATCard();
    void deposit( unsigned int amount );
    void withdraw( unsigned int amount );
    unsigned int getBalance();
  private:
  	unsigned int balance = 0;
    WATCard( const WATCard & ) = delete;      // prevent copying
    WATCard & operator=( const WATCard & ) = delete;
};

#endif