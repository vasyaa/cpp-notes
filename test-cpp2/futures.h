#ifndef FUTURES_H_
#define FUTURES_H_

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <type_traits>

// future example
#include <iostream>       // std::cout
#include <future>         // std::async, std::future
#include <chrono>         // std::chrono::milliseconds
#include <thread>


namespace futures {

// a non-optimized way of checking for prime numbers:
bool is_prime(int x) {
    for (int i = 2; i < x; ++i)
        if (x % i == 0)
            return false;
    return true;
}


template <typename T>
T my_auto(T t) {
    return t;
}

inline void test_fut() {
    // call function asynchronously:
    std::future<bool> fut = std::async(is_prime, 444444443);

    // do something while waiting for function to set future:
    std::cout << "checking, please wait";
    std::chrono::milliseconds span(100);
    while (fut.wait_for(span) == std::future_status::timeout)
        std::cout << '.' << std::flush;

    bool x = fut.get();     // retrieve return value

    std::cout << "\n444444443 " << (x ? "is" : "is not") << " prime.\n";
}

void test_thr() {
    int x;
    int X = 444444443;

    std::thread t = std::thread([=, &x](){
        x = is_prime(X);
    });

    t.join();
    std::cout << "\n444444443 " << (x ? "is" : "is not") << " prime.\n";
}


void test() {
    test_thr();
//    test_fut();
}

}


#endif /* FUTURES_H_ */
