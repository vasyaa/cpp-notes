#ifndef SQRT_H_
#define SQRT_H_

#include <iostream>
#include <cmath>

namespace mysqrt {

double mysqrt(int a, double prec = 0.0001) {
    int n = 0;
    double rc = a / 2;

    while (1) {
        n++;
        std::cout << n << std::endl;
        double d = rc * rc;
        double delt = fabs(a - d);
        if (delt <= prec) {
            return rc;
        }
        if (d > a) {
            rc = rc - rc / 2;
        } else {
            rc = rc + rc / 2;
        }
    }
}

double mysqrt2(double a, double prec = 0.001) {
    int n = 0;
    double rc = 1;

    while (1) {
        n++;
        std::cout << n << std::endl;
        double d = rc * rc;
        double delt = fabs(a - d);
        if (delt <= prec) {
            return rc;
        }

        rc = rc - (rc * rc - a) / (2 * rc);
    }
}

inline void test() {
    double N = 10;
    double rc = mysqrt2(N);
    std::cout << rc << " " << sqrt(N) << std::endl;
}

}

#endif /* SQRT_H_ */
