#include "HashTable.h"

#include <cstdint>

template<class T, class U>
HashTable<T, U>::HashTable():
    table(TABLE_SIZE)
{
}

template<class T, class U>
HashTable<T, U>::HashTable(int size):
    TABLE_SIZE(size),
    table(size)
{
}

template<class T, class U>
void HashTable<T, U>::insert(T key, U value) {
    int index = hash(key);

    for (auto& pair : table[index]) {
        if (pair.first == key) {
            pair.second = value;
            return;
        }
    }

    table[index].push_back({key, value});
}

template<class T, class U>
std::optional<U> HashTable<T, U>::get(T key) {
    int index = hash(key);

    for (auto& pair : table[index]) {
        if (key == pair.first) return pair.second;
    }

    return std::nullopt;
}

template<class T, class U>
void HashTable<T, U>::remove(T key) {
    int index = hash(key);

    table[index].remove_if([key](Pair<T, U>& pair) -> bool { return pair.first == key; });
}

template<class T, class U>
bool HashTable<T, U>::is_value(T key, U value) {
    int index = hash(key);

    for (auto& pair : table[index]) {
        if (pair.first == key) {
            if (pair.second == value) return true;
            return false;
        }
    }

    return false;
}

template<class T, class U>
size_t HashTable<T, U>::capacity() const {
    return TABLE_SIZE;
}

template<class T, class U>
int HashTable<T, U>::hash(T key) {
    if constexpr (std::is_same_v<T, int> || std::is_same_v<T, long>) {
        auto x = static_cast<uint64_t>(key);

        // Mixing the bits
        x = (x ^ (x >> 16)) * 0x45d9f3b;
        x = x ^ (x >> 16);

        return static_cast<int>(x % TABLE_SIZE);
    }
    else if constexpr (std::is_same_v<T, char>) {
        return key % TABLE_SIZE;
    }
    else if constexpr (std::is_same_v<T, std::string>) {
        // simple djb2 algorithm
        u_long hash = 5381;

        for (const char c : key) {
            hash = ((hash << 5) + hash) + c;
        }

        return hash % TABLE_SIZE;
    }
    else { return 0; }
}
