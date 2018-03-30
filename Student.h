#ifndef __STUDENT_H__
#define __STUDENT_H__

class Printer;
class NameServer;
class WATCardOffice;
class Groupoff;

_Task Student {
	public:
		Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
             unsigned int id, unsigned int maxPurchases );
	private:
		Printer prt;
		NameServer nameServer;
		WATCardOffice cardOffice;
		Groupoff groupoff;
		unsigned int id;
		unsigned int maxPurchases;
    void main();
};

#endif