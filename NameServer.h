#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

_Monitor Printer;
_Task VendingMachine;

_Task NameServer {
  public:
    NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine * vendingmachine );
    VendingMachine * getMachine( unsigned int id );
    VendingMachine ** getMachineList();
  private:
  	Printer & prt;
  	// int curIndex;
  	// int curRegister;
  	unsigned int numVendingMachines;                 	// number of total machines
  	unsigned int numStudents;                        	// number of total students
  	VendingMachine ** vendingMachineList;            	// map machine id to machine pointer
    unsigned int *machineOfStudent;                		// map student to machine id which is managed saperately
  	void main();
};

#endif