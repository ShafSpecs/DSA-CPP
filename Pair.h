#ifndef PAIR_H
#define PAIR_H
#include <tuple>

template<class T, class U>
class Pair {
public:
    explicit Pair(std::tuple<T, U> pair);

    T first;
    U second;

    // Return `void` is T & U are the same (e.g <int, int>) and return
    // a new `Pair` if they different.
    auto swap() -> std::conditional_t<std::is_same_v<T, U>, void, Pair<U, T>>;
};

#endif //PAIR_H
