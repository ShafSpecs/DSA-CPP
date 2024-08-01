#include "Pair.h"

template<class T, class U>
Pair<T, U>::Pair(std::tuple<T, U> pair):
    first(std::get<0>(pair)),
    second(std::get<1>(pair))
{
}

template<class T, class U>
Pair<T, U>::Pair(T first, U second):
    first(first),
    second(second)
{
}

template<class T, class U>
auto Pair<T, U>::swap() -> std::conditional_t<std::is_same_v<T, U>, void, Pair<U, T>> {
    if constexpr (std::is_same_v<T, U>) {
        T temp = this->first;
        this->first = this->second;
        this->second = temp;
    } else {
        return Pair<U, T>({second, first});
    }
}
