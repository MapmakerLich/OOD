#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <set>
#include <map>
#include <functional>
#include "prio.h"

struct Comp {
    Comp(const std::map<const Prioritized*, int> &m) : myMap(m) { }
    std::map<const Prioritized*, int> myMap;
    bool operator()(const Prioritized &p1, const Prioritized &p2) { return myMap[&p1] < myMap[&p2]; }
};

template <class T> class MySet {
    public:
    std::set<T, Comp> s;
    MySet(const Comp &f) : s(f) {}
};

#endif // MAIN_H_INCLUDED
