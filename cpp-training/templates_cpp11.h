/*
 * templates_cpp11.h
 *
 *  Created on: Apr 27, 2018
 *      Author: vasyaa
 */

#ifndef TEMPLATES_CPP11_H_
#define TEMPLATES_CPP11_H_


#include <iostream>
#include <vector>
#include <string>

namespace templates_cpp11 {

using namespace std;

//------------------------------------------------------------------------------
template <int val>
struct Fib {
	static const int value = Fib<val - 1>::value + Fib<val - 2>::value;
};

template <>
struct Fib<0> {
	static const int value = 0;
};

template <>
struct Fib<1> {
	static const int value = 1;
};

void testFib() {
	Fib<7> f;
	cout << f.value << endl;
}

//------------------------------------------------------------------------------
template <typename T>
T adder(T t) {
	T s = t;
	return s;
}

template <typename T, typename ... Rest>
T adder(T t, Rest ... rest) {
	T s = t + adder(rest...);
	return s;
}

void testAdderFunc() {
	int s = adder(1,2,3,4,5);
	cout << s << endl;
}

//------------------------------------------------------------------------------
template <int ... Rest>
struct Adder;

template <int head, int ... Rest>
struct Adder<head, Rest...> {
	enum {value = head + Adder<Rest...>::value};
};

template <>
struct Adder<> {
	enum {value = 0};
};

void testAdderClass() {
	Adder<1,2,3,4,5> a;
	cout << a.value << endl;
}

//------------------------------------------------------------------------------
template <typename ... Rest>
struct Size;

template <typename Head, typename ... Rest>
struct Size<Head, Rest...> {
	enum {value = Size<Rest...>::value + 1};
};

template <>
struct Size<> {
	enum {value = 0};
};

void testSize() {
	Size<int, float, char, long> s;
	cout << s.value << endl;
}

inline void test() {
	testAdderFunc();
	testAdderClass();
	testSize();
}

}


#endif /* TEMPLATES_CPP11_H_ */
