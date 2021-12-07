#ifndef Record_H
#define Record_H

#include <iostream>
#include <string>

class Record {
private:
    //member variables
public:
    //accessor/mutator functions
};

// Stream operators
std::istream& operator>>(std::istream& is, Record& rec);
std::ostream& operator<<(std::ostream& os, Record& rec);

// Comparison operators
bool operator==(const Record& r1, const Record& r2);
#endif