#ifndef FINITE_DERIVATE_EULER_H_
#define FINITE_DERIVATE_EULER_H_

#include <vector>
#include <iostream>
#include <functional>

namespace finite_derivate_euler {

using namespace std;

double f(double t, double y) {
    return y;
}

double f2(double t, double y) {
    return t * t + y * y;
}

template <double F(double,double)>
//template <std::function<double(double, double)>>
struct FiniteDerivateEuler {
    vector<double> v;

//    std::function<double(double, double)> F;
    double run(double start_t, double start_y, double at_t) {
        double h = 0.1;
        double t;
        double y, y1;

        t = start_t;
        y = start_y;

        for(int i = 0; i * h < at_t; i++) {
            y1 = y + h * F(t, y);
            t += h;
            y = y1;
        }

        cout << t << "=" << y << endl;
        return y;
    }
};

inline void test() {
    FiniteDerivateEuler<f2> fd;
    fd.run(0, 1, 0.5);
}

}

#endif /* FINITE_DERIVATE_EULER_H_ */
