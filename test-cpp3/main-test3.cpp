#include <bits/stdc++.h>
//#include <iostream>
//#include <algorithm>
//#include <utility>
//#include <vector>
//#include <type_traits>

using namespace std;

//template <typename ...Args>
//struct Counter{
//
//};

template <typename ...Args>
struct Counter;

template <typename T, typename ...Args>
struct Counter<T, Args...> {
    enum { value = Counter<Args...>::value + 1};
};

template <>
struct Counter<> {
    enum {value = 0};
};

template <typename T, typename ...Args>
struct Counter2 {
    enum {value = Counter2<Args...>::value + 1};
};

template <typename T>
struct Counter2<T> {
    enum {value = 1};
};

int main() {

    Counter<int, long, int> c1;
    cout << c1.value << endl;

    Counter2<int, long, int> c2;
    cout << c2.value << endl;

    return 0;
}
