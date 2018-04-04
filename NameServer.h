//--------------------------------------------------------------------------------------------------------------------
// Define the interface to the NameServer Monitor for the vending machine system.
//--------------------------------------------------------------------------------------------------------------------
#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

_Monitor Printer;
_Task VendingMachine;

_Task NameServer {
  public:
    NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine * vendingmachine ); // Vending matchine to register themself
    VendingMachine * getMachine( unsigned int id );     // Student ask for a vending machine
    VendingMachine ** getMachineList();                 // Get the whole list of the registered vending machine
  private:
  	Printer & prt;
  	unsigned int numVendingMachines;                 	 // Total number of vending machines
  	unsigned int numStudents;                        	 // Total number of students
  	VendingMachine ** vendingMachineList;            	 // Map machine id to machine pointer
    unsigned int *machineOfStudent;                		 // Map student to machine id which is managed saperately
  	void main();                                       // Main body of task
};

#endif