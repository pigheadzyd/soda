//--------------------------------------------------------------------------------------------------------------------
// Define the interface to the Printer Monitor for the vending machine system.
//--------------------------------------------------------------------------------------------------------------------
#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <map>

_Monitor Printer {
  public:
    // Possibe states when print is called
    enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };    
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    ~Printer();
    // Different print methods by different inputs
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
  private:
    // The info struct to record the require print info
    struct PrintInfo {                                                                                  
      bool update = false;
      bool updateValue1 = false;
      bool updateValue2 = false;
      char state;
      int value1;
      int value2;
    }; 
    std::map<Kind, unsigned int> indexMap;      // Mapping the state to the index for printing position
    PrintInfo* printInfo;                       // Array of PrintInfo about all required printing items, a buffer
    unsigned int numStudents;                   // Total number of students
    unsigned int numVendingMachines;            // Total number of vending machines
    unsigned int numCouriers;                   // Total number of couriers
    unsigned int total;                         // Total number of require printing items
    void flush();                               // Print the buffer immediately and clear the buffer
    // Different setState method by different input length
    void setState( unsigned int index, char state );
    void setState( unsigned int index, char state, int value1 );
    void setState( unsigned int index, char state, int value1, int value2 );
    // Different getIndex method by different calling index method
    unsigned int getIndex( Kind kind );
    unsigned int getIndex( Kind kind, unsigned int lid );
};

#endif
