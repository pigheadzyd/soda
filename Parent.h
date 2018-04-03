#ifndef __PARENT_H__
#define __PARENT_H__

_Monitor Printer; 
_Monitor Bank;

_Task Parent {
  public:
		Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay );
		~Parent();
  private:
  	Printer & prt;
  	Bank & bank;
  	unsigned int numStudents;
  	unsigned int parentalDelay;
  	void main();
};

#endif