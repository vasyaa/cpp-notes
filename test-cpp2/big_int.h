#ifndef BIG_INT_H_
#define BIG_INT_H_

#include <string>
#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>
#include <iterator>

namespace big_int {

//namespace internal {
//template <size_t SZ>
//
//struct block {
//
//};
//
//}

template <size_t SZ = 12>
class BigInt {
    int start = 0;
    int sign = 1;
public:
    BigInt() {
        s.resize(SZ, 0);
        start = SZ - 1;
    }

    BigInt(const BigInt& o) {
        s = o.s;
    }

    BigInt(BigInt&& o) {
        s = o.s;
    }

    BigInt& operator=(const BigInt& o) {
        if(&o != this) {
            s = o.s;
        }
        return *this;
    }

    BigInt& operator=(BigInt&& o) {
        if(&o != this) {
            s = std::move(o.s);
        }
        return *this;
    }

    BigInt(const std::string& o) {
        s.resize(SZ, 0);
        start = SZ - 1;
        for(size_t i = SZ - o.size(), j = 0; i < SZ; i++, j++) {
            s[i] = o[j] - '0';
        }
    }

    BigInt& operator=(const std::string& o) {
//        s = o;
        return *this;
    }

    friend BigInt operator+(const BigInt& n1, const BigInt& n2) {
        BigInt rc;
        size_t pos = SZ - 1;

        for(int i = pos; i >= 0; i--) {
            int r;
            r = n1.s[i] + n2.s[i] + rc.s[i];
            if(r >= 10) {
                rc.s[i - 1] = 1;
                r -= 10;
                rc.start = i;
            }
            rc.s[i] = r;
        }

        return rc;
    }

    BigInt& operator-(const BigInt& o) {
        return *this;
    }

    BigInt& operator*(const BigInt& o) {
        return *this;
    }

    BigInt& operator/(const BigInt& o) {
        return *this;
    }

    std::string str() {
        std::ostringstream str;
        std::copy(s.begin(), s.end(), std::ostream_iterator<int>(str));
        return str.str();
    }
    friend std::ostream& operator<<(std::ostream& ostr, const BigInt& o) {
        std::copy(o.s.begin(), o.s.end(), std::ostream_iterator<int>(ostr));
        return ostr;
    }
protected:
    std::vector<int> s;
};

inline void test() {
    {
    BigInt<> b1("1234567890");
    std::cout << b1.str() << std::endl;

    BigInt<> b2("1234567890");
    std::string rc_sum = "2469135780";

    BigInt<> b3(b1 + b2);
    std::cout << b3.str() << std::endl;
//    assert(rc_sum == b3.str());
    }

    {
    BigInt<> b1("51234567890");
    std::cout << b1.str() << std::endl;

    BigInt<> b2("51234567890");
    std::string rc_sum = "102469135780";

    BigInt<> b3(b1 + b2);
    std::cout << b3.str() << std::endl;
//    assert(rc_sum == b3.str());
    }
}

}


#endif /* BIG_INT_H_ */
