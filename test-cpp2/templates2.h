#ifndef TEMPLATES2_H_
#define TEMPLATES2_H_

#include <iostream>

namespace templates2 {

using namespace std;

template <typename T, typename ...Args>
struct Counter {
    static const int value = Counter<Args...>::value + 1;

};

template <typename T>
struct Counter<T> {
    static const int value = 1;
};


inline void test() {
    Counter<int, double, char, long> c;

    cout << c.value << endl;

}

}


#endif /* TEMPLATES2_H_ */
