//--------------------------------------------------------------------------------------------------------------------
// Define the interface to the Bank Monitor for the vending machine system.
//--------------------------------------------------------------------------------------------------------------------

#ifndef __BANK_H__
#define __BANK_H__

_Monitor Bank {
  public:
		Bank( unsigned int numStudents );
		~Bank();
		void deposit( unsigned int id, unsigned int amount );			// deposit the amount of money into student with id
		void withdraw( unsigned int id, unsigned int amount );		// withdraw the amount of money from student with id
  private:
  	unsigned int numStudents;																	// the number of student 
  	unsigned int * studentBalance;														// the array of current students' balance
  	uCondition * waiting;																			// the condition array for waiting if there is not enough money for withdraw
};

#endif