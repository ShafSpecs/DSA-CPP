#include <iostream>
#include "Vector.h"

using namespace std;

int main() {
    auto v = Vector(5);
    // Vector init = {0};  // works!

    v[0] = 4;
    v[3] = 5;

    cout << "Vector 'v' initialised all elements to 0, and we were able to "
            "override the first and fourth elements to 4 and 5 respectively" << endl;
    cout << "1. v[0] = " << v[0] << endl;
    cout << "2. v[1] = " << v[1] << endl;
    cout << "3. v[2] = " << v[2] << endl;
    cout << "4. v[3] = " << v[3] << endl;
    cout << "5. v[4] = " << v[4] << endl;

    return 0;
}
