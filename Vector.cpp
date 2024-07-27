#include <memory>
#include "Vector.h"

template<typename T>
Vector<T>::Vector(const int size):
    sz(size),
    data(std::make_unique<T[]>(size))
{
    for (int i = 0; i < sz; ++i) {
        data[i] = T();
    }
}

template<typename T>
Vector<T>::~Vector() {
    data.reset();
    sz = 0;
}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T> list):
    sz(static_cast<int>(list.size())),
    data(std::make_unique<T[]>(list.size()))
{
    std::copy(list.begin(), list.end(), data.get());
}

template<typename T>
Vector<T>::Vector(const Vector& other):
    sz(other.sz),
    data(std::make_unique<int[]>(other.sz))
{
    std::copy(other.data.get(), other.data.get() + other.size(), data.get());
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept:
    sz(other.sz),
    data(std::move(other.data))
{
    other.sz = 0;
}

template<typename T>
size_t Vector<T>::size() const {
    return this->sz;
}

template<typename T>
T* Vector<T>::begin() const {
    return this->data.get();
}

template<typename T>
T* Vector<T>::end() const {
    return this->data.get() + this->sz;
}

template<typename T>
T &Vector<T>::operator[](const int index) {
    return this->data[index];
}

template<typename T>
const T &Vector<T>::operator[](const int index) const {
    return this->data[index];
}

// Btw, `Vector &other` and `Vector& other` are the same
// (the same applies to `Vector &&other` and `Vector&& other`)
// They are just different ways to write reference types.
template<typename T>
Vector<T> &Vector<T>::operator=(const Vector& other) {
    this->sz = other.sz;
    this->data = std::make_unique<int[]>(other.sz);
    std::copy(other.data.get(), other.data.get() + other.size(), this->data.get());
    return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) { // prevent self-assignment & errors
        this->sz = other.sz;
        this->data = std::move(other.data);
        other.sz = 0;
    }
    return *this;
}

template<typename T>
bool Vector<T>::operator==(const Vector &other) const {
    if (this->size() != other.size()) {
        return false;
    }

    for (int i = 0; i < this->size(); ++i) {
        if (this->operator[](i) != other[i]) {
            return false;
        }
    }

    return true;
}

template<typename T>
bool Vector<T>::operator!=(const Vector &other) const {
    if (this->size() != other.size()) {
        return true;
    }

    for (int i = 0; i < this->size(); ++i) {
        if (this->operator[](i) != other[i]) {
            return true;
        }
    }

    return false;
}
