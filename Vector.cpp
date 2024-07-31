#include <memory>
#include "Vector.h"

template<typename T>
Vector<T>::Vector():
    data(nullptr)
{
}

template<typename T>
Vector<T>::Vector(const int size):
    _sz(size),
    data(std::make_unique<T[]>(size)),
    _space(size)
{
    for (int i = 0; i < _sz; ++i) {
        data[i] = T();
    }
}

template<typename T>
Vector<T>::~Vector() {
    data.reset();
    _sz = _space = 0;
}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T> list):
    _sz(static_cast<int>(list.size())),
    data(std::make_unique<T[]>(list.size())),
    _space(list.size())
{
    std::copy(list.begin(), list.end(), data.get());
}

template<typename T>
Vector<T>::Vector(const Vector& other):
    _sz(other._sz),
    data(std::make_unique<int[]>(other._sz)),
    _space(other._space)
{
    std::copy(other.data.get(), other.data.get() + other._sz, data.get());
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept:
    _sz(other._sz),
    data(std::move(other.data)),
    _space(other._sz)
{
    other._sz = other._space = 0;
}

template<typename T>
size_t Vector<T>::size() const {
    return this->_sz;
}

template<typename T>
T* Vector<T>::begin() const {
    return this->data.get();
}

template<typename T>
T* Vector<T>::end() const {
    return this->data.get() + this->_sz;
}

template<class T>
bool Vector<T>::empty() const {
    return _sz == 0;
}

template<class T>
T Vector<T>::front() const {
    return data[0];
}

template<class T>
T Vector<T>::back() const {
    return data[_sz - 1];
}

template<class T>
T Vector<T>::at(const int index) const {
    if (index >= _sz) throw std::out_of_range("Attempted to access an item out of bounds!");
    return data[index];
}

template<class T>
int Vector<T>::capacity() const {
    return _space;
}

template<class T>
void Vector<T>::reserve(int newalloc) {
    if (newalloc <= _space) return;

    auto new_data = std::make_unique<T[]>(newalloc);
    for (int i = 0; i < _sz; ++i) {
        new_data[i] = std::move(data[i]);
    }

    data.reset();
    data = std::move(new_data);
    _space = newalloc;
}

template<class T>
void Vector<T>::resize(const int new_size) {
    if (new_size <= _sz) return;

    reserve(new_size);

    for(int i = _sz; i < new_size; ++i) {
        data[i] = T();
    }

    _sz = new_size;
}

template<class T>
void Vector<T>::push_back(T new_item) {
    if (_space == 0) reserve(8);

    if (_space == _sz) reserve(INCREASE_FACTOR * _space);

    data[_sz] = new_item;
    ++_sz;
}

template<class T>
void Vector<T>::pop_back() {
    if (_sz == 0) return; // throw?

    data[_sz - 1] = T();
    --_sz;
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
    this->_sz = other._sz;
    if (this->_space < other._sz) this->_space = other._sz;
    this->data = std::make_unique<int[]>(this->_space);
    std::copy(other.data.get(), other.data.get() + other.size(), this->data.get());
    return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) { // prevent self-assignment & errors
        this->_sz = this->_space = other._sz;
        this->data = std::move(other.data);
        other._sz = other._space = 0;
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
