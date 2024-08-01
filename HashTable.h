#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <list>
#include <optional>
#include <type_traits>

#include "Pair.h"
#include "Vector.h"

template<class T, class U>
class HashTable {
    static_assert(
        std::is_same_v<T, std::string> ||
        std::is_same_v<T, int> ||
        std::is_same_v<T, char> ||
        std::is_same_v<T, long>,
        "Key type must be a string, int, char, or long"
    );

public:
    HashTable();
    explicit HashTable(int size);

    void insert(T key, U value);
    std::optional<U> get(T key);
    void remove(T key);
    bool is_value(T key, U value);

    [[nodiscard]] size_t capacity() const;
    size_t size();
private:
    int TABLE_SIZE = 16;
    Vector<std::list<Pair<T, U>>> table;
    int hash(T key);
};

#endif //HASHTABLE_H
