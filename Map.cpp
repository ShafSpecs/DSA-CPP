#include "Map.h"

template<class T, class U>
Map<T, U>::Map():
    keys(std::make_unique<T[]>(0)),
    values(std::make_unique<U[]>(0))
{
}

template<class T, class U>
Map<T, U>::Map(std::initializer_list<std::pair<T, U>> list)
{
    size_t initial_size = list.size();

    this->_sz = initial_size;
    this->keys = std::make_unique<T[]>(initial_size);
    this->values = std::make_unique<U[]>(initial_size);

    auto it = list.begin();
    for (int i = 0; i < list.size(); ++i) {
        this->keys[i] = it->first;
        this->values[i] = it->second;

        ++it;
    }
}

template<class T, class U>
int Map<T, U>::size() const {
    return this->_sz;
}

template<class T, class U>
bool Map<T, U>::empty() const {
    return this->_sz == 0;
}

template<class T, class U>
void Map<T, U>::clear() {
    this->_sz = 0;
    this->keys.reset();
    this->values.reset();

    this->keys = std::make_unique<T[]>(0);
    this->values = std::make_unique<U[]>(0);
}

template<class T, class U>
void Map<T, U>::insert(T k, U v) {
    this->keys.get()[_sz] = k;
    this->values.get()[_sz] = v;
    this->_sz = ++_sz;
}

template<class T, class U>
void Map<T, U>::insert(std::pair<T, U> pair) {
    this->keys.get()[_sz] = pair.first;
    this->values.get()[_sz] = pair.second;
    this->_sz = ++_sz;
}

template<class T, class U>
void Map<T, U>::erase(T key) {
    // This is super-inefficient
    auto key_arr = this->keys.get();

    int index = -1;
    for (int i = 0; i < _sz; ++i) {
        if (key_arr[i] == key) {
            index = i;
            break;
        }
    }

    if (index == -1) return;

    for (int j = index; j < _sz - 1; ++j) {
        auto value_arr = this->values.get();

        this->keys.get()[j] = key_arr[j + 1];
        this->values.get()[j] = value_arr[j + 1];
    }

    this->_sz -= 1;
}
