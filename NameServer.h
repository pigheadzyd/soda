#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

class Printer, VendingMachines;

_Task NameServer {
  public:
    NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine * vendingmachine );
    VendingMachine * getMachine( unsigned int id );
    VendingMachine ** getMachineList();
  private:
  	Printer & prt;
  	int curIndex;
  	int curRegister;
  	unsigned int numVendingMachines;
  	unsigned int numStudents;
  	VendingMachine ** vendingMachineList;
  	void main();
};

#endif