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
int Map<T, U>::index_of(T key) const {
    auto key_arr = this->keys.get();

    int index = -1;
    for (int i = 0; i < _sz; ++i) {
        if (key_arr[i] == key) {
            index = i;
            break;
        }
    }

    return index;
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

    const int index = index_of(key);

    if (index == -1) return;

    for (int j = index; j < _sz - 1; ++j) {
        auto value_arr = this->values.get();

        this->keys.get()[j] = key_arr[j + 1];
        this->values.get()[j] = value_arr[j + 1];
    }

    this->_sz -= 1;
}

template<class T, class U>
bool Map<T, U>::operator==(const Map& other) const {
    if (this->_sz != other._sz) return false;

    const auto this_map_keys = this->keys.get();
    const auto this_map_values = this->values.get();
    const auto other_map_keys = other.keys.get();
    const auto other_map_values = other.values.get();

    for (int i = 0; i < _sz; ++i) {
        if (this_map_keys[i] != other_map_keys[i]) return false;
        if (this_map_values[i] != other_map_values[i]) return  false;
    }

    return true;
}

template<class T, class U>
bool Map<T, U>::operator!=(const Map& other) const {
    if (this->_sz == other._sz) return false;

    const auto this_map_keys = this->keys.get();
    const auto this_map_values = this->values.get();
    const auto other_map_keys = other.keys.get();
    const auto other_map_values = other.values.get();

    for (int i = 0; i < _sz; ++i) {
        if (this_map_keys[i] == other_map_keys[i]) return false;
        if (this_map_values[i] == other_map_values[i]) return false;
    }

    return true;
}

template<class T, class U>
U& Map<T, U>::operator[](T key) {
    auto index_of_key = this->index_of(key);

    if (index_of_key == -1) {
        // This works because Map is in a linear, simple,
        // unsorted format.
        index_of_key = _sz;
        insert(key, U());
    };

    return values[index_of_key];
}

template<class T, class U>
const U& Map<T, U>::operator[](T key) const {
    const auto index_of_key = this->index_of(key);

    if (index_of_key == -1) throw std::out_of_range("Key is not found");

    return values[index_of_key];
}
