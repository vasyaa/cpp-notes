#ifndef TEMPLATES_CPP98_H_
#define TEMPLATES_CPP98_H_

namespace templates_cpp98 {

using namespace std;

template <int i>
struct Factorial {
	enum {value = i * Factorial<i - 1>::value};
};

template<>
struct Factorial<0> {
	enum {value = 1};
};

void testFactorial() {
	Factorial<5> f;
	cout << f.value << endl;
}

// -----------------------------------------------------------------------------
template <int N, int D> struct Frak {
    static const long Num = N;
    static const long Den = D;
};

namespace test_frak1 {

template <int N, typename X> struct ScalarMultiplication {
    static const long Num = N * X::Num;
    static const long Den = N * X::Den;
};

void testFrak() {
	typedef Frak<1, 2> F1;
	Frak<10, 20> f2;

	ScalarMultiplication<5, F1> mult;

	cout<< mult.Num << "/" << mult.Den << endl;
}

}

namespace test_frak2 {

template <int N, typename F> struct ScalarMultiplication {
	typedef Frak<N*F::Num, N*F::Den> result;
};

void testFrak() {
	  typedef Frak< 2, 3 > Two_Thirds;
	  typedef ScalarMultiplication< 2, Two_Thirds >::result Four_Sixths;
	  std::cout << Four_Sixths::Num << "/" << Four_Sixths::Den << "\n";

}
}

// -----------------------------------------------------------------------------
inline void test() {
	testFactorial();
	test_frak1::testFrak();
	test_frak2::testFrak();
}

}



#endif /* TEMPLATES_CPP98_H_ */
