#include <iostream>
#include<set>
#include <functional>
#include <map>
#include "main.h"

using namespace std;

int main()
{
    const Prioritized *p1 = new Prioritized("1");
    const Prioritized *p2 = new Prioritized("5");
    const Prioritized *p3 = new Prioritized("2");
    map<const Prioritized*, int> myMap;
    myMap[p1] = 1;
    myMap[p2] = 5;
    myMap[p3] = 2;
    MySet<Prioritized> s = Comp(myMap);
    s.s.insert(*p1);
    s.s.insert(*p2);
    s.s.insert(*p3);

    for (Prioritized i : s.s) {
        cout << i.toString() << " ";
    }

    cout << endl;
    return 0;
}
