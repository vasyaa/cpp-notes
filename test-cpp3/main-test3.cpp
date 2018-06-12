#include <bits/stdc++.h>


using namespace std;


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

void test1() {
    Counter<int, long, int> c1;
    cout << c1.value << endl;

    Counter2<int, long, int> c2;
    cout << c2.value << endl;
}

struct A {
    vector<int> v;
    A(){}
    A(const vector<int>& o) {
        cout << "A ctor const" << endl;
        v = o;
    }

    A(vector<int>&& o) {
        cout << "A ctor move" << endl;
        v = move(o);
    }

};
void test2() {
    vector<int> v(30);

    A a(v);
    A aa(vector<int>(25));

}

int main() {
    test1();
    test2();
    return 0;
}
