#ifndef NUMBER_WITH_COMMAS_H_
#define NUMBER_WITH_COMMAS_H_

#include <string>
#include <sstream>
#include <iostream>

namespace number_with_commas {

using namespace std;

string get_string_with_commas( string& s) {
    ostringstream rc;

    const string::size_type first_comma_at = s.size() - (s.size() / 3) * 3;

    string::size_type i = 0;
    for(; i < first_comma_at; i++) {
        rc << s[i];
    }
    if(first_comma_at > 0) {
        rc << ",";
    }
    for(i = first_comma_at; i < s.size(); i++) {
        if(i && ((i - first_comma_at) % 3 == 0)) {
            rc << ",";
        }
        rc << s[i];
    }

    return rc.str();
}

inline void test() {
    {
    string s = "12345678901234567890";
    string rc = get_string_with_commas(s);
    cout << rc << endl;
    }
    {
    string s = "123456789012345678";
    string rc = get_string_with_commas(s);
    cout << rc << endl;
    }
}

}

#endif /* NUMBER_WITH_COMMAS_H_ */
