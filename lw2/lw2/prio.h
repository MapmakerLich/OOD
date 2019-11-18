#ifndef PRIO_H_INCLUDED
#define PRIO_H_INCLUDED

#include <string>

using namespace std;

class Prioritized {
    public:
    string prio;
    Prioritized(string p) { prio = p; }
    string toString() { return "[" + prio + "]"; }
};

#endif // PRIO_H_INCLUDED
