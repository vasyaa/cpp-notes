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
    num ^= (-val ^ num) & (1UL << n);
    return num;
}

void print_bits_backward(uint64_t num) {
   for(int bit=0;bit<(sizeof(uint64_t) * 8); bit++)
   {
      std::cout << (int)(num & 0x01);
      num = num >> 1;
   }
   std::cout  << std::endl;
}

inline void test() {
    uint64_t num = 2;

    assert(is_bit_set(num, 1));

    num = 3;
    num = clear_bit(num, 0);
    assert(is_bit_set(num, 0) == 0);

    num = 0;
    num = set_bit_to_val(num, 2, 1);
    assert(num == 4);
    std::cout << "Ok" << std::endl;

    print_bits_backward(5);
    print_bits_backward(-5);

}

}


#endif /* BITS_H_ */
