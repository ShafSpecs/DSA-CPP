#ifndef MAP_H
#define MAP_H
#include <memory>

template<class T, class U>
class Map {
public:
    Map();
    Map(std::initializer_list<std::pair<T, U>> list);

    [[nodiscard]] int size() const;
    void insert(T k, U v);
    void insert(std::pair<T, U> pair);
    void erase(T key);
    [[nodiscard]] bool empty() const;
    void clear();

    U& operator[](T key);
    const U& operator[](T key) const;
    bool operator==(const Map& other) const;
    bool operator!=(const Map& other) const;
private:
    int _sz{};
    // Ig, I could have used a pair here...
    std::unique_ptr<T[]> keys{};
    std::unique_ptr<U[]> values{};

    int index_of(T key) const;
};



#endif //MAP_H
