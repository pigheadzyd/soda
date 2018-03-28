#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <map>

_Monitor Printer {
  public:
    enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    ~Printer();
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
  private:
    struct PrintInfo {
      bool update = false;
      bool updateValue1 = false;
      bool updateValue2 = false;
      char state;
      int value1;
      int value2;
    };
    std::map<Kind, unsigned int> indexMap;
    PrintInfo* printInfo;
    unsigned int numStudents;
    unsigned int numVendingMachines;
    unsigned int numCouriers;
    unsigned int total;
    void flush();
    void setState( unsigned int index, char state );
    void setState( unsigned int index, char state, int value1 );
    void setState( unsigned int index, char state, int value1, int value2 );
    unsigned int getIndex( Kind kind );
    unsigned int getIndex( Kind kind, unsigned int lid );
};

#endif
