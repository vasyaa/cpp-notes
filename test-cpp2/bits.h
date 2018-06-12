#ifndef BITS_H_
#define BITS_H_

#include <iostream>
#include <inttypes.h>
#include <cassert>

namespace bits {

uint64_t set_bit(uint64_t num, int n) {
    num |= 1UL << n;
    return num;
}

uint64_t clear_bit(uint64_t num, int n) {
    num &= ~(1UL << n);
    return num;
}

uint64_t toggle_bit(uint64_t num, int n) {
    num ^= 1UL << n;
    return num;
}

bool is_bit_set(uint64_t num, int n) {
    int bit = (num >> n) & 1U;
    return bit;
}

uint64_t set_bit_to_val(uint64_t num, int n, int val) {
    num ^= (-n ^ num) & (1UL << val);
    return num;
}

inline void test() {
    uint64_t num = 2;

    assert(is_bit_set(num, 1));
    num = 3;
    num = clear_bit(num, 0);
    assert(is_bit_set(num, 0) == 0);

    std::cout << "Ok" << std::endl;
}

}


#endif /* BITS_H_ */
