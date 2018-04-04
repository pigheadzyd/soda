#ifndef __GROUPOFF_H__
#define __GROUPOFF_H__
#include "WATCard.h"
#include <vector>

_Monitor Printer;

_Task Groupoff {
	public:
		Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    ~Groupoff();
		WATCard::FWATCard giftCard();
	private:
		Printer & prt;
		unsigned int numStudents;
		unsigned int sodaCost;
		unsigned int groupoffDelay;
    std::vector<WATCard::FWATCard> giftcards;
    void main();
};

#endif