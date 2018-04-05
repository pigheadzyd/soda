//--------------------------------------------------------------------------------------------------------------------
// Define the interface to the Parent Monitor for the vending machine system.
//--------------------------------------------------------------------------------------------------------------------
#ifndef __PARENT_H__
#define __PARENT_H__

_Monitor Printer; 
_Monitor Bank;

_Task Parent {
  public:
		Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay );
		~Parent();
  private:
  	Printer & prt;								// Current printer
  	Bank & bank;									// Current bank
  	unsigned int numStudents;			// Total number of students
  	unsigned int parentalDelay;		// Interval for parent sending money
  	void main();									// Main body of task
};

#endif