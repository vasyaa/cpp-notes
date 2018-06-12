#ifndef TEMPLATES1_H_
#define TEMPLATES1_H_

#include <iostream>

namespace templates1 {

using namespace std;

void printf(const char* s) {
    while(*s) {
        cout << *s;
        cout.flush();
        s++;
    }
}

template <typename T, typename ...Args>
void printf(const char* s, T value, Args... args) {
    while(*s) {
        if(*s == '%') {
            s++;
            if(*s == '%') {
                cout << *s;
                s++;
            }
            else {
                s++;
                cout << value;
                cout.flush();
                printf(s, args...);
                return;
            }
        }
        cout << *s;
        cout.flush();
        s++;
    }
}

void printf() {

}


inline void test() {
    printf("test %d %c %s asas\n", 23, 'A', "ASDFGH");
}


}


#endif /* TEMPLATES1_H_ */
