#include <memory>
#include "Vector.h"

Vector::Vector(const int size):
    sz(size),
    data(std::make_unique<int[]>(size))
{
    for (int i = 0; i < sz; ++i) {
        data[i] = 0;
    }
}

Vector::~Vector() {
    data = nullptr;
}

Vector::Vector(const std::initializer_list<int> list):
    sz(static_cast<int>(list.size())),
    data(std::make_unique<int[]>(list.size()))
{
    std::copy(list.begin(), list.end(), data.get());
}

Vector::Vector(const Vector& other):
    sz(other.sz),
    data(std::make_unique<int[]>(other.sz))
{
    std::copy(other.data.get(), other.data.get() + other.size(), data.get());
}

Vector::Vector(Vector&& other) noexcept:
    sz(other.sz),
    data(std::move(other.data))
{
    other.sz = 0;
}


int Vector::size() const {
    return this->sz;
}

int* Vector::begin() const {
    return this->data.get();
}

int* Vector::end() const {
    return this->data.get() + this->sz;
}

int &Vector::operator[](const int index) {
    return this->data[index];
}

const int &Vector::operator[](const int index) const {
    return this->data[index];
}

// Btw, `Vector &other` and `Vector& other` are the same
// (the same applies to `Vector &&other` and `Vector&& other`)
// They are just different ways to write reference types.
Vector &Vector::operator=(const Vector& other) {
    this->sz = other.sz;
    this->data = std::make_unique<int[]>(other.sz);
    std::copy(other.data.get(), other.data.get() + other.size(), this->data.get());
    return *this;
}

Vector &Vector::operator=(Vector&& other) noexcept {
    if (this != &other) { // prevent self-assignment & errors
        this->sz = other.sz;
        this->data = std::move(other.data);
        other.sz = 0;
    }
    return *this;
}

bool Vector::operator==(const Vector &v1, const Vector &v2) const {
    if (v1.size() != v2.size()) {
        return false;
    }

    for (int i = 0; i < v1.size(); ++i) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }

    return true;
}

bool Vector::operator!=(const Vector &v1, const Vector &v2) const {
    if (v1.size() != v2.size()) {
        return true;
    }

    for (int i = 0; i < v1.size(); ++i) {
        if (v1[i] != v2[i]) {
            return true;
        }
    }

    return false;
}
