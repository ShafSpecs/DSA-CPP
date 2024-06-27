#include <iostream>
#include "Vector.h"

using namespace std;

int main() {
    auto v = Vector(5);
    // Vector init = {0};  // works!

    v[0] = 4;

    cout << "Size of vector v: " << v.size() << endl;
    cout << "Number at index 0 is supposed to be 4: " << v[0] << endl;

    const auto v_ptr =  new Vector(2);
    // Vector* v_ptr = &v;
    v_ptr->operator[](0) = 1;

    *v_ptr = v;

    cout << "Number at first position is supposed to be 4 now (copied): " << v_ptr->operator[](0) << endl;
    cout << "Memory address of the data should be: " << v_ptr << endl;

    cout << "Number at index 0 in vector v is now: " << v[1];

    delete v_ptr;

    return 0;
}
