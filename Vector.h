#ifndef VECTOR_H
#define VECTOR_H

#include <memory>


class Vector {
public:
    explicit Vector(int size);

    int size() const;
    int get(int index) const;
    void set(int index, int value) const;
private:
    int sz{};
    std::unique_ptr<int[]> data{};
};


#endif //VECTOR_H
