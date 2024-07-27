#ifndef MAP_H
#define MAP_H
#include <memory>


template<class T, class U>
class Map {
public:
    Map(std::initializer_list<std::pair<T, U>> list);

    [[nodiscard]] int size() const;
private:
    int _sz{};
    std::unique_ptr<T[]> keys{};
    std::unique_ptr<U[]> values{};
};



#endif //MAP_H
