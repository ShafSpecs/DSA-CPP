#include <iostream>
#include "Vector.h"

using namespace std;

int main() {
    const auto v = Vector(5);

    v.set(0, 4);
    v.set(2, 7);
    // should fail; it doesn't
    // v.set(10, 1);

    cout << "Size of vector v: " << v.size() << endl;
    cout << "Number at index 0 is " << v.get(0) << endl;

    cout << "Value of v[1] should be zero. It is:  " << v.get(1) << endl;

    const auto v_ptr =  new Vector(2);
    v_ptr->set(0, 1);

    cout << "Number at first position is: " << v_ptr->get(0) << endl;
    cout << "Memory address of the data should be: " << v_ptr;

    delete v_ptr;

    return 0;
}
