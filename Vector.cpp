#include <memory>
#include "Vector.h"

Vector::Vector(const int size):
    sz(size),
    data(std::make_unique<int[]>(size))
{
}

int Vector::size() const {
    return this->sz;
}

int Vector::get(const int index) const {
    return this->data[index];
}

void Vector::set(const int index, const int value) const {
    this->data[index] = value;
}

