#ifndef __GROUPOFF_H__
#define __GROUPOFF_H__

class Printer;
class WATCard;
_Task Groupoff {
	public:
		Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
		WATCard::FWATCard giftCard();
	private:
		Printer prt;
		unsigned int numStudents;
		unsigned int sodaCost;
		unsigned int groupoffDelay;
    void main();
};

#endif