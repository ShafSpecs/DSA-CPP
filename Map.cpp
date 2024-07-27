#include "Map.h"

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
